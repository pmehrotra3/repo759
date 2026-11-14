#include <cstdio>  // std::printf
#include <cstdlib> // std::atoi: turns the text "1024" into the number 1024
#include <random>
#include <cuda_runtime.h>
#include "vscale.cuh"

int main(int argc, char **argv) {
    int n = std::atoi(argv[1]);

    float *hA = new float[n];
    float *hB = new float[n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist1(-10.0f, 10.0f);
    std::uniform_real_distribution<float> dist2(0.0f, 1.0f);

    for (int i = 0; i < n; i++) {
        hA[i] = dist1(gen);
        hB[i] = dist2(gen);
    }

    float *dA;
    float *dB;

    cudaMalloc((void **)&dA, n * sizeof(float));
    cudaMalloc((void **)&dB, n * sizeof(float));

    cudaMemcpy(dA, hA, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, n * sizeof(float), cudaMemcpyHostToDevice);

    int threadsPerBlock = (argc > 2) ? std::atoi(argv[2]) : 512;
    int numBlocks = (n + threadsPerBlock - 1) / threadsPerBlock;

    cudaEvent_t start;
    cudaEvent_t stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    vscale<<<1, threadsPerBlock>>>(dA, dB, 0); // untimed warm-up, n = 0 touches no data
    cudaDeviceSynchronize();

    cudaEventRecord(start);
    vscale<<<numBlocks, threadsPerBlock>>>(dA, dB, n);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms;
    cudaEventElapsedTime(&ms, start, stop);

    cudaMemcpy(hB, dB, n * sizeof(float), cudaMemcpyDeviceToHost);

    std::printf("%f\n", ms);        // time in ms
    std::printf("%f\n", hB[0]);     // first element
    std::printf("%f\n", hB[n - 1]); // last element

    cudaFree(dA);
    cudaFree(dB);
    delete[] hA;
    delete[] hB;
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}
