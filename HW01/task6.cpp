#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc < 2){
        printf("Need to enter atleast one argument.\n"); 
        exit(1); 
    }

    int input = atoi(argv[1]); 

    for (int i = 0; i < input; i++){
        printf("%d ", i); 
    }

    printf("%d\n", input); 

    for (int i = 0; i < input; i++){
        std::cout << input - i << " ";
    }

     std::cout << "0\n";

     return 0; 

}