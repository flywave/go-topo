package topo

/*
#include "topo_c_api.h"
*/
import "C"

// cgoEnumCValues 返回 src/topo_c_api.h 匿名枚举的 C 侧原值,
// 供 topo_const_alignment_test.go 与 Go 字面量常量对照。
// 置于常规构建文件 (非 _test.go) 以复用包级 cgo 配置。
func cgoEnumCValues() map[string]int {
	return map[string]int{
		"FUSE":                   int(C.BOOLFUSE),
		"CUT":                    int(C.BOOLCUT),
		"COMMON":                 int(C.BOOLCOMMON),
		"WEST":                   int(C.DIR_WEST),
		"EAST":                   int(C.DIR_EAST),
		"NORTH":                  int(C.DIR_NORTH),
		"SOUTH":                  int(C.DIR_SOUTH),
		"UP":                     int(C.DIR_UP),
		"DOWN":                   int(C.DIR_DOWN),
		"TextureCube":            int(C.TextureCube),
		"TextureNormal":          int(C.TextureNormal),
		"TextureNormalAutoScale": int(C.TextureNormalAutoScale),
		"TopoSolid":              int(C.TopoSolid),
		"TopoShell":              int(C.TopoShell),
		"TopoFace":               int(C.TopoFace),
		"TopoEdge":               int(C.TopoEdge),
		"TopoVertex":             int(C.TopoVertex),
		"TopoWire":               int(C.TopoWire),
		"TopoCompound":           int(C.TopoCompound),
		"TopoCompSolid":          int(C.TopoCompSolid),
		"TopoShape":              int(C.TopoShape),
		"FORWARD":                int(C.ORI_FORWARD),
		"REVERSED":               int(C.ORI_REVERSED),
		"INTERNAL":               int(C.ORI_INTERNAL),
		"EXTERNAL":               int(C.ORI_EXTERNAL),
		"UNKNOW":                 int(C.ORI_UNKNOW),
	}
}
