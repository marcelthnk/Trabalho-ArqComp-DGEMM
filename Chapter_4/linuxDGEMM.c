#define _POSIX_C_SOURCE 199309L

/* This is the Linux version of DGEMM*/
#include <stdlib.h>
#include <stdio.h>
#include <mm_malloc.h>
#include <immintrin.h>  // AVX
#define UNROLL 4

/* We will be using this library for time measurement of the DGEMM algorithm*/
#include <time.h>

void dgemm(int n, double* A, double* B, double* C) {
    for (int i = 0; i < n; i += UNROLL * 4) {
        for (int j = 0; j < n; ++j) {
            __m256d c[UNROLL];
            for (int r = 0; r < UNROLL; r++) {
                c[r] = _mm256_load_pd(C + i + r * 4 + j * n);
            }

            for (int k = 0; k < n; ++k) {
                __m256d b = _mm256_broadcast_sd(B + k + j * n);
                for (int r = 0; r < UNROLL; r++) {
                    __m256d a = _mm256_load_pd(A + i + r * 4 + k * n);
                    c[r] = _mm256_fmadd_pd(a, b, c[r]);
                }
            }

            for (int r = 0; r < UNROLL; r++) {
                _mm256_store_pd(C + i + r * 4 + j * n, c[r]);
            }
        }
    }
}

void initializer(int n, double* A, double* B){
    /* This function will initialize A and B with different random values and with the range of [0,9], the values are double type */

    /* Initializing a set seed, which means that the benchmarks will be done always with the same seed (same random numbers each time) */
    srand(1);

    for (int i = 0; i < n*n; ++i){
        int integer_value_for_A = rand()% 10;
        double double_value_for_A = (double)integer_value_for_A;

        int integer_value_for_B = rand()% 10;
        double double_value_for_B = (double)integer_value_for_B;
        
        A[i] = double_value_for_A;
        B[i] = double_value_for_B;
    }
}

int main(){
    /* Creating the size of the matrix, the sizes for this project are 1K, 2K, 4K and 8K(1024, 2048, 4096, 8192)*/
    int n = 8192; 

    /* Initializng each matrix */
    double* A = (double*)_mm_malloc(n * n * sizeof(double), 32);
    double* B = (double*)_mm_malloc(n * n * sizeof(double), 32);
    double* C = (double*)_mm_malloc(n * n * sizeof(double), 32);

    /* Verifying if the allocation was successful*/
    if (!A || !B || !C) {
        printf("Error allocating memory.\n");
        return 1;
    }

    /* Setting all values of C with zeroes, since it is the one that will keep the results from the dgemm*/
    for (int i = 0; i < n * n; i++)
        C[i] = 0.0;

    /* Initializing the matrices that were with thrash due to the malloc */
    initializer(n, A, B);

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    dgemm(n, A, B, C);

    clock_gettime(CLOCK_MONOTONIC, &end);

    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;

    if (nanoseconds < 0) {
        nanoseconds += 1000000000;
        seconds -= 1;
    }
  
    double dgemm_time = seconds + nanoseconds * 1e-9;

    printf("%d O3 %.9f\n", n, dgemm_time);
    
    _mm_free(A);
    _mm_free(B);
    _mm_free(C);
    /* Free memory after it was used */

    return 0;
}

