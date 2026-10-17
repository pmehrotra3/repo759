#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:10:00
#SBATCH -J task3
#SBATCH -o task3.out -e task3.err
#SBATCH -c 20

cd $SLURM_SUBMIT_DIR
g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

n=1000000

# Sweep 1: t = 8, ts = 2^1 .. 2^10
# Each line of task3_ts_times.txt: ts time_ms
rm -f task3_ts_times.txt
for i in $(seq 1 10); do
    ts=$((2**i))
    ms=$(./task3 $n 8 $ts | sed -n 3p)
    echo "$ts $ms" >> task3_ts_times.txt
done

# Pick the ts with the smallest time
best_ts=$(sort -k2 -g task3_ts_times.txt | head -n 1 | cut -d' ' -f1)

# Sweep 2: ts = best_ts, t = 1 .. 20
# Each line of task3_t_times.txt: t time_ms
rm -f task3_t_times.txt
for t in $(seq 1 20); do
    ms=$(./task3 $n $t $best_ts | sed -n 3p)
    echo "$t $ms" >> task3_t_times.txt
done

python3 plot_task3.py $best_ts
