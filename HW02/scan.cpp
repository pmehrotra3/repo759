#include "scan.h"

// Performs an inclusive scan on input array arr and stores
// the result in the output array
// arr and output are arrays of n elements
void scan(const float *arr, float *output, std::size_t n){

    for (std::size_t i = 0; i < n; i++) {

        if (i == 0){
            output[i] = arr[i]; 
        }

        else{
            output[i] = output[i-1] + arr[i];
        }
    }
}