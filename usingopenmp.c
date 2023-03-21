#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1028
#define NUM_THREADS 1

int A[N][N], B[N][N], C[N][N];

int main() {
    int i, j, k;

    // initialize matrices A and B
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j;
        }
    }

    // multiply matrices A and B using OpenMP
    double start_time = omp_get_wtime();
    #pragma omp parallel for private(i,j,k) num_threads(NUM_THREADS)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end_time = omp_get_wtime();

    // print matrix C
    printf("Matrix C:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    
    // print time taken
    double time_taken = end_time - start_time;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
