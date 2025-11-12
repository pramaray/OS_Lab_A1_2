/* ============================================================================
Group No     : A1
Team No      : 02
Team Members : Rishika Sur (002311001025)
             : Vidhi Mantry (002311001043)
             : Prama Ray (002311001033)

Date         : 11th September, 2025

Assignment   : 6 - Parallel Matrix Multiplication using Pthreads

Description  :
    This program performs matrix multiplication between two large square matrices
    using pthreads for parallel computation. Matrices are initialized with random
    unsigned integers modulo a given value (mod).
   
    It measures the time taken for matrix multiplication (excluding matrix initialization).
    CPU and process usage can be checked with `ps` and `cpustat` commands.
   
Input:
    - dim (int)         : Size of square matrices (e.g. 3000)
    - numThreads (int)  : Number of threads to use
    - mod (int)         : Value to mod the matrix entries with
    - printSwitch (int) : 1 to print matrices, 0 otherwise

Output:
    - Time taken to multiply matrices
    - (Optional) Matrix A, B, and C if printSwitch is 1

Compilation:
    gcc -o A1_02_6 A1_02_6.c -lpthread

Execution:
    ./A1_02_6 <dim> <numThreads> <mod> <printSwitch>

Timing Measurements:
    Dimension: 3000, Mod: 1000

    Threads: 1  →  136.6178 seconds
    Threads: 2  →  70.2771 seconds
    Threads: 4  →  35.5311 seconds
    Threads: 8  →  23.4053 seconds

Process Info (sample):
    ps -eLf | grep ./A1_02_6

CPU Utilisation:
    cpustat

Sample Output:
    
    Command : ./A1_02_6 3000 1 100 0
    Matrix multiplication completed in 136.6178 seconds with 1 threads.
    
    CPU Utilisation : cpustat

    %CPU   %USR   %SYS     PID S  CPU    Time Task
    100.00 100.00   0.00   11754 S    4  45.12s ./A1_02_06
    6.00   6.00   0.00    1686 S    4   2.12m /usr/bin/gnome-shell
    4.00   3.00   1.00    8698 S   10   1.25m /usr/share/code/code
    4.00   3.00   1.00    8671 S    1  35.58s /usr/share/code/code
    4.00   3.00   1.00    1556 S    6   1.31m /usr/lib/xorg/Xorg
    3.00   3.00   0.00    4432 S    3   1.04m /usr/libexec/gnome-terminal-server
    1.00   0.00   1.00    1043 S    7  55.14s /usr/sbin/mysqld

    Threads Creation : ps -eLf | grep ./A1_02_6

    adminpc    11754    4440   11754  0    2 13:14 pts/0    00:00:00 ./A1_02_06 3000 1 100 0
    adminpc    11754    4440   11755 98    2 13:14 pts/0    00:00:25 ./A1_02_06 3000 1 100 0
    adminpc    11804    6905   11804  0    1 13:14 pts/2    00:00:00 grep --color=auto ./A1_02_06

    Command : ./A1_02_6 3000 2 100 0
    Matrix multiplication completed in 70.2771 seconds with 2 threads.

    CPU Utilisation : cpustat

    %CPU   %USR   %SYS     PID S  CPU    Time Task
    200.00 200.00   0.00   11606 S    7  45.21s ./A1_02_06
    6.00   5.00   1.00    8698 S    4   1.24m /usr/share/code/code
    6.00   4.00   2.00    8671 S   10  34.63s /usr/share/code/code
    4.00   4.00   0.00    1686 S    5   2.10m /usr/bin/gnome-shell
    3.00   1.00   2.00    1556 S   10   1.30m /usr/lib/xorg/Xorg
    1.00   1.00   0.00    8728 S    6   9.96s /proc/self/exe
    1.00   1.00   0.00    1043 S    7  54.62s /usr/sbin/mysqld
    1.00   1.00   0.00    8627 S    0  13.05s /usr/share/code/code

    Threads Creation : ps -eLf | grep ./A1_02_6

    adminpc    11606    4440   11606  0    3 13:13 pts/0    00:00:00 ./A1_02_06 3000 2 100 0
    adminpc    11606    4440   11607 99    3 13:13 pts/0    00:00:09 ./A1_02_06 3000 2 100 0
    adminpc    11606    4440   11608 99    3 13:13 pts/0    00:00:09 ./A1_02_06 3000 2 100 0
    adminpc    11614    6905   11614  0    1 13:13 pts/2    00:00:00 grep --color=auto ./A1_02_06

    Command : ./A1_02_6 3000 4 100 0
    Matrix multiplication completed in 35.5311 seconds with 4 threads.

    CPU Utilisation : cpustat

    %CPU   %USR   %SYS     PID S  CPU    Time Task
    400.00 400.00   0.00   11471 S    8   2.10m ./A1_02_06
    35.00  35.00   0.00    8698 S    5   1.17m /usr/share/code/code
    6.00   4.00   2.00    8671 S    8  31.67s /usr/share/code/code
    6.00   4.00   2.00    1686 S   11   2.07m /usr/bin/gnome-shell
    4.00   3.00   1.00    1556 S    9   1.27m /usr/lib/xorg/Xorg
    2.00   2.00   0.00    8728 S    0   9.33s /proc/self/exe
    2.00   1.00   1.00    8627 S    9  12.31s /usr/share/code/code
    1.00   0.00   1.00    1043 S    7  54.05s /usr/sbin/mysqld
    1.00   1.00   0.00    1868 S    5   3.59s /usr/libexec/gsd-media-keys
    1.00   1.00   0.00      14 I    0   4.07s [rcu_sched]

    Threads Creation : ps -eLf | grep ./A1_02_6

    adminpc    11471    4440   11471  0    5 13:11 pts/0    00:00:00 ./A1_02_06 3000 4 100 0
    adminpc    11471    4440   11472 99    5 13:11 pts/0    00:00:12 ./A1_02_06 3000 4 100 0
    adminpc    11471    4440   11473 99    5 13:11 pts/0    00:00:12 ./A1_02_06 3000 4 100 0
    adminpc    11471    4440   11474 99    5 13:11 pts/0    00:00:12 ./A1_02_06 3000 4 100 0
    adminpc    11471    4440   11475 99    5 13:11 pts/0    00:00:12 ./A1_02_06 3000 4 100 0
    adminpc    11483    6905   11483  0    1 13:11 pts/2    00:00:00 grep --color=auto ./A1_02_06

    Command : ./A1_02_6 3000 8 100 0
    Matrix multiplication completed in 23.4053 seconds with 8 threads.
    
    CPU Utilisation : cpustat

    %CPU   %USR   %SYS     PID S  CPU    Time Task
    800.00 800.00   0.00   11288 S    6   1.57m ./A1_02_06
    4.00   2.00   2.00    1686 S    7   2.01m /usr/bin/gnome-shell
    3.00   3.00   0.00    1556 S    9   1.24m /usr/lib/xorg/Xorg
    3.00   2.00   1.00    4432 S    3   1.00m /usr/libexec/gnome-terminal-server
    1.00   1.00   0.00    4024 S    7   1.13m /usr/lib/firefox/firefox

    Threads Creation : ps -eLf | grep ./A1_02_6

    adminpc    11288    4440   11288  0    9 13:09 pts/0    00:00:00 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11289 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11290 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11291 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11292 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11293 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11294 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11295 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11288    4440   11296 98    9 13:09 pts/0    00:00:09 ./A1_02_06 3000 8 100 0
    adminpc    11302    6905   11302  0    1 13:09 pts/2    00:00:00 grep --color=auto ./A1_02_06



============================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define MAX_DIM 3000

typedef struct {
    int startRow, endRow, dim;
    int **matrixA;
    int **matrixB;
    int **resultMatrix;
} ThreadData;

int **initMatrix(int dim, int mod) {
    int **matrix = (int **)malloc(dim * sizeof(int *));
    for (int i = 0; i < dim; i++) {
        matrix[i] = (int *)malloc(dim * sizeof(int));
        for (int j = 0; j < dim; j++) {
            matrix[i][j] = rand() % mod;
        }
    }
    return matrix;
}

void *multiplyMatrix(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start = data->startRow;
    int end = data->endRow;
    int dim = data->dim;
    int **A = data->matrixA;
    int **B = data->matrixB;
    int **C = data->resultMatrix;

    int i, j, k; // loop variables declared outside
    for (i = start; i < end; i++) {
        for (j = 0; j < dim; j++) {
            C[i][j] = 0;
            for (k = 0; k < dim; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: ./A1_02_6 <dim> <numThreads> <mod> <printSwitch>\n");
        return 1;
    }

    int dim = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    int mod = atoi(argv[3]);
    int printSwitch = atoi(argv[4]);

    srand(time(NULL));  // <-- Initialize random seed to generate different matrices

    // Initialize matrices A, B, and result matrix
    int **matrixA = initMatrix(dim, mod);
    int **matrixB = initMatrix(dim, mod);
    int **resultMatrix = (int **)malloc(dim * sizeof(int *));
    int i, j;
    for (i = 0; i < dim; i++) {
        resultMatrix[i] = (int *)malloc(dim * sizeof(int));
    }

    pthread_t *threads = (pthread_t *)malloc(numThreads * sizeof(pthread_t));
    ThreadData *threadData = (ThreadData *)malloc(numThreads * sizeof(ThreadData));

    // Divide the work equally among the threads
    int chunkSize = dim / numThreads;
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    // Create threads for matrix multiplication
    for (i = 0; i < numThreads; i++) {
        threadData[i].startRow = i * chunkSize;
        threadData[i].endRow = (i == numThreads - 1) ? dim : (i + 1) * chunkSize;
        threadData[i].dim = dim;
        threadData[i].matrixA = matrixA;
        threadData[i].matrixB = matrixB;
        threadData[i].resultMatrix = resultMatrix;

        pthread_create(&threads[i], NULL, multiplyMatrix, (void *)&threadData[i]);
    }

    // Join all threads
    for (i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&endTime, NULL);

    // Calculate elapsed time
    double elapsedTime = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("Matrix multiplication completed in %.4f seconds with %d threads.\n", elapsedTime, numThreads);

    // Optionally print matrices (truncated output)
    if (printSwitch == 1) {
        printf("Matrix A:\n");
        int show = (dim < 10 ? dim : 10);
        for (i = 0; i < show; i++) {
            for (j = 0; j < show; j++) {
                printf("%d ", matrixA[i][j]);
                if (j == 9) { printf("..."); break; }
            }
            printf("\n");
            if (i == 9) { printf("...\n"); break; }
        }

        printf("Matrix B:\n");
        for (i = 0; i < show; i++) {
            for (j = 0; j < show; j++) {
                printf("%d ", matrixB[i][j]);
                if (j == 9) { printf("..."); break; }
            }
            printf("\n");
            if (i == 9) { printf("...\n"); break; }
        }

        printf("Result Matrix C:\n");
        for (i = 0; i < show; i++) {
            for (j = 0; j < show; j++) {
                printf("%d ", resultMatrix[i][j]);
                if (j == 9) { printf("..."); break; }
            }
            printf("\n");
            if (i == 9) { printf("...\n"); break; }
        }
    }

    // Free allocated memory
    for (i = 0; i < dim; i++) {
        free(matrixA[i]);
        free(matrixB[i]);
        free(resultMatrix[i]);
    }
    free(matrixA);
    free(matrixB);
    free(resultMatrix);
    free(threads);
    free(threadData);

    return 0;
}


