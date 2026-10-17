#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:5:00
#SBATCH -J task2
#SBATCH -o task2.out -e task2.err
#SBATCH -c 20

cd $SLURM_SUBMIT_DIR
g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp

# Each line of task2_times.txt: t time_ms
rm -f task2_times.txt
for t in $(seq 1 20); do
    ms=$(./task2 1024 $t | sed -n 3p)
    echo "$t $ms" >> task2_times.txt
done

python3 plot_task2.py
