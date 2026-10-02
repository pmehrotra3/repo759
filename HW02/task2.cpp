#include "convolution.h"
#include <chrono>
#include <cstdlib>   // still needed for atoi
#include <iostream>
#include <random>

int main(int argc, char* argv[]){


    // i) 
    std::size_t n = std::atoi(argv[1]);
    float *image = new float[n*n];

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> dist1(-10.0f, 10.0f); 

    for (std::size_t i = 0 ; i < n*n; i++){
        image[i] = dist1(gen); 
    }

    // ii) 
    std::size_t m = std::atoi(argv[2]);
    float *mask = new float[m*m];

    std::uniform_real_distribution<float> dist2(-1.0f, 1.0f); 

    for (std::size_t i = 0 ; i < m*m; i++){
        mask[i] = dist2(gen); 
    }

    // iii)
    float *convolve_output = new float[n*n];
    auto start = std::chrono::steady_clock::now();
    convolve(image, convolve_output, n, mask, m ); 
    auto end = std::chrono::steady_clock::now(); 

    // iv)
    std::chrono::duration<double, std::milli> elapsed = end - start; 
    std::cout << elapsed.count() << "\n"; 

    // v)
    std::cout << convolve_output[0] << "\n"; 

    // vi)
    std::cout << convolve_output[n*n-1] << "\n"; 

    // vii)
    delete[] image; 
    delete[] mask; 
    delete[] convolve_output; 

    return 0; 

}
