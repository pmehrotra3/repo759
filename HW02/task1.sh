#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:30:00
#SBATCH -J task1
#SBATCH -o task1.out -e task1.err
#SBATCH -c 1
#SBATCH --mem=16G

cd $SLURM_SUBMIT_DIR
g++ scan.cpp task1.cpp -Wall -O3 -std=c++17 -o task1

# Each line of task1_times.txt: n time_ms
rm -f task1_times.txt
for i in $(seq 10 30); do
    n=$((2**i))
    t=$(./task1 $n | head -n 1)
    echo "$n $t" >> task1_times.txt
done
