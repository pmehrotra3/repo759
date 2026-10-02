#include "convolution.h"

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m){

    long long N = n;
    long long M = m;
    long long half = (M - 1) / 2;


    for (std::size_t k = 0; k < n * n; k++){
        long long x = k / n;   // row
        long long y = k % n;   // column
        float sum = 0.0f;

        for (long long i = 0; i < M; i++) {
            for (long long j = 0; j < M; j++) {

                long long row = x + i - half;
                long long col = y + j - half;

                bool rowIn = (row >= 0 && row < N);
                bool colIn = (col >= 0 && col < N);

                float f;

                if (rowIn && colIn) {
                    f = image[row * N + col];   // inside the image
                } else if (rowIn || colIn) {
                    f = 1.0f;                   // edge: only one index out of range
                } else {
                    f = 0.0f;                   // corner: both out of range
                }

                sum += mask[i * M + j] * f;
            }
        }
        output[k] = sum;
    }
}
