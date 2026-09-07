package topo

import (
	"errors"
	"reflect"
)

// errNaNParams Create* 系列 NaN 参数统一拒绝错误。
var errNaNParams = errors.New("primitives: 参数含 NaN, 已拒绝")

// hasNaN 深度检查参数中是否含 NaN。
//
// NaN 维度会穿过 cgo 边界在 OCC 深处引发空指针解引用 (SIGSEGV) 或无界循环,
// 且 C++ 的 try/catch 无法拦截这类错误, 因此必须在 Go 边界统一拒绝。
// 遍历包含: 导出/未导出字段 (Point3/Dir3 等 C 值封装的字段为未导出)、
// 嵌套结构体、切片、数组、指针。
func hasNaN(v interface{}) bool { return anyNaN(reflect.ValueOf(v)) }

func anyNaN(rv reflect.Value) bool {
	switch rv.Kind() {
	case reflect.Float32, reflect.Float64:
		return rv.Float() != rv.Float() // NaN 判定, 避免依赖 math 包
	case reflect.Interface, reflect.Ptr:
		if rv.IsNil() {
			return false
		}
		return anyNaN(rv.Elem())
	case reflect.Struct:
		for i := 0; i < rv.NumField(); i++ {
			if anyNaN(rv.Field(i)) {
				return true
			}
		}
	case reflect.Slice, reflect.Array:
		for i := 0; i < rv.Len(); i++ {
			if anyNaN(rv.Index(i)) {
				return true
			}
		}
	}
	return false
}
