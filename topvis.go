package topovis

/*
#include <stdlib.h>
#include "topovis_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include -I ./include/linux -I ./
#cgo darwin CXXFLAGS: -I ./include -I ./include/darwin -I ./
#cgo windows CXXFLAGS:  -I ./include -I ./include/windows -I ./
#cgo linux LDFLAGS: -L ./lib/linux_amd64 -lfreetype
#cgo darwin LDFLAGS: -L ./lib/darwin_amd64 -lfreetype 
#cgo windows LDFLAGS: -L ./lib/windows_amd64 -lfreetype
*/
import "C"
