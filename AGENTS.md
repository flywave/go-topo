# go-topo

Go bindings for a C++ 3D topological geometry modeling library (OpenCASCADE-based).

## Project structure

- Go package root: `package topo` — cgo wrappers calling C API layer
- C++ source: `src/` — compiled to `libtopo.a` via CMake
- Prebuilt libs: `libs/{darwin,darwin_arm,linux,linux_arm,windows}/`
- External C++ deps: `external/` (OpenCASCADE, Ipopt, Boost, Eigen, Freetype, Fontconfig, etc.)
- Go-only deps: `github.com/flywave/go3d`, `golang.org/x/image`

## Build

```sh
# Build C++ libs (Apple Silicon example)
cmake -S . -B build/build -G "Xcode"
cmake --build build/build --config Release

# Test Go package (requires prebuilt libs in libs/)
go test ./...
```

Go cgo link flags are in the `#cgo` directives of each `.go` file — they reference `./libs/<platform>/`.

## Local dev constraints

- `go.mod` has `replace` directives pointing to `../gltf` and `../go-mst` — those repos must exist as sibling directories
- Go tests require CGO and the prebuilt static libraries; they will fail without them
- Tests that read DXF/IFC STEP files may need fixture data not checked into this repo

## C++ rebuild

```sh
cmake -S . -B build/build -G "Xcode" && cmake --build build/build --config Release
cmake --install build/build --prefix libs/darwin_arm
```

## Key entrypoints

| File | Purpose |
|------|---------|
| `topo.go` | Core types (Shape, Location, constants) |
| `shape.go` | Shape methods |
| `shape_ops.go` | Boolean ops, extrude, sweep, loft, offset |
| `primitives.go` | Box, sphere, cylinder, prism creation |
| `geometry.go` | Geometry type constants |
| `geometry_creator.go` | Curve/surface creation helpers |
| `dxf.go` / `ifc.go` | DXF/IFC import |
| `mesh.go` / `topo_export.go` | Mesh export via callback |
| `selector.go` / `workplane.go` / `sketch.go` | Higher-level modeling |

## Workplane API

Entrypoint: `NewWorkplane()` (empty) or `NewNamedWorkplane("XY")` or `NewWorkplaneFromName("XY", nil)`.

Convenience wrappers in `workplane.go`:

| Method | Calls | Use |
|--------|-------|-----|
| `BoxCentered(w,h,d)` | `BoxAll(w,h,d, true,true,true)` | Centered box, combined |
| `BoxCorners(w,h,d)` | `Box(w,h,d, false,false,false, true,true)` | Corner-at-origin, combined |
| `SphereCentered(r)` | `Sphere(r, nil, -90,90,360, false,false,false, true,true)` | |
| `CylinderCentered(h,r)` | `CylinderAll(h,r, nil,360, true,true,true)` | |
| `CylinderAt(h,r)` | `Cylinder(h,r, nil,360, false,false,false, true,true)` | Grows in +Z from XY |
| `RectCentered(w,h)` | `RectAll(w,h, true,false)` | Non-construction |
| `CircleCentered(r)` | `Circle(r, false)` | |
| `PolygonSimple(n,d)` | `Polygon(n,d, false,false)` | |
| `ExtrudeSimple(d)` | `Extrude(d, true,true, false,0)` | |
| `CutBlindSimple(d)` | `CutBlind(d, true, false,0)` | |
| `RevolveSimple(a)` | `Revolve(nil,nil, a, true,true)` | Defaults to Y axis |
| `LoftSimple()` | `Loft(false, true,true)` | Non-ruled |
| `HoleThrough(d)` | `Hole(d, nil, true)` | Through-hole (auto depth) |
| `HoleThroughWithDepth(d,dep)` | `Hole(d, &dep, true)` | |

Optional pointer params (`nil` = use C++ default): `origin`, `basePoint`, `direct`, `normal`, `auxSpine`, `smoothing`, `pnt`, `dir`, `depth`, `axisStart`, `axisEnd`, `rotate`, `offset`, `vec`.

Check errors: `if err := wp.Err(); err != nil { ... }`.

## Key entrypoints

| File | Purpose |
|------|---------|
| `topo.go` | Core types (Shape, Location, constants) |
| `shape.go` | Shape methods |
| `shape_ops.go` | Boolean ops, extrude, sweep, loft, offset |
| `primitives.go` | Box, sphere, cylinder, prism creation |
| `geometry.go` | Geometry type constants |
| `geometry_creator.go` | Curve/surface creation helpers |
| `dxf.go` / `ifc.go` | DXF/IFC import |
| `mesh.go` / `topo_export.go` | Mesh export via callback |
| `selector.go` / `workplane.go` / `sketch.go` | Higher-level modeling |

## Tests

- `topo_test.go` — basic shape creation, wire ops, multi-segment pipe
- `shape_ops_test.go` — centerline fitting, wire sampling, shape outline, catenary
- `dxf_test.go`, `ifc_test.go` — DXF/IFC import (may require external fixture files)

Run: `go test -v -count=1 ./...`
Run one test: `go test -v -run TestSampleCenterlineWire ./...`

## C++ API nil-safety

The C API layer (`src/workplane_c_api.cc`) now handles `nullptr` for optional pointer parameters (those with C++ defaults). The Go wrapper forwards `nil` as `NULL`. Methods with "required" semantics still panic on `nil` — this is intentional.
