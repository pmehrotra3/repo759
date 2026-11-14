#include <cstdio>
#include <random>
#include <cuda_runtime.h>

__global__ void simpleKernel(int *dA, int a) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int result = a * threadIdx.x + blockIdx.x;
    dA[idx] = result; 
}

int main() {
    int hA[16];

    std::random_device rd;                          // seed source from the OS
    std::mt19937 gen(rd());                         // generator, seeded
    std::uniform_int_distribution<int> dist(1, 10); // range for a: 1 to 10, inclusive
    int a = dist(gen);                              // draw one random a

    int *dA;
    cudaMalloc((void **)&dA, 16 * sizeof(int));

    simpleKernel<<<2, 8>>>(dA, a);

    cudaMemcpy(hA, dA, 16 * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < 15; i++) {
        std::printf("%d ", hA[i]);
    }
    std::printf("%d\n", hA[15]);

    cudaFree(dA);

    return 0;
}
