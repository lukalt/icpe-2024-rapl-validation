#!/bin/bash
SAMPLE_INTERVAL=5
SCRIPT_PATH="./benchmarks/workloads/run_dram.sh"

run_measurement() {
    echo "Running experiment $1"
    python3 measure-wrapper.py -I$SAMPLE_INTERVAL -N$1 $2
    echo "Experiment completed"
}

for run in {1}; do
    echo "Running repetition $run"
    run_measurement "addpd" "$SCRIPT_PATH addpd 1"
    sleep 5
    run_measurement "busywait" "$SCRIPT_PATH busywait 1"
    sleep 5
    run_measurement "idle" "$SCRIPT_PATH idle 1"
    sleep 5
    run_measurement "memorycopy" "$SCRIPT_PATH memorycopy 32"
    sleep 5
    run_measurement "memorywrite" "$SCRIPT_PATH memorywrite 32"
    sleep 5
    run_measurement "compute" "$SCRIPT_PATH compute 1"
    sleep 5
    run_measurement "matmul" "$SCRIPT_PATH matmul 1"
    sleep 5
    run_measurement "memoryread" "$SCRIPT_PATH memoryread 32"
    sleep 5
    run_measurement "mulpd" "$SCRIPT_PATH mulpd 1"
    sleep 5
    run_measurement "stream_add" "$SCRIPT_PATH stream_add 32"
    sleep 5
    run_measurement "stream_scale" "$SCRIPT_PATH stream_scale 32"
    sleep 5
    run_measurement "stream_triad" "$SCRIPT_PATH stream_triad 32"
    sleep 5
    run_measurement "stream_copy_32" "$SCRIPT_PATH stream_copy 32"
    sleep 5
    run_measurement "stream_copy_24" "$SCRIPT_PATH stream_copy 24"
    sleep 5
    run_measurement "stream_copy_16" "$SCRIPT_PATH stream_copy 16"
    sleep 5
    run_measurement "stream_copy_8" "$SCRIPT_PATH stream_copy 8"
    sleep 5
    run_measurement "stream_copy_4" "$SCRIPT_PATH stream_copy 4"
    sleep 5
    run_measurement "stream_copy_1" "$SCRIPT_PATH stream_copy 1"
    sleep 5
    run_measurement "stream_combined" "$SCRIPT_PATH stream_c"

done
