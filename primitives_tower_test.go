package topo

import (
	"testing"
)

func TestCreatePoleTower(t *testing.T) {
	params := PoleTowerParams{
		Heights: []PoleTowerHeight{
			{Value: 18.0, BodyID: "body1", LegID: "leg1"},
		},
		Bodies: []PoleTowerBody{
			{
				ID:     "body1",
				Height: 30.0,
				Nodes: []PoleTowerNode{
					{ID: "n1", Position: NewPoint3([3]float64{0, 0, 0})},
					{ID: "n2", Position: NewPoint3([3]float64{1, 0, 0})},
					{ID: "n3", Position: NewPoint3([3]float64{0, 1, 0})},
					{ID: "n4", Position: NewPoint3([3]float64{1, 1, 0})},
				},
				Legs: []PoleTowerLeg{
					{
						ID: "leg1", CommonHeight: 10.0, SpecificHeight: 8.0,
						Nodes: []PoleTowerNode{
							{ID: "ln1", Position: NewPoint3([3]float64{0, 0, -10})},
							{ID: "ln2", Position: NewPoint3([3]float64{1, 0, -10})},
						},
					},
				},
			},
		},
		Members: []PoleTowerMember{
			{
				ID: "m1", StartNodeID: "n1", EndNodeID: "n2",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
			{
				ID: "m2", StartNodeID: "n2", EndNodeID: "n3",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
			{
				ID: "m3", StartNodeID: "n1", EndNodeID: "n3",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
			{
				ID: "m4", StartNodeID: "n2", EndNodeID: "n4",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
			{
				ID: "m5", StartNodeID: "n3", EndNodeID: "n4",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
		},
		Attachments: []PoleTowerAttachment{
			{Name: "ground_wire", Type: 1, Position: NewPoint3([3]float64{0.5, 0.5, 30})},
		},
	}
	shp := CreatePoleTower(params)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create pole tower")
	}
}

func TestCreatePoleTowerWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	params := PoleTowerParams{
		Heights: []PoleTowerHeight{
			{Value: 18.0, BodyID: "body1", LegID: "leg1"},
		},
		Bodies: []PoleTowerBody{
			{
				ID:     "body1",
				Height: 30.0,
				Nodes: []PoleTowerNode{
					{ID: "n1", Position: NewPoint3([3]float64{0, 0, 0})},
					{ID: "n2", Position: NewPoint3([3]float64{1, 0, 0})},
					{ID: "n3", Position: NewPoint3([3]float64{0, 1, 0})},
				},
				Legs: []PoleTowerLeg{
					{
						ID: "leg1", CommonHeight: 10.0, SpecificHeight: 8.0,
						Nodes: []PoleTowerNode{
							{ID: "ln1", Position: NewPoint3([3]float64{0, 0, -10})},
							{ID: "ln2", Position: NewPoint3([3]float64{1, 0, -10})},
						},
					},
				},
			},
		},
		Members: []PoleTowerMember{
			{
				ID: "m1", StartNodeID: "n1", EndNodeID: "n2",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
			{
				ID: "m2", StartNodeID: "n2", EndNodeID: "n3",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
			{
				ID: "m3", StartNodeID: "n1", EndNodeID: "n3",
				Type: 1, Specification: "L0.2x0.05", Material: "Q345",
				XDirection: NewDir3FromXYZ([3]float64{1, 0, 0}),
				YDirection: NewDir3FromXYZ([3]float64{0, 1, 0}),
			},
		},
	}
	shp := CreatePoleTowerWithPlace(params, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create pole tower with place")
	}
}
