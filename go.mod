module github.com/flywave/go-topo

go 1.24

toolchain go1.24.4

replace github.com/flywave/gltf => ../gltf

replace github.com/flywave/go-mst => ../go-mst

require (
	github.com/flywave/go-mst v0.0.0-00010101000000-000000000000
	github.com/flywave/go3d v0.0.0-20250816053852-aed5d825659f
)

require (
	github.com/flywave/gltf v0.20.4-0.20250828104044-ebb99e75f3cc // indirect
	golang.org/x/image v0.26.0 // indirect
)
