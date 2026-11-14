#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:05:00
#SBATCH -J task1
#SBATCH -o task1.out -e task1.err
#SBATCH -n 1
#SBATCH --gpus-per-task=1

cd $SLURM_SUBMIT_DIR
module load nvidia/cuda
nvcc task1.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task1

./task1
