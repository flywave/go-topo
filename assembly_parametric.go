package topo

import (
	"encoding/json"
	"fmt"
	"sync"
)

// ParametricData 参数化配方: primitive 类型 + 参数 JSON
// 生成器往 Assembly 放几何时挂载, 编辑器修改后可由注册的 builder 确定性重建
type ParametricData struct {
	Type   string          `json:"type"`
	Params json.RawMessage `json:"params,omitempty"`
}

// parametricNode 装配树中一个节点对应的配方子树 (C++ 侧 AddAssembly 为深拷贝,
// 配方无法挂在 C++ 对象上, 仅在 Go 侧按节点名同步维护)
type parametricNode struct {
	data     *ParametricData
	children map[string]*parametricNode
}

// ParametricElement 参数化装配导出的 JSON 节点, 含层级/name/location/color/配方
// Location 为 Trsf 的 12 个分量 (行优先, 平移在 [3] [7] [11])
type ParametricElement struct {
	Name     string               `json:"name"`
	Location *[12]float64         `json:"location,omitempty"`
	Color    *[3]float64          `json:"color,omitempty"`
	Type     string               `json:"type,omitempty"`
	Params   json.RawMessage      `json:"params,omitempty"`
	Children []*ParametricElement `json:"children,omitempty"`
}

// ParametricBuilder 由参数 JSON 重建几何
// 返回的 loc 仅在节点 JSON 未携带 location 时作为缺省放置; 节点 location 优先
type ParametricBuilder func(params json.RawMessage) (shape *Shape, loc *TopoLocation, err error)

var (
	parametricBuildersMu sync.RWMutex
	parametricBuilders   = map[string]ParametricBuilder{}
)

// RegisterParametricBuilder 注册参数化 builder, fn 为 nil 时注销
func RegisterParametricBuilder(typeName string, fn ParametricBuilder) {
	parametricBuildersMu.Lock()
	defer parametricBuildersMu.Unlock()
	if fn == nil {
		delete(parametricBuilders, typeName)
		return
	}
	parametricBuilders[typeName] = fn
}

func lookupParametricBuilder(typeName string) ParametricBuilder {
	parametricBuildersMu.RLock()
	defer parametricBuildersMu.RUnlock()
	return parametricBuilders[typeName]
}

// SetParametric 设置装配自身的参数化配方, 返回自身便于链式调用
func (c *Assembly) SetParametric(data *ParametricData) *Assembly {
	c.parametric = data
	return c
}

// Parametric 返回装配自身的参数化配方, 未设置返回 nil
func (c *Assembly) Parametric() *ParametricData {
	return c.parametric
}

// AddObjectParams 同 AddObject, 同时为元素挂载参数化配方, data 为 nil 时退化为 AddObject
func (c *Assembly) AddObjectParams(obj *AssemblyObject, loc *TopoLocation, name string, color *Color, data *ParametricData) *Assembly {
	c.AddObject(obj, loc, name, color)
	if data != nil {
		if c.childParametrics == nil {
			c.childParametrics = map[string]*parametricNode{}
		}
		c.childParametrics[name] = &parametricNode{data: data}
	}
	return c
}

// GetParametric 按名查询顶层子元素的参数化配方
func (c *Assembly) GetParametric(name string) (*ParametricData, bool) {
	n, ok := c.childParametrics[name]
	if !ok || n.data == nil {
		return nil, false
	}
	return n.data, true
}

// ExportParametric 导出整棵装配树为 JSON (含层级/name/location/color/参数化配方),
// 可存数据库或发前端编辑, 编辑后经 RebuildFromParametric 确定性重建
// 注意: 未挂配方的元素导出后只有 name/location/color, 重建时为占位容器 (不含原几何)
func (c *Assembly) ExportParametric() ([]byte, error) {
	return json.Marshal(c.exportParametricNode(c.parametric, c.childParametrics))
}

func (c *Assembly) exportParametricNode(self *ParametricData, children map[string]*parametricNode) *ParametricElement {
	el := &ParametricElement{Name: c.GetName()}
	d := c.GetLocation().Trsf().Data()
	el.Location = &d
	// 颜色仅在合法范围内导出: 未设颜色的装配经 C++ color() 会得到
	// Quantity_Color 默认值, 但历史上可能读到垃圾值 (含 NaN / 越界),
	// 这类值会让重建侧 Quantity_Color 构造抛异常
	if r, g, b := c.GetColor().RGBD(); r == r && g == g && b == b &&
		r >= 0 && r <= 1 && g >= 0 && g <= 1 && b >= 0 && b <= 1 {
		el.Color = &[3]float64{r, g, b}
	}
	if self != nil {
		el.Type = self.Type
		el.Params = self.Params
	}
	for _, ch := range c.Children() {
		var cself *ParametricData
		var cchildren map[string]*parametricNode
		if n, ok := children[ch.GetName()]; ok {
			cself = n.data
			cchildren = n.children
		}
		el.Children = append(el.Children, ch.exportParametricNode(cself, cchildren))
	}
	return el
}

// RebuildFromParametric 由 ExportParametric 导出的 JSON 重建装配
// 有配方的节点经注册的 builder 重建几何; 无配方的节点重建为占位容器 (原点 vertex)
// 节点类型未注册 builder 时返回明确错误, 不静默跳过
func RebuildFromParametric(data []byte) (*Assembly, error) {
	var root ParametricElement
	if err := json.Unmarshal(data, &root); err != nil {
		return nil, fmt.Errorf("assembly: invalid parametric JSON: %w", err)
	}
	return rebuildParametricNode(&root)
}

func rebuildParametricNode(el *ParametricElement) (*Assembly, error) {
	var shape *Shape
	var bloc *TopoLocation
	if el.Type != "" {
		fn := lookupParametricBuilder(el.Type)
		if fn == nil {
			return nil, fmt.Errorf("assembly: no parametric builder registered for type %q (element %q)", el.Type, el.Name)
		}
		s, l, err := fn(el.Params)
		if err != nil {
			return nil, fmt.Errorf("assembly: build element %q (type %q): %w", el.Name, el.Type, err)
		}
		if s == nil || s.inner == nil {
			return nil, fmt.Errorf("assembly: builder for type %q returned nil shape (element %q)", el.Type, el.Name)
		}
		shape = s
		bloc = l
	} else {
		// 无配方: 容器节点, 用原点 vertex 占位 (空 compound 是 null shape, assembly 构造不接受)
		shape = NewVertex(0, 0, 0).ToShape()
	}
	loc := bloc
	if el.Location != nil {
		d := *el.Location
		loc = NewTopoLocation(NewTrsf(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8], d[9], d[10], d[11]))
	}
	var color *Color
	if el.Color != nil {
		cl := NewColor(*el.Color)
		color = &cl
	}
	as := NewAssembly(NewAssemblyObjectFromShpe(*shape), loc, el.Name, color)
	if el.Type != "" {
		as.SetParametric(&ParametricData{Type: el.Type, Params: el.Params})
	}
	for _, ch := range el.Children {
		childAs, err := rebuildParametricNode(ch)
		if err != nil {
			return nil, err
		}
		// loc/color 传 nil, 保留子节点自身构造时的值
		as.AddAssembly(childAs, nil, "", nil)
		if as.HasError() {
			return nil, fmt.Errorf("assembly: add child %q: %s", ch.Name, as.Error())
		}
	}
	return as, nil
}
