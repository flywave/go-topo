package topo

import (
	"testing"
)

// C 枚举一致性校验: topo.go 的字面量常量必须与 src/topo_c_api.h 的
// 匿名枚举取值逐一对齐 (枚举为 0 递增)。C 侧改动枚举顺序/插入新值时,
// 此测试立即报警, 防止 Go 常量与 C 实现静默错位。
func TestCgoEnumAlignment(t *testing.T) {
	cases := []struct {
		name  string
		goVal int
		cVal  int
	}{
		{"FUSE", FUSE, cgoEnumCValues()["FUSE"]},
		{"CUT", CUT, cgoEnumCValues()["CUT"]},
		{"COMMON", COMMON, cgoEnumCValues()["COMMON"]},
		{"WEST", WEST, cgoEnumCValues()["WEST"]},
		{"EAST", EAST, cgoEnumCValues()["EAST"]},
		{"NORTH", NORTH, cgoEnumCValues()["NORTH"]},
		{"SOUTH", SOUTH, cgoEnumCValues()["SOUTH"]},
		{"UP", UP, cgoEnumCValues()["UP"]},
		{"DOWN", DOWN, cgoEnumCValues()["DOWN"]},
		{"TextureCube", TextureCube, cgoEnumCValues()["TextureCube"]},
		{"TextureNormal", TextureNormal, cgoEnumCValues()["TextureNormal"]},
		{"TextureNormalAutoScale", TextureNormalAutoScale, cgoEnumCValues()["TextureNormalAutoScale"]},
		{"TopoSolid", TopoSolid, cgoEnumCValues()["TopoSolid"]},
		{"TopoShell", TopoShell, cgoEnumCValues()["TopoShell"]},
		{"TopoFace", TopoFace, cgoEnumCValues()["TopoFace"]},
		{"TopoEdge", TopoEdge, cgoEnumCValues()["TopoEdge"]},
		{"TopoVertex", TopoVertex, cgoEnumCValues()["TopoVertex"]},
		{"TopoWire", TopoWire, cgoEnumCValues()["TopoWire"]},
		{"TopoCompound", TopoCompound, cgoEnumCValues()["TopoCompound"]},
		{"TopoCompSolid", TopoCompSolid, cgoEnumCValues()["TopoCompSolid"]},
		{"TopoShape", TopoShape, cgoEnumCValues()["TopoShape"]},
		{"FORWARD", FORWARD, cgoEnumCValues()["FORWARD"]},
		{"REVERSED", REVERSED, cgoEnumCValues()["REVERSED"]},
		{"INTERNAL", INTERNAL, cgoEnumCValues()["INTERNAL"]},
		{"EXTERNAL", EXTERNAL, cgoEnumCValues()["EXTERNAL"]},
		{"UNKNOW", UNKNOW, cgoEnumCValues()["UNKNOW"]},
	}
	for _, c := range cases {
		if c.goVal != c.cVal {
			t.Errorf("Go 常量 %s=%d 与 C 枚举 %d 不一致", c.name, c.goVal, c.cVal)
		}
	}
}
