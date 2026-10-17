#include "matmul.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " n t\n";
        return 1;
    }

    const int n = std::stoi(argv[1]);
    const int t = std::stoi(argv[2]);

    if (n <= 0 || t < 1 || t > 20) {
        std::cerr << "n must be > 0 and t must be in [1, 20]\n";
        return 1;
    }

    // i) Create and fill the n x n matrices A and B
    float* A = new float[n * n];
    float* B = new float[n * n];
    float* C = new float[n * n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int i = 0; i < n * n; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    // ii) Compute C = AB with t threads
    omp_set_num_threads(t);

    auto start = std::chrono::steady_clock::now();
    mmul(A, B, C, n);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // iii) Print the first element of C
    std::cout << C[0] << "\n";

    // iv) Print the last element of C
    std::cout << C[n * n - 1] << "\n";

    // v) Print the time taken by mmul in milliseconds
    std::cout << elapsed.count() << "\n";

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
