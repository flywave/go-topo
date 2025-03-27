package topo

import "testing"

func TestNewDxfReader(t *testing.T) {
	tests := []struct {
		name     string
		filename string
		wantNil  bool
	}{
		{
			name:     "Valid filename",
			filename: "tests/test.dxf",
			wantNil:  false,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got := NewDxfReader(tt.filename)
			if (got == nil) != tt.wantNil {
				t.Errorf("NewDxfReader() = %v, wantNil %v", got, tt.wantNil)
			}
			got.DoRead()
			if got.IsFailed() {
				t.Errorf("NewDxfReader() = %v, want no error", got.GetError())
			}
			layers := got.GetLayerNames()
			if len(layers) == 0 {
				t.Errorf("NewDxfReader() = %v, want layers", got)
			}
		})
	}
}
