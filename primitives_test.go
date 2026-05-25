package topo

import (
	"math"
	"testing"
)

func TestCreateSphere(t *testing.T) {
	shp := CreateSphere(SphereParams{Radius: 20})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sphere")
	}
	if !shp.IsValid() {
		t.Fatal("Sphere is not valid")
	}
}

func TestCreateSphereWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{10, 20, 30})
	shp := CreateSphereWithPlace(SphereParams{Radius: 15}, center)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sphere with place")
	}
}

func TestCreateRotationalEllipsoid(t *testing.T) {
	shp := CreateRotationalEllipsoid(RotationalEllipsoidParams{
		PolarRadius:      8,
		EquatorialRadius: 4,
		Height:           16,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create full rotational ellipsoid")
	}
	if !shp.IsValid() {
		t.Fatal("Full rotational ellipsoid is not valid")
	}
}

func TestCreateRotationalEllipsoidPartial(t *testing.T) {
	shp := CreateRotationalEllipsoid(RotationalEllipsoidParams{
		PolarRadius:      5,
		EquatorialRadius: 3,
		Height:           6,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create partial rotational ellipsoid")
	}
}

func TestCreateRotationalEllipsoidWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateRotationalEllipsoidWithPlace(RotationalEllipsoidParams{
		PolarRadius:      8,
		EquatorialRadius: 4,
		Height:           16,
	}, center, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rotational ellipsoid with place")
	}
}

func TestCreateCuboid(t *testing.T) {
	shp := CreateCuboid(CuboidParams{
		Length: 30,
		Width:  20,
		Height: 10,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cuboid")
	}
	if !shp.IsValid() {
		t.Fatal("Cuboid is not valid")
	}
}

func TestCreateCuboidWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	zDir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateCuboidWithPlace(CuboidParams{
		Length: 30,
		Width:  20,
		Height: 10,
	}, center, xDir, zDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cuboid with place")
	}
}

func TestCreateDiamondFrustum(t *testing.T) {
	shp := CreateDiamondFrustum(DiamondFrustumParams{
		TopDiag1:    10.0,
		TopDiag2:    7.5,
		BottomDiag1: 20.0,
		BottomDiag2: 15.0,
		Height:      12.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create diamond frustum")
	}
	if !shp.IsValid() {
		t.Fatal("Diamond frustum is not valid")
	}
}

func TestCreateDiamondFrustumWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateDiamondFrustumWithPlace(DiamondFrustumParams{
		TopDiag1:    10.0,
		TopDiag2:    7.5,
		BottomDiag1: 20.0,
		BottomDiag2: 15.0,
		Height:      12.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create diamond frustum with place")
	}
}

func TestCreateOffsetRectangularTable(t *testing.T) {
	shp := CreateOffsetRectangularTable(OffsetRectangularTableParams{
		TopLength:    15.0,
		TopWidth:     10.0,
		BottomLength: 20.0,
		BottomWidth:  12.0,
		Height:       8.0,
		XOffset:      2.0,
		YOffset:      1.5,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create offset rectangular table")
	}
	if !shp.IsValid() {
		t.Fatal("Offset rectangular table is not valid")
	}
}

func TestCreateOffsetRectangularTableWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateOffsetRectangularTableWithPlace(OffsetRectangularTableParams{
		TopLength:    15.0,
		TopWidth:     10.0,
		BottomLength: 20.0,
		BottomWidth:  12.0,
		Height:       8.0,
		XOffset:      2.0,
		YOffset:      1.5,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create offset rectangular table with place")
	}
}

func TestCreateCylinderShape(t *testing.T) {
	shp := CreateCylinderShape(CylinderShapeParams{
		Radius: 15,
		Height: 25,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cylinder")
	}
	if !shp.IsValid() {
		t.Fatal("Cylinder is not valid")
	}
}

func TestCreateCylinderShapeWithAngle(t *testing.T) {
	angle := math.Pi
	shp := CreateCylinderShape(CylinderShapeParams{
		Radius: 10,
		Height: 20,
		Angle:  &angle,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cylinder with angle")
	}
}

func TestCreateCylinderShapeWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateCylinderShapeWithPlace(CylinderShapeParams{
		Radius: 15,
		Height: 25,
	}, pos, dir, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cylinder with place")
	}
}

func TestCreateSharpBentCylinder(t *testing.T) {
	shp := CreateSharpBentCylinder(SharpBentCylinderParams{
		Radius:    5.0,
		Length:    70.0,
		BendAngle: float32(math.Pi / 4),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sharp bent cylinder")
	}
	if !shp.IsValid() {
		t.Fatal("Sharp bent cylinder is not valid")
	}
}

func TestCreateSharpBentCylinderWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateSharpBentCylinderWithPlace(SharpBentCylinderParams{
		Radius:    5.0,
		Length:    70.0,
		BendAngle: float32(math.Pi / 4),
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sharp bent cylinder with place")
	}
}
