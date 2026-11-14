#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:05:00
#SBATCH -J task2
#SBATCH -o task2.out -e task2.err
#SBATCH -n 1
#SBATCH --gpus-per-task=1

cd $SLURM_SUBMIT_DIR
module load nvidia/cuda
nvcc task2.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task2

./task2
