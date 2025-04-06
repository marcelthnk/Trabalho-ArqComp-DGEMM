/* This is the Windows version of DGEMM*/
#include <stdlib.h>
#include <stdio.h>

/* We will be using this library for time measurement of the DGEMM algorithm*/
#include <windows.h>

void dgemm(int n, double* A, double* B, double* C){
    /* n is the number of columns and rows of the matrix, it is necessarily a square matrix */
    /* A, B and C are pointers to the matrices, they are double because their element's type is double  */ 
    /* C is the result of the multiplication, A and B are the ones being multiplied */
    /* The matrices are column-major, which means that the matrices are just a vector, going column by column. */
    /* [0 1] */
    /* [2 3] */
    /* Will be the vector [0, 2, 1, 3]*/
    
        /* This nested loop is for rows and columns of the C matrix */
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j){
            
                double cij = C[i+j*n]; /* cij = C[i][j], it gets the value (row i and column j) from the C matrix and puts it in the cij variable */
                                       /* For our purpose C is a zero matrix, which means that the value cij is necessarily 0 */
    
                for(int k = 0; k < n; k++ )
                    cij += A[i+k*n] * B[k+j*n]; /* cij += A[i][k]*B[k][j], this loop makes the multiplication in column-major format */
                C[i+j*n] = cij; /* C[i][j] = cij, the value of the multiplication is attributed to the C matrix (vector) */
            }
}

void initializer(int n, double* A, double* B){
    /* This function will initialize A and B with the same random values and with the range of [0,9], the values are double type */

    /* Initializing a set seed, which means that the benchmarks will be done always with the same seed (same random numbers each time) */
    srand(1);

    for (int i = 0; i < n*n; ++i){
        int integer_value = rand()% 10;
        double double_value = (double)integer_value;
        A[i] = double_value;
        B[i] = double_value;
    }
}

int main(){
    /* Creating the size of the matrix*/
    int n = 5; 

    /* Pointer to a place in memory where there is a sequence of doubles, the size of this sequence is defined by: */
    /* n*n*(the size of the double type defined in the architecture or compiler [some embedded compilers the size is different than 8 bytes]) */
    /* The function calloc initializes the memory with 0's, different of malloc, which is initialized with undefined values(thrash) */
    /* Since we want a zero matrix, the calloc function will be more useful */
    double* C = calloc(n*n, sizeof(double));

    /* Confirming if the alocation was successful, if it was not then the program will end*/
    if (C == NULL) {
        printf("Error to alocate memory in C.\n");
        return 1;
    }

    /* Creating the other matrices and checking if the creation worked */
    double* A = calloc(n*n, sizeof(double));
    if (A == NULL) {
        printf("Error to alocate memory in A.\n");
        return 1;
    }

    double* B = calloc(n*n, sizeof(double));
    if (B == NULL) {
        printf("Error to alocate memory in B.\n");
        return 1;
    }

    /* Initializing the matrices now */
    initializer(n, A, B);

    /* This part of the code is based on Windows */
    /* We will be using this Windows type because the function that we will use expects this type as an argument */
    LARGE_INTEGER freq; 
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double dgemm_time;

    /* This function gets the frequency of the high performance counter from Windows, which is a very precise counter (<1us)*/
    QueryPerformanceFrequency(&freq);

    /* Gets the current counter and attributes to start*/
    QueryPerformanceCounter(&start);

    dgemm(n, A, B, C);

    /* Gets the current counter and attributes to end*/
    QueryPerformanceCounter(&end);
    /* We calculate the time with this expression */
    /* Since LARGE_INTEGER is a struct, QuadPart is the part of the struct that keeps the 64 bits of the counter */
    /* So end.QuadPart we are retrieving the counter */
    /* The (double) is a type cast, since the counter contains a longlong int (64 bits) we transform the numerator in a double */
    /* This way we the compiler makes a precise division with decimals instead of integers */
    dgemm_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("The DGEMM algorithm with matrices the size of %d took: %.9f seconds\n", n, dgemm_time);
    
    free(A);
    free(B);
    free(C);
    /* Free memory after it was used */

    return 0;
}

