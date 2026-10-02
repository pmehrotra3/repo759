#include "scan.h"
#include <chrono>
#include <cstdlib>   // still needed for atoi
#include <iostream>
#include <random>

int main(int argc, char* argv[]){


    // i) 
    std::size_t n = std::atoi(argv[1]);
    float *input = new float[n];
    float *output = new float[n];

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f); 

    for (std::size_t i = 0 ; i < n; i++){
        input[i] = dist(gen); 
    }

    // ii) 
    auto start = std::chrono::steady_clock::now();
    scan(input, output, n);
    auto end = std::chrono::steady_clock::now(); 

    // iii)
    std::chrono::duration<double, std::milli> elapsed= end - start; 
    std::cout << elapsed.count() << "\n";


    // iv)
    std::cout << output[0] << "\n"; 

    // v)
    std::cout << output[n-1] << "\n"; 

    // vi)
    delete[] input; 
    delete[] output; 

    return 0; 

}
