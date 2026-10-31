#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:10:00
#SBATCH -J task2
#SBATCH -o task2.out -e task2.err
#SBATCH -c 8

cd $SLURM_SUBMIT_DIR
g++ task2.cpp -Wall -O3 -std=c++17 -o task2

./task2 1000 100
