#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:45:00
#SBATCH -J task4
#SBATCH -o task4.out -e task4.err
#SBATCH -c 8

cd $SLURM_SUBMIT_DIR
g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

N=1000
tEnd=100

# Each line of task4_times.txt: policy num_threads time_ms
rm -f task4_times.txt
for policy in static dynamic guided; do
    for t in $(seq 1 8); do
        ms=$(./task3 $N $tEnd $t $policy | sed 's/time: \(.*\)ms/\1/')
        echo "$policy $t $ms" >> task4_times.txt
    done
done
