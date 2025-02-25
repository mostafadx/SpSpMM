#!/bin/bash

exe_path="./execution_files/"

export LD_LIBRARY_PATH="../shared/runtime/3rdparty/taco/build/lib"


# To make sure that all computaion execute on a single core 
export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1
export NUMEXPR_NUM_THREADS=1

function run() {

    # define the following two variables that TACO uses to compile the generated code to be same as baseline
    local opt_flags="-O3 -ffast-math -ftree-vectorize -mtune=native -std=c99"
    local compiler="clang"
    eval "export TACO_CFLAGS=\"${opt_flags}\" ; export TACO_CC=\"${compiler}\""

    make clean

    make generate_matrices

    make micro
    
    # for scipy
    export OPENBLAS_NUM_THREADS=1
    export MKL_NUM_THREADS=1
    export OMP_NUM_THREADS=1
    export NUMEXPR_NUM_THREADS=1

    taskset -c 1 python scipy_spspmm.py

    taskset -c 1 ${exe_path}optimized_baseline_spspmm.exe

    taskset -c 1 ${exe_path}taco_spspmm.exe

    taskset -c 1 ${exe_path}baseline_spspmm.exe

    # ${exe_path}parallelized_baseline_spspmm.exe

    make generate_plots
}

run