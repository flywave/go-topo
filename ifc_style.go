package topo

type IfcStyle struct {
	Name         string
	Diffuse      IfcColor
	Specular     IfcColor
	Transparency float64
	Specularity  float64
}

var defaultMaterials map[string]*IfcStyle
var defaultMaterial *IfcStyle

func init() {
	defaultMaterials = make(map[string]*IfcStyle)

	defaultMaterials["IfcSite"] = &IfcStyle{
		Name:    "IfcSite",
		Diffuse: IfcColor{0.75, 0.8, 0.65},
	}

	defaultMaterials["IfcBuilding"] = &IfcStyle{
		Name:    "IfcBuilding",
		Diffuse: IfcColor{0.8, 0.8, 0.8},
	}

	defaultMaterials["IfcColumn"] = &IfcStyle{
		Name:    "IfcColumn",
		Diffuse: IfcColor{0.6, 0.6, 0.6},
	}

	defaultMaterials["IfcFooting"] = &IfcStyle{
		Name:    "IfcFooting",
		Diffuse: IfcColor{0.5, 0.5, 0.5},
	}

	defaultMaterials["IfcBuildingStorey"] = &IfcStyle{
		Name:    "IfcBuildingStorey",
		Diffuse: IfcColor{0.7, 0.7, 0.7},
	}

	defaultMaterials["IfcCurtainWall"] = &IfcStyle{
		Name:    "IfcCurtainWall",
		Diffuse: IfcColor{0.85, 0.85, 0.85},
	}

	defaultMaterials["IfcDuctSegment"] = &IfcStyle{
		Name:    "IfcDuctSegment",
		Diffuse: IfcColor{0.7, 0.7, 0.9},
	}

	defaultMaterials["IfcPipeSegment"] = &IfcStyle{
		Name:    "IfcPipeSegment",
		Diffuse: IfcColor{0.7, 0.7, 0.9},
	}

	defaultMaterials["IfcStair"] = &IfcStyle{
		Name:    "IfcStair",
		Diffuse: IfcColor{0.7, 0.7, 0.7},
	}

	defaultMaterials["IfcRamp"] = &IfcStyle{
		Name:    "IfcRamp",
		Diffuse: IfcColor{0.7, 0.7, 0.7},
	}

	defaultMaterials["IfcFurniture"] = &IfcStyle{
		Name:    "IfcFurniture",
		Diffuse: IfcColor{0.8, 0.6, 0.4},
	}

	defaultMaterials["IfcFlowTerminal"] = &IfcStyle{
		Name:    "IfcFlowTerminal",
		Diffuse: IfcColor{0.8, 0.8, 0.8},
	}

	defaultMaterials["IfcRoof"] = &IfcStyle{
		Name:    "IfcRoof",
		Diffuse: IfcColor{0.5, 0.3, 0.2},
	}

	defaultMaterials["IfcSlab"] = &IfcStyle{
		Name:    "IfcSlab",
		Diffuse: IfcColor{0.4, 0.4, 0.4},
	}

	defaultMaterials["IfcWallStandardCase"] = &IfcStyle{
		Name:    "IfcWallStandardCase",
		Diffuse: IfcColor{0.9, 0.9, 0.9},
	}

	defaultMaterials["IfcWall"] = &IfcStyle{
		Name:    "IfcWall",
		Diffuse: IfcColor{0.9, 0.9, 0.9},
	}

	defaultMaterials["IfcWindow"] = &IfcStyle{
		Name:         "IfcWindow",
		Diffuse:      IfcColor{0.75, 0.8, 0.75},
		Transparency: 0.3,
	}

	defaultMaterials["IfcDoor"] = &IfcStyle{
		Name:    "IfcDoor",
		Diffuse: IfcColor{0.55, 0.3, 0.15},
	}

	defaultMaterials["IfcBeam"] = &IfcStyle{
		Name:    "IfcBeam",
		Diffuse: IfcColor{0.75, 0.7, 0.7},
	}

	defaultMaterials["IfcRailing"] = &IfcStyle{
		Name:    "IfcRailing",
		Diffuse: IfcColor{0.65, 0.6, 0.6},
	}

	defaultMaterials["IfcMember"] = &IfcStyle{
		Name:    "IfcMember",
		Diffuse: IfcColor{0.65, 0.6, 0.6},
	}

	defaultMaterials["IfcPlate"] = &IfcStyle{
		Name:    "IfcPlate",
		Diffuse: IfcColor{0.8, 0.8, 0.8},
	}

	defaultMaterials["IfcSpace"] = &IfcStyle{
		Name:         "IfcSpace",
		Diffuse:      IfcColor{0.65, 0.75, 0.8},
		Transparency: 0.8,
	}

	defaultMaterial = &IfcStyle{
		Name:    "DefaultMaterial",
		Diffuse: IfcColor{0.7, 0.7, 0.7},
	}
}

func GetIfcStyle(tp string) *IfcStyle {
	if mtl, ok := defaultMaterials[tp]; ok {
		return mtl
	}
	return defaultMaterial
}
