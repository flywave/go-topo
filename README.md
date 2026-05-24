# go-topo

Go bindings for a 3D topological geometry modeling library built on **OpenCASCADE**. Provides a CadQuery-style workplane API for parametric CAD modeling from Go.

```
go get github.com/flywave/go-topo
```

## Architecture

```
Go package (package topo)
    ↕ cgo
C API layer  (src/*_c_api.cc → libtopo.a)
    ↕
C++ core     (namespace flywave::topo)
    ↕
OpenCASCADE  (external/ogg/)
```

## Quick Start

```go
package main

import "github.com/flywave/go-topo"

func main() {
    wp := topo.NewWorkplane()
    r := wp.BoxCentered(2.0, 2.0, 0.5)
    r.ExportTo("plate.step")  // → STEP
    r.ExportTo("plate.stl")   // → STL (binary)
}
```

## Key Types

| Type | Description |
|------|-------------|
| `Workplane` | Fluent CAD modeling API (100+ methods) |
| `Shape` | Generic 3D shape (compound/solid/face/wire/edge/vertex) |
| `Vertex` | 0D point |
| `Edge` | 1D curve |
| `Wire` | Connected sequence of edges |
| `Face` | 2D surface |
| `Shell` | Connected collection of faces |
| `Solid` | Closed 3D volume |
| `Compound` | Collection of any shapes |
| `TopoVector` | 3D vector |
| `TopoLocation` | Placement / transformation |
| `Selector` | Shape filtering by direction, radius, area, etc. |

## Workplane API

Construction and sketching is done through the `Workplane` type:

```go
wp := topo.NewWorkplane()

// 2D sketching
r := wp.CircleCentered(2.0)
r = r.RectCentered(0.5, 0.75)
r = r.PolygonSimple(6, 1.0)

// 3D operations
r = r.ExtrudeSimple(0.5)
r = r.RevolveSimple(180)
r = r.LoftSimple()

// Boolean operations
r = r.Cut(other, true, 0.001)
r = r.Union(other, true, false, 0.001)

// Face/edge selection
r = r.Faces(">Z", "")
r = r.Edges("|Z", "").Fillet(0.125)

// Through-hole
r = r.HoleThrough(diameter)

// Export
r.ExportTo("output.step")
r.ExportTo("output.stl")
```

## Export Formats

| Format | Extension | Method |
|--------|-----------|--------|
| STEP | `.step`, `.stp` | `ExportTo(path)` — auto-detected |
| STL | `.stl` | `ExportTo(path)` — binary, auto-detected |
| BREP | `.brep` | `Shape.ExportBrep(path)` |

`ExportTo` detects format from the file extension.

## Import Formats

| Format | Entry Point |
|--------|-------------|
| STEP | `Shape.ImportFromStep(path)` |
| BREP | `Shape.ImportFromBrep(path)` |
| DXF | `NewDxfReader(path)` → `.DoRead()` |
| IFC | `IfcConverter.LoadFile(path)` |

## Directory Structure

```
go-topo/
├── *.go                  # Go package (package topo)
├── src/                  # C++ source → libtopo.a
│   ├── *.hh, *.cc        # Core C++ geometry kernel
│   ├── *_c_api.cc        # C API bridge layer
│   └── *_test.cc         # C++ tests
├── libs/                 # Prebuilt static libraries
│   ├── linux/            # libtopo.a + OpenCASCADE + deps
│   ├── linux_arm/
│   ├── darwin/
│   ├── darwin_arm/
│   └── windows/
├── external/             # Vendored C++ deps
│   └── ogg/              # OpenCASCADE source
├── go.mod
└── CMakeLists.txt
```

## Building the C++ Library

```sh
cmake -S . -B build/build && cmake --build build/build --config Release
cmake --install build/build --prefix libs/linux
```

Requires prebuilt dependencies in `external/`. For Apple Silicon:

```sh
cmake -S . -B build/build -G "Xcode" && cmake --build build/build --config Release
cmake --install build/build --prefix libs/darwin_arm
```

## Testing

```sh
go test ./...              # Requires prebuilt libs in libs/
go test -v -count=1 ./...
```

Build and run the 33 CadQuery-style example tests:

```sh
go test -v -run "Test_example_" .
```

## Dependencies

**C++ (vendored):** OpenCASCADE, Boost 1.67, Ipopt, Eigen, IFC, fontconfig, freetype, ICU, NLopt, METIS, LAPACK/BLAS, MA27, libxml2, libexpat, zlib, RapidJSON

**Go:** `github.com/flywave/go3d`, `golang.org/x/image`

## License

See LICENSE file.
