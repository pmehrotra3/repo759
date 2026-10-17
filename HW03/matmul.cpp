#include "matmul.h"
#include "omp.h"

void mmul(const double* A, const double* B, double* C, const unsigned int n){

    #pragma omp parallel for
    for (size_t i = 0; i < n * n; i++) {
        C[i] = 0.0;
    }

    #pragma omp parallel for
    for (size_t i = 0; i < n; i++){
        for (size_t k = 0; k < n; k ++){
            for (size_t j = 0; j <n; j++){
                C[i*n + j] += A[i*n + k] * B[j + n*k];
            }

        }
    }
}