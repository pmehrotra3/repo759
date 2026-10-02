#include "matmul.h"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const unsigned int n = 1024;

    double *A = new double[n * n];
    double *B = new double[n * n];
    double *C = new double[n * n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (std::size_t i = 0; i < n * n; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    std::vector<double> A_vec(A, A + n * n);
    std::vector<double> B_vec(B, B + n * n);

    std::cout << n << "\n";

    // mmul1
    auto start = std::chrono::steady_clock::now();
    mmul1(A, B, C, n);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << elapsed.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    // mmul2
    start = std::chrono::steady_clock::now();
    mmul2(A, B, C, n);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    // mmul3
    start = std::chrono::steady_clock::now();
    mmul3(A, B, C, n);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    // mmul4
    start = std::chrono::steady_clock::now();
    mmul4(A_vec, B_vec, C, n);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}