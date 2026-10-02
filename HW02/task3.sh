#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:10:00
#SBATCH -J task3
#SBATCH -o task3.out -e task3.err
#SBATCH -c 1

cd $SLURM_SUBMIT_DIR
g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3
./task3
