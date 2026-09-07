package topo

/*
#include <stdlib.h>
#include <stdint.h>
*/
import "C"

import (
	"sync"
	"unsafe"
)

// cgo 回调注册表:
// cgo 规则禁止把"指向含 Go 指针内存"的指针 (如 &funcValue) 传给 C,
// 运行时会 panic ("cgo argument has Go pointer to unpinned Go pointer")。
// 因此把回调值登记在 Go 侧注册表里, 传给 C 的是一个 malloc 出来的小槽位,
// 槽内只存整数 id (不是 Go 指针, 合规); 导出回调函数用槽位取回 id 再查表。
// 回调均为同步调用, 调用返回后立即释放槽位并注销。

var cbRegistry = struct {
	sync.Mutex
	next uintptr
	m    map[uintptr]interface{}
}{m: make(map[uintptr]interface{})}

// registerCallback 登记回调值, 返回可安全传给 C 的槽位指针。
// 必须配对调用 unregisterCallback 释放。
func registerCallback(v interface{}) unsafe.Pointer {
	cbRegistry.Lock()
	cbRegistry.next++
	id := cbRegistry.next
	cbRegistry.m[id] = v
	cbRegistry.Unlock()

	slot := C.malloc(C.size_t(unsafe.Sizeof(C.uintptr_t(0))))
	*(*C.uintptr_t)(slot) = C.uintptr_t(id)
	return slot
}

// unregisterCallback 注销回调并释放槽位 (在 C 调用返回后调用)。
func unregisterCallback(slot unsafe.Pointer) {
	if slot == nil {
		return
	}
	id := uintptr(*(*C.uintptr_t)(slot))
	C.free(slot)
	cbRegistry.Lock()
	defer cbRegistry.Unlock()
	delete(cbRegistry.m, id)
}

// callbackValue 由导出回调函数调用: 用槽位取回登记的回调值。
func callbackValue(slot unsafe.Pointer) interface{} {
	if slot == nil {
		return nil
	}
	id := uintptr(*(*C.uintptr_t)(slot))
	cbRegistry.Lock()
	defer cbRegistry.Unlock()
	return cbRegistry.m[id]
}

// firstElem 返回切片首元素地址; 空切片返回 nil。
// 用于消除 &s[0] 直接取址在空输入时的 index-out-of-range panic。
func firstElem[T any](s []T) unsafe.Pointer {
	if len(s) == 0 {
		return nil
	}
	return unsafe.Pointer(&s[0])
}
