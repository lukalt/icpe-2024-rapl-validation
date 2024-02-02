#!/bin/bash
BENCHMARK="$1"
N_THREADS="$2"
source /opt/intel/oneapi/compiler/latest/env/vars.sh
source /opt/intel/oneapi/mkl/latest/env/vars.sh
OMP_NUM_THREADS="$N_THREADS" OMP_PLACES=cores OMP_PROC_BIND=spread numactl --cpunodebind=0 --membind=0 "/home/aw272604/rapl_validation/benchmarks/workloads/$BENCHMARK.exe"
