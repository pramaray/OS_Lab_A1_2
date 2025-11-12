/*
 =============================================================================
 Group No     : A1
 Team No      : 02
 Team Members : Rishika Sur (002311001025)
              : Vidhi Mantry (002311001043)
              : Prama Ray  (002311001033)

 Date         : 4 September 2025
 Assignment   : 5 - Threads, Synchronization & Shared Memory (SysV)

 Description  :
   - Main process creates System V shared memory (shmget/shmat).
   - Generates N random (X,Y) pairs where 0 <= X,Y < 10 and stores them in shm.
   - Creates 3 threads:
       Th1: computes A = X * Y
       Th2: computes B = 2*X + 2*Y + 1
       Th3: computes C = B / A  (if A==0, C is set to INFINITY)
   - For each row (pair), all three threads START together (barrier1),
     Th3 waits until A and B are written, computes C, then all three
     threads finish the row together (barrier2) before moving to next.
   - After all rows done, main prints the table and removes shm.

 Sample Input (CLI) :
   N  (number of random pairs)
   Example:  ./A1_02_5 5

 Sample Output :
   A formatted table:
     Pairs(X,Y) | A | B | C
     -----------------------
     (x, y) | A | B | C
     ...

 Compilation :
   gcc -pthread A1_02_5.c -o A1_02_5

 Execution :
   ./A1_02_5 8


 Notes :
   - Uses perror() for error reporting.
   - Cleans shm via shmctl(IPC_RMID) at the end.
   - Indentation is 4 spaces.

 System Output:
	------ Message Queues --------
	key        msqid      owner      perms      used-bytes   messages    

	------ Shared Memory Segments --------
	key        shmid      owner      perms      bytes      nattch     status      
	0x00000072 65536      be2342     444        1          0                       
	0xffffffff 1474561    be2348     666        2536       0                       
	0x55027210 1998850    be2333     600        388        1                       

	------ Semaphore Arrays --------
	key        semid      owner      perms      nsems     

 Program Output:
	Pairs(X,Y) | A | B | C
	-----------------------
	(0, 3) | 0 | 7 | inf
	(4, 5) | 20 | 19 | 0.950000
	(1, 1) | 1 | 5 | 5.000000
	(4, 1) | 4 | 11 | 2.750000
	(9, 0) | 0 | 19 | inf
	(7, 5) | 35 | 25 | 0.714286
	(2, 9) | 18 | 23 | 1.277778
	(7, 5) | 35 | 25 | 0.714286

 =============================================================================
*/

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int X, Y;
    long A, B;
    double C;
    int a_done, b_done, c_done;  // flags for synchronization checks
} Row;

typedef struct {
    int N;
    // Rows start immediately after this header in shared segment
} Header;

typedef struct {
    Header *hdr;
    Row    *rows;
    int     N;
} ShmView;

/* Global (process-local) synchronization objects */
static pthread_barrier_t start_barrier;  // all threads start same row together
static pthread_barrier_t end_barrier;    // all threads finish row together

/* Thread argument bundle */
typedef struct {
    ShmView shm;
} ThreadArgs;

/* ---------- Thread functions ---------- */

void *thread_A(void *arg) {
    ThreadArgs *ta = (ThreadArgs *)arg;
    Row *rows = ta->shm.rows;
    int N = ta->shm.N;
    int i;
    for (i = 0; i < N; i++) {
        pthread_barrier_wait(&start_barrier);  // start together

        rows[i].A = (long)rows[i].X * (long)rows[i].Y;
        rows[i].a_done = 1;

        pthread_barrier_wait(&end_barrier);    // finish row together
    }
    return NULL;
}

void *thread_B(void *arg) {
    ThreadArgs *ta = (ThreadArgs *)arg;
    Row *rows = ta->shm.rows;
    int N = ta->shm.N;
    int i;
    for (i = 0; i < N; i++) {
        pthread_barrier_wait(&start_barrier);  // start together

        rows[i].B = (long)(2 * rows[i].X + 2 * rows[i].Y + 1);
        rows[i].b_done = 1;

        pthread_barrier_wait(&end_barrier);    // finish row together
    }
    return NULL;
}

void *thread_C(void *arg) {
    ThreadArgs *ta = (ThreadArgs *)arg;
    Row *rows = ta->shm.rows;
    int N = ta->shm.N;
    int i;
    for (i = 0; i < N; i++) {
        pthread_barrier_wait(&start_barrier);  // start together

        /* Wait until A and B are computed for this row */
        while (!(rows[i].a_done && rows[i].b_done)) {
            /* Small sleep to avoid busy spinning */
            struct timespec ts = {0, 1000000}; // 1 ms
            nanosleep(&ts, NULL);
        }

        if (rows[i].A == 0) {
            rows[i].C = INFINITY;  // or NAN
        } else {
            rows[i].C = (double)rows[i].B / (double)rows[i].A;
        }
        rows[i].c_done = 1;

        pthread_barrier_wait(&end_barrier);    // finish row together
    }
    return NULL;
}

/* ---------- Utility: attach shared memory and view rows ---------- */
static int create_and_attach_shm(int N, ShmView *view, int *out_shmid) {
    /* Compute total shm size: header + N rows */
    size_t seg_size = sizeof(Header) + sizeof(Row) * (size_t)N;

    key_t key = ftok(".", 0x55);  // project id 0x55; ensure "." exists
    if (key == (key_t)-1) {
        perror("ftok");
        return -1;
    }

    int shmid = shmget(key, seg_size, IPC_CREAT | IPC_EXCL | 0600);
    if (shmid == -1) {
        perror("shmget");
        return -1;
    }

    void *base = shmat(shmid, NULL, 0);
    if (base == (void *)-1) {
        perror("shmat");
        /* attempt to remove segment if attach failed */
        shmctl(shmid, IPC_RMID, NULL);
        return -1;
    }

    Header *hdr = (Header *)base;
    Row *rows   = (Row *)((char *)base + sizeof(Header));
    hdr->N = N;

    view->hdr  = hdr;
    view->rows = rows;
    view->N    = N;
    *out_shmid = shmid;
    return 0;
}

/* ---------- Main ---------- */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int i;
    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Error: N must be positive.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));

    ShmView shm = {0};
    int shmid = -1;
    if (create_and_attach_shm(N, &shm, &shmid) != 0) {
        return EXIT_FAILURE;
    }

    /* Populate (X,Y) pairs and clear flags */
    for (i = 0; i < N; i++) {
        shm.rows[i].X = rand() % 10;
        shm.rows[i].Y = rand() % 10;
        shm.rows[i].A = 0;
        shm.rows[i].B = 0;
        shm.rows[i].C = 0.0;
        shm.rows[i].a_done = 0;
        shm.rows[i].b_done = 0;
        shm.rows[i].c_done = 0;
    }

    /* Init barriers: 3 threads must meet at each barrier */
    if (pthread_barrier_init(&start_barrier, NULL, 3) != 0) {
        perror("pthread_barrier_init(start_barrier)");
        shmctl(shmid, IPC_RMID, NULL);
        return EXIT_FAILURE;
    }
    if (pthread_barrier_init(&end_barrier, NULL, 3) != 0) {
        perror("pthread_barrier_init(end_barrier)");
        pthread_barrier_destroy(&start_barrier);
        shmctl(shmid, IPC_RMID, NULL);
        return EXIT_FAILURE;
    }

    pthread_t th1, th2, th3;
    ThreadArgs ta;
    ta.shm = shm;
    if (pthread_create(&th1, NULL, thread_A, &ta) != 0) {
        perror("pthread_create Th1");
        return EXIT_FAILURE;
    }
    if (pthread_create(&th2, NULL, thread_B, &ta) != 0) {
        perror("pthread_create Th2");
        return EXIT_FAILURE;
    }
    if (pthread_create(&th3, NULL, thread_C, &ta) != 0) {
        perror("pthread_create Th3");
        return EXIT_FAILURE;
    }
    system("ipcs");
    /* Wait for all threads to finish */
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    pthread_barrier_destroy(&start_barrier);
    pthread_barrier_destroy(&end_barrier);

    /* Print result table */
    printf("Pairs(X,Y) | A | B | C\n");
    printf("-----------------------\n");
    for (i = 0; i < N; i++) {
        printf("(%d, %d) | %ld | %ld | %f\n",
               shm.rows[i].X, shm.rows[i].Y,
               shm.rows[i].A, shm.rows[i].B, shm.rows[i].C);
    }

    /* Detach and remove shared memory */
    if (shmdt(shm.hdr) == -1) {
        perror("shmdt");
        // continue to try IPC_RMID anyway
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl(IPC_RMID)");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
