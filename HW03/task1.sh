#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:5:00
#SBATCH -J task1
#SBATCH -o task1.out -e task1.err
#SBATCH -c 20

cd $SLURM_SUBMIT_DIR
g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp

# Each line of task1_times.txt: t time_ms
rm -f task1_times.txt
for t in $(seq 1 20); do
    ms=$(./task1 1024 $t | sed -n 3p)
    echo "$t $ms" >> task1_times.txt
done

python3 plot_task1.py
