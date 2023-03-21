#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1028
#define NUM_THREADS 1

int A[N][N], B[N][N], C[N][N];

void *worker(void *arg) {
    int tid = *(int *)arg;
    int i, j, k;

    for (i = tid * N / NUM_THREADS; i < (tid + 1) * N / NUM_THREADS; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    int i, j, tids[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    // initialize matrices A and B
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j;
        }
    }

    // create threads
    clock_t start = clock();
    for (i = 0; i < NUM_THREADS; i++) {
        tids[i] = i;
        pthread_create(&threads[i], NULL, worker, (void *)&tids[i]);
    }

    // join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();

    // print matrix C
    printf("Matrix C:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    
    // print time taken
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
