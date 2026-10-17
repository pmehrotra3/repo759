#include "convolution.h"
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
    const int m = 3;

    if (n <= 0 || t < 1 || t > 20) {
        std::cerr << "n must be > 0 and t must be in [1, 20]\n";
        return 1;
    }

    // i) Create and fill the n x n image
    float* image = new float[n * n];
    float* output = new float[n * n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist1(-10.0f, 10.0f);

    for (int i = 0; i < n * n; i++) {
        image[i] = dist1(gen);
    }

    // ii) Create and fill the 3 x 3 mask
    float* mask = new float[m * m];

    std::uniform_real_distribution<float> dist2(-1.0f, 1.0f);

    for (int i = 0; i < m * m; i++) {
        mask[i] = dist2(gen);
    }

    // iii) Apply the mask to the image with t threads
    omp_set_num_threads(t);

    auto start = std::chrono::steady_clock::now();
    convolve(image, output, n, mask, m);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // iv) Print the first element of output
    std::cout << output[0] << "\n";

    // v) Print the last element of output
    std::cout << output[n * n - 1] << "\n";

    // vi) Print the time taken by convolve in milliseconds
    std::cout << elapsed.count() << "\n";

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}
