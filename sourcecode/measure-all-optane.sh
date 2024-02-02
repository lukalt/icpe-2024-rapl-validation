#!/bin/bash
SAMPLE_INTERVAL=5
SCRIPT_PATH="./benchmarks/workloads/run_optane.sh"
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
    run_measurement "memorycopy_4" "$SCRIPT_PATH memorycopy 4"
    sleep 5
    run_measurement "memorywrite_4" "$SCRIPT_PATH memorywrite 4"
    sleep 5
    run_measurement "compute" "$SCRIPT_PATH compute 1"
    sleep 5
    run_measurement "matmul" "$SCRIPT_PATH matmul 1"
    sleep 5
    run_measurement "memoryread_4" "$SCRIPT_PATH memoryread 4"
    sleep 5
    run_measurement "mulpd" "$SCRIPT_PATH mulpd 1"
    sleep 5
    run_measurement "stream_add_4" "$SCRIPT_PATH stream_add 4"
    sleep 5
    run_measurement "stream_scale_4" "$SCRIPT_PATH stream_scale 4"
    sleep 5
    run_measurement "stream_triad_4" "$SCRIPT_PATH stream_triad 4"
    sleep 5
    run_measurement "stream_copy_4" "$SCRIPT_PATH stream_copy 4"
    sleep 5
    run_measurement "stream_copy_2" "$SCRIPT_PATH stream_copy 2"
    sleep 5
    run_measurement "stream_copy_1" "$SCRIPT_PATH stream_copy 1"
    sleep 5
    run_measurement "stream_combined_4" "$SCRIPT_PATH stream_c 4"

done
