#include <cstdio> 
#include <cuda_runtime.h>

__global__ void factorialKernel(){

    int a = threadIdx.x + 1; 
    int result = 1; 
    
    for (int i = 1; i <= a; i ++){
        result = result * i; 
    }

    std::printf("%d!=%d\n", a, result); 

}

int main(){

    factorialKernel<<<1, 8>>>(); 
    cudaDeviceSynchronize(); 
    return 0; 
}