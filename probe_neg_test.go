package topo

import (
	"fmt"
	"testing"
)

func TestProbeNeg(t *testing.T) {
	p := TunnelCompartmentPartitionParams{Width: -120, Thickness: -18}
	err := p.Validate()
	fmt.Printf("validate err: %v\n", err)
	sh := CreateTunnelCompartmentPartition(p)
	fmt.Printf("shape: nil=%v null=%v valid=%v\n", sh == nil, sh != nil && sh.IsNull(), sh != nil && sh.IsValid())
}
