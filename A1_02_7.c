/* ============================================================================
Group No : A1
Team No : 02
Team Members : Rishika Sur (002311001025)
             : Vidhi Mantry (002311001043)
             : Prama Ray (002311001033)

Date : 19th September, 2025

Assignment : 7 - Deadlock Avoidance with Mutexes and Threads

Description :
This program demonstrates deadlock avoidance using pthreads and mutexes.
Three global totals (totalOne, totalTwo, totalThree) are initialized to 100000.
Each total is protected by its own mutex (mutexOne, mutexTwo, mutexThree).

Four threads are created:
- Th1: Subtracts a random value (≤ 10) from totalOne and adds it to
totalTwo or totalThree (randomly chosen).
- Th2: Subtracts a random value (≤ 20) from totalTwo and adds it to
totalOne or totalThree.
- Th3: Subtracts a random value (≤ 30) from totalThree and adds it to
totalOne or totalTwo.
- Th4: Displays totals and grand total, but only when they change.

Input Description:
- None (program runs indefinitely)

Output Description:
- Updated totals and grand total whenever values change
- Grand total always remains constant (= 300000)

Compilation:
gcc -pthread -o A1_02_7 A1_02_7.c

Execution:
./A1_02_7

Deadlock Avoidance Explanation:
- Deadlock occurs when multiple threads acquire locks in conflicting order.
Example:
Thread A: locks mutexOne → then waits for mutexTwo
Thread B: locks mutexTwo → then waits for mutexOne
→ Both threads are stuck forever (classic circular wait condition).

- To prevent this, all threads in this program always acquire mutexes in
the same strict order:
mutexOne → mutexTwo → mutexThree
and release them in the reverse order:
mutexThree → mutexTwo → mutexOne

- Because every thread follows the same global locking order,
circular wait cannot occur, and deadlock is avoided.

How Deadlock Could Have Occurred:
- If different threads locked mutexes in inconsistent order, circular wait
would be possible. For example:
Th1: locks mutexOne → tries for mutexTwo
Th2: locks mutexTwo → tries for mutexOne
- Both would block each other, creating a deadlock.

- Similarly, if one thread locks (mutexThree → mutexOne) while another
locks (mutexOne → mutexThree), neither could proceed.

- Hence, inconsistent mutex ordering is the root cause of deadlock.

Sample Output:
TotalOne = 175432 | TotalTwo = 69915 | TotalThree = 54653 | GrandTotal = 300000
TotalOne = 175436 | TotalTwo = 69911 | TotalThree = 54653 | GrandTotal = 300000
TotalOne = 175453 | TotalTwo = 69911 | TotalThree = 54636 | GrandTotal = 300000
TotalOne = 175456 | TotalTwo = 69911 | TotalThree = 54633 | GrandTotal = 300000
TotalOne = 175466 | TotalTwo = 69963 | TotalThree = 54571 | GrandTotal = 300000
TotalOne = 175482 | TotalTwo = 69963 | TotalThree = 54555 | GrandTotal = 300000
TotalOne = 175490 | TotalTwo = 69963 | TotalThree = 54547 | GrandTotal = 300000
TotalOne = 175499 | TotalTwo = 69954 | TotalThree = 54547 | GrandTotal = 300000
TotalOne = 175494 | TotalTwo = 69956 | TotalThree = 54550 | GrandTotal = 300000
TotalOne = 175494 | TotalTwo = 69937 | TotalThree = 54569 | GrandTotal = 300000
TotalOne = 175514 | TotalTwo = 69937 | TotalThree = 54549 | GrandTotal = 300000
TotalOne = 175514 | TotalTwo = 69974 | TotalThree = 54512 | GrandTotal = 300000
TotalOne = 175531 | TotalTwo = 69957 | TotalThree = 54512 | GrandTotal = 300000
TotalOne = 175531 | TotalTwo = 69953 | TotalThree = 54516 | GrandTotal = 300000
TotalOne = 175542 | TotalTwo = 69953 | TotalThree = 54505 | GrandTotal = 300000
TotalOne = 175542 | TotalTwo = 69964 | TotalThree = 54494 | GrandTotal = 300000
TotalOne = 175541 | TotalTwo = 69964 | TotalThree = 54495 | GrandTotal = 300000
TotalOne = 175547 | TotalTwo = 69958 | TotalThree = 54495 | GrandTotal = 300000
TotalOne = 175547 | TotalTwo = 69945 | TotalThree = 54508 | GrandTotal = 300000
TotalOne = 175542 | TotalTwo = 69945 | TotalThree = 54513 | GrandTotal = 300000
TotalOne = 175561 | TotalTwo = 69926 | TotalThree = 54513 | GrandTotal = 300000
TotalOne = 175574 | TotalTwo = 69878 | TotalThree = 54548 | GrandTotal = 300000
TotalOne = 175574 | TotalTwo = 69877 | TotalThree = 54549 | GrandTotal = 300000
TotalOne = 175591 | TotalTwo = 69823 | TotalThree = 54586 | GrandTotal = 300000
TotalOne = 175610 | TotalTwo = 69804 | TotalThree = 54586 | GrandTotal = 300000
TotalOne = 175610 | TotalTwo = 69802 | TotalThree = 54588 | GrandTotal = 300000
TotalOne = 175602 | TotalTwo = 69810 | TotalThree = 54588 | GrandTotal = 300000
TotalOne = 175607 | TotalTwo = 69805 | TotalThree = 54588 | GrandTotal = 300000
TotalOne = 175607 | TotalTwo = 69799 | TotalThree = 54594 | GrandTotal = 300000
TotalOne = 175599 | TotalTwo = 69799 | TotalThree = 54602 | GrandTotal = 300000
TotalOne = 175596 | TotalTwo = 69802 | TotalThree = 54602 | GrandTotal = 300000
TotalOne = 175588 | TotalTwo = 69810 | TotalThree = 54602 | GrandTotal = 300000
TotalOne = 175590 | TotalTwo = 69808 | TotalThree = 54602 | GrandTotal = 300000

============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Global totals
long totalOne = 100000;
long totalTwo = 100000;
long totalThree = 100000;

// Mutexes
pthread_mutex_t mutexOne = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexTwo = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexThree = PTHREAD_MUTEX_INITIALIZER;

// Lock mutexes in fixed order to avoid deadlock
void lockAllInOrder(pthread_mutex_t *m1, pthread_mutex_t *m2)
{
    if (m1 == &mutexOne || m2 == &mutexOne)
        pthread_mutex_lock(&mutexOne);
    if (m1 == &mutexTwo || m2 == &mutexTwo)
        pthread_mutex_lock(&mutexTwo);
    if (m1 == &mutexThree || m2 == &mutexThree)
        pthread_mutex_lock(&mutexThree);
}

// Unlock mutexes in reverse order
void unlockAllInOrder(pthread_mutex_t *m1, pthread_mutex_t *m2)
{
    if (m1 == &mutexThree || m2 == &mutexThree)
        pthread_mutex_unlock(&mutexThree);
    if (m1 == &mutexTwo || m2 == &mutexTwo)
        pthread_mutex_unlock(&mutexTwo);
    if (m1 == &mutexOne || m2 == &mutexOne)
        pthread_mutex_unlock(&mutexOne);
}

// Thread functions
void *threadTh1(void *arg)
{
    while (1)
    {
        int qty = rand() % 10 + 1;
        int choice = rand() % 2;

        pthread_mutex_t *first = &mutexOne;
        pthread_mutex_t *second = (choice == 0) ? &mutexTwo : &mutexThree;

        lockAllInOrder(first, second);

        totalOne -= qty;
        if (choice == 0)
            totalTwo += qty;
        else
            totalThree += qty;

        unlockAllInOrder(first, second);
    }
    return NULL;
}

void *threadTh2(void *arg)
{
    while (1)
    {
        int qty = rand() % 20 + 1;
        int choice = rand() % 2;

        pthread_mutex_t *first = &mutexTwo;
        pthread_mutex_t *second = (choice == 0) ? &mutexOne : &mutexThree;

        lockAllInOrder(first, second);

        totalTwo -= qty;
        if (choice == 0)
            totalOne += qty;
        else
            totalThree += qty;

        unlockAllInOrder(first, second);
    }
    return NULL;
}

void *threadTh3(void *arg)
{
    while (1)
    {
        int qty = rand() % 30 + 1;
        int choice = rand() % 2;

        pthread_mutex_t *first = &mutexThree;
        pthread_mutex_t *second = (choice == 0) ? &mutexOne : &mutexTwo;

        lockAllInOrder(first, second);

        totalThree -= qty;
        if (choice == 0)
            totalOne += qty;
        else
            totalTwo += qty;

        unlockAllInOrder(first, second);
    }
    return NULL;
}

void *threadTh4(void *arg)
{
    long lastOne = -1, lastTwo = -1, lastThree = -1; 
    while (1)
    {
        pthread_mutex_lock(&mutexOne);
        pthread_mutex_lock(&mutexTwo);
        pthread_mutex_lock(&mutexThree);

        long grandTotal = totalOne + totalTwo + totalThree;

        if (totalOne != lastOne || totalTwo != lastTwo || totalThree != lastThree)
        {
            printf("TotalOne = %ld | TotalTwo = %ld | TotalThree = %ld | GrandTotal = %ld\n",
                   totalOne, totalTwo, totalThree, grandTotal);

            lastOne = totalOne;
            lastTwo = totalTwo;
            lastThree = totalThree;
        }

        pthread_mutex_unlock(&mutexThree);
        pthread_mutex_unlock(&mutexTwo);
        pthread_mutex_unlock(&mutexOne);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t th1, th2, th3, th4;

    if (pthread_create(&th1, NULL, threadTh1, NULL) != 0)
    {
        perror("Failed to create Th1");
        exit(1);
    }
    if (pthread_create(&th2, NULL, threadTh2, NULL) != 0)
    {
        perror("Failed to create Th2");
        exit(1);
    }
    if (pthread_create(&th3, NULL, threadTh3, NULL) != 0)
    {
        perror("Failed to create Th3");
        exit(1);
    }
    if (pthread_create(&th4, NULL, threadTh4, NULL) != 0)
    {
        perror("Failed to create Th4");
        exit(1);
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);

    return 0;
}
