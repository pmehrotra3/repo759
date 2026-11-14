#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -t 0-00:20:00
#SBATCH -J task3
#SBATCH -o task3.out -e task3.err
#SBATCH -n 1
#SBATCH --gpus-per-task=1

cd $SLURM_SUBMIT_DIR
module load nvidia/cuda
nvcc task3.cu vscale.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task3

# Each line of task3_times.txt: threads_per_block n time_ms
rm -f task3_times.txt
for tpb in 512 16; do
    for p in $(seq 10 29); do
        n=$((2 ** p))
        ms=$(./task3 $n $tpb | head -n 1)
        echo "$tpb $n $ms" >> task3_times.txt
    done
done
