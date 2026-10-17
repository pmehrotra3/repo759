#include "msort.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " n t ts\n";
        return 1;
    }

    const int n = std::stoi(argv[1]);
    const int t = std::stoi(argv[2]);
    const int ts = std::stoi(argv[3]);

    if (n <= 0 || ts <= 0 || t < 1 || t > 20) {
        std::cerr << "n must be > 0, ts must be > 0 and t must be in [1, 20]\n";
        return 1;
    }

    // i) Create and fill arr with n random ints in [-1000, 1000]
    int* arr = new int[n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    for (int i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }

    // ii) Sort arr in place with msort using t threads
    omp_set_num_threads(t);

    auto start = std::chrono::steady_clock::now();
    msort(arr, n, ts);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // iii) Print the first element of the sorted arr
    std::cout << arr[0] << "\n";

    // iv) Print the last element of the sorted arr
    std::cout << arr[n - 1] << "\n";

    // v) Print the time taken by msort in milliseconds
    std::cout << elapsed.count() << "\n";

    delete[] arr;

    return 0;
}
