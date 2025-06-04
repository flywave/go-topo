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
		Diffuse: IfcColor{0.0, 102.0 / 255.0, 180.0 / 255.0},
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
		Name:         "IfcCurtainWall",
		Diffuse:      IfcColor{0.5, 0.5, 0.5},
		Transparency: 0.5,
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
		Diffuse: IfcColor{160.0 / 255.0, 150.0 / 255.0, 104.0 / 255.0},
	}

	defaultMaterials["IfcWallStandardCase"] = &IfcStyle{
		Name:    "IfcWallStandardCase",
		Diffuse: IfcColor{150.0 / 255.0, 150.0 / 255.0, 104.0 / 255.0},
	}

	defaultMaterials["IfcWall"] = &IfcStyle{
		Name:    "IfcWall",
		Diffuse: IfcColor{146.0 / 255.0, 72.0 / 255.0, 38.0 / 255.0},
	}

	defaultMaterials["IfcWindow"] = &IfcStyle{
		Name:         "IfcWindow",
		Diffuse:      IfcColor{0.2, 0.2, 0.8},
		Transparency: 0.3,
	}

	defaultMaterials["IfcDoor"] = &IfcStyle{
		Name:    "IfcDoor",
		Diffuse: IfcColor{0.637255, 0.603922, 0.670588},
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
		Name:    "IfcSpace",
		Diffuse: IfcColor{0.5, 0.4, 0.1},
	}

	defaultMaterials["IfcStairFlight"] = &IfcStyle{
		Name:    "IfcStairFlight",
		Diffuse: IfcColor{0.637255, 0.603922, 0.670588},
	}

	defaultMaterials["IfcFlowSegment"] = &IfcStyle{
		Name:    "IfcFlowSegment",
		Diffuse: IfcColor{0.6, 0.4, 0.5},
	}

	defaultMaterials["IfcFurnishingElement"] = &IfcStyle{
		Name:    "IfcFurnishingElement",
		Diffuse: IfcColor{205.0 / 255.0, 104.0 / 255.0, 57.0 / 255.0},
	}

	defaultMaterials["IfcBuildingElementProxy"] = &IfcStyle{
		Name:    "IfcBuildingElementProxy",
		Diffuse: IfcColor{0.0, 0.8, 0.5},
	}

	defaultMaterials["IfcProxy"] = &IfcStyle{
		Name:         "IfcProxy",
		Diffuse:      IfcColor{0.0, 0.8, 0.5},
		Transparency: 0.9,
	}

	defaultMaterials["IfcDistributionFlowElement"] = &IfcStyle{
		Name:    "IfcDistributionFlowElement",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
	}

	defaultMaterials["IfcPile"] = &IfcStyle{
		Name:    "IfcPile",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
	}

	defaultMaterials["IfcCovering"] = &IfcStyle{
		Name:    "IfcCovering",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
	}

	defaultMaterials["IfcTransportElement"] = &IfcStyle{
		Name:    "IfcTransportElement",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
	}

	defaultMaterials["IfcFlowController"] = &IfcStyle{
		Name:    "IfcFlowController",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
	}

	defaultMaterials["IfcFlowFitting"] = &IfcStyle{
		Name:    "IfcFlowFitting",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
	}

	defaultMaterials["IfcBuildingElementPart"] = &IfcStyle{
		Name:    "IfcBuildingElementPart",
		Diffuse: IfcColor{1.0, 0.5, 0.5},
	}

	defaultMaterials["IfcDistributionElement"] = &IfcStyle{
		Name:    "IfcDistributionElement",
		Diffuse: IfcColor{1.0, 0.5, 0.5},
	}

	defaultMaterials["IfcProduct"] = &IfcStyle{
		Name:    "IfcProduct",
		Diffuse: IfcColor{0.8470588235, 0.427450980392, 0.0},
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
