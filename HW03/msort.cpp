#include "msort.h"
#include <omp.h>
#include <vector>

// Serial insertion sort with no recursion, used once a piece is below the threshold.
// Sorts arr[0, n) in place in ascending order.
void insertion_sort(int* arr, const std::size_t n){

    for (std::size_t i = 1; i < n; i++){

        int key = arr[i];           // element to place into the sorted part arr[0, i)
        std::size_t j = i;
        while (j>0 && arr[j-1] > key){
            arr[j] = arr[j-1];      // shift bigger elements one step right
            j --;
        }
        arr[j] = key;               // drop key into its spot
    }
}

// Merges the sorted halves arr[0, mid) and arr[mid, n) into one sorted arr
void merge(int* arr, const std::size_t mid, const std::size_t n){

    std::vector<int> temp(n);
    std::size_t i = 0;      // index into left half
    std::size_t j = mid;    // index into right half
    std::size_t k = 0;      // index into temp

    // take the smaller front element of the two halves each step
    while (i < mid && j < n){
        if (arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }

    // one half has run out, copy what is left of the other
    while (i < mid){
        temp[k++] = arr[i++];
    }
    while (j < n){
        temp[k++] = arr[j++];
    }

    // copy the merged result back into arr
    for (std::size_t x = 0; x < n; x++){
        arr[x] = temp[x];
    }
}

// Recursive merge sort on arr[0, n); each half is sorted as a separate OpenMP task
void recurse(int* arr, const std::size_t n, const std::size_t threshold){

    // small piece: sort serially (n < 2 also stops endless splitting when threshold is 1)
    if (n < threshold || n < 2){
        insertion_sort(arr, n);
    }
    else{
        // split in half, sort each half in parallel, then merge them
        std::size_t mid = n / 2;

        // left half arr[0, mid), any free thread can take this task
        #pragma omp task
        recurse(arr, mid, threshold);

        // right half arr[mid, n), any free thread can take this task
        #pragma omp task
        recurse(arr + mid, n - mid, threshold);

        // wait until both halves are sorted before merging
        #pragma omp taskwait
        merge(arr, mid, n);
    }
}

// Sorts arr[0, n) in place in ascending order
void msort(int* arr, const std::size_t n, const std::size_t threshold){

    // create the team of threads once; a single thread starts the recursion
    // and the other threads pick up the tasks it creates
    #pragma omp parallel
    #pragma omp single
    recurse(arr, n, threshold);
}
