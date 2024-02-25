#!/bin/bash
BENCHMARK="$1"
N_THREADS="$2"
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
source /opt/intel/oneapi/compiler/latest/env/vars.sh
source /opt/intel/oneapi/mkl/latest/env/vars.sh
OMP_NUM_THREADS="$N_THREADS" OMP_PLACES=cores OMP_PROC_BIND=spread numactl --cpunodebind=0 --membind=0 "$SCRIPT_DIR/$BENCHMARK.exe"
