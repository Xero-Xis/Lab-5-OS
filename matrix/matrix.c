#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int **matA;
int **matB;

int **matSumResult;
int **matDiffResult;
int **matProductResult;

int N;

void fillMatrix(int **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

void printMatrix(int **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

typedef struct {
    int row;
    int col;
} thread_args;

void* computeSum(void* args) {
    thread_args *arguments = (thread_args *)args;
    int row = arguments->row;
    int col = arguments->col;

    matSumResult[row][col] = matA[row][col] + matB[row][col];

    free(arguments);
    return NULL;
}

void* computeDiff(void* args) {
    thread_args *arguments = (thread_args *)args;
    int row = arguments->row;
    int col = arguments->col;

    matDiffResult[row][col] = matA[row][col] - matB[row][col];

    free(arguments);
    return NULL;
}

void* computeProduct(void* args) {
    thread_args *arguments = (thread_args *)args;
    int row = arguments->row;
    int col = arguments->col;

    matProductResult[row][col] = 0;
    for (int k = 0; k < N; k++) {
        matProductResult[row][col] += matA[row][k] * matB[k][col];
    }

    free(arguments);
    return NULL;
}

int main() {
    srand(time(0)); // Do Not Remove. Just ignore and continue below.

    // 0. Get the matrix size from the command line and assign it to N
    printf("Enter the matrix size N: ");
    scanf("%d", &N);

    // 1. Allocate memory for the matrices
    matA = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matA[i] = (int *)malloc(N * sizeof(int));
    }

    matB = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matB[i] = (int *)malloc(N * sizeof(int));
    }

    matSumResult = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matSumResult[i] = (int *)malloc(N * sizeof(int));
    }

    matDiffResult = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matDiffResult[i] = (int *)malloc(N * sizeof(int));
    }

    matProductResult = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matProductResult[i] = (int *)malloc(N * sizeof(int));
    }

    // 2. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);

    // 3. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);

    // 4. Create pthread_t objects for our threads.
    pthread_t threads[N * N];

    // 5.
