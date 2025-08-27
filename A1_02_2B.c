/*
Group No     : A1
Team No      : 02
Team Members : Rishika Sur (002311001025)
             : Vidhi Mantry (002311001043)
             : Prama Ray (002311001033)
             
Date: 7th August, 2025      
              
Assignment: IPC using Named Pipe (FIFO)

Description: 
Using the fork system call, create a Child Process.. Transfer 1GB file
from the Parent Process to Child Process using a FIFO. Now, transfer
the same file from the Child Process to the Parent Process using
another FIFO. Now, compare the two files (use cmp or diff command)
to make sure that the same file has returned back. Also, print the time
required to do this double transfer. Attach this output to the source file
as a comment.
To create FIFO, you can either use a shell command or a system call.
To create a large file you can use the relevant command.
Use ‘ls –l’ command to show the FIFO and the large file. Attach this
output to the source file as a comment.

Command: dd if=/dev/zero of=large_file.bin bs=1M count=1024
Output:
1024+0 records in
1024+0 records out
1073741824 bytes (1.1 GB, 1.0 GiB) copied, 0.319966 s, 3.4 GB/s

Command: gcc A1_02_2B.c -o A1_02_2B
         mkfifo fifo1 fifo2
         ls -l
Output:
total 3145832
-rw-r--r-- 1 rahul rahul      16864 Aug 27 15:16 A1_02_1A.sh
-rw-r--r-- 1 rahul rahul       4956 Aug 27 15:16 A1_02_1B.c
-rw-r--r-- 1 rahul rahul       2294 Aug 27 15:16 A1_02_2A.c
-rw-r--r-- 1 rahul rahul       9356 Aug 27 15:16 A1_02_2B.c
-rwxr-xr-x 1 rahul rahul      16968 Aug 27 15:40 A1_02_2B
-rw-r--r-- 1 rahul rahul       4327 Aug 27 15:16 A1_02_3.py
-rw-r--r-- 1 rahul rahul       8985 Aug 27 15:16 A1_02_4.c
-rw-r--r-- 1 rahul rahul 1073741824 Aug 27 15:40 child_received.bin
prw-r--r-- 1 rahul rahul          0 Aug 27 15:40 fifo1
prw-r--r-- 1 rahul rahul          0 Aug 27 15:40 fifo2
-rw-r--r-- 1 rahul rahul 1073741824 Aug 27 15:18 large_file.bin
-rw-r--r-- 1 rahul rahul 1073741824 Aug 27 15:40 parent_received.bin

Execution Command: ./A1_02_2B
Output:

Robust 1GB FIFO File Transfer Program
=====================================

Starting 1GB file transfer...
File info:
-rw-r--r-- 1 rahul rahul 1.0G Aug 27 15:18 large_file.bin

Step 1: Parent sends 1GB file to Child via fifo1
Parent: Sending 1GB file...
Child: Ready to receive 1GB file...
Transferring dataReceiving data.................... Done
 Done
Parent: Sent 1073741824 bytes (1024.00 MB)
Child: Received 1073741824 bytes (1024.00 MB)
Step 1 completed successfully

Step 2: Child sends 1GB file back to Parent via fifo2
Parent: Ready to receive 1GB file back...
Child: Sending 1GB file back...
Transferring dataReceiving data.................... Done
Child: Sent 1073741824 bytes back (1024.00 MB)
 Done
Parent: Received 1073741824 bytes back (1024.00 MB)
Step 2 completed successfully


Performance Results:
===================
Transfer time: 1.647 seconds
Data transferred: 2048 MB (1024MB x 2)
Average rate: 1243.8 MB/s

Final file verification:
-rw-r--r-- 1 rahul rahul 1.0G Aug 27 15:40 child_received.bin
-rw-r--r-- 1 rahul rahul 1.0G Aug 27 15:18 large_file.bin
-rw-r--r-- 1 rahul rahul 1.0G Aug 27 15:40 parent_received.bin

Now compare files manually using:
cmp large_file.bin parent_received.bin
If no output, files are identical.

Comparison Command : cmp large_file.bin parent_received.bin
Output : empty - This means files are identical
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 1048576
#define ORIGINAL_FILE "large_file.bin"
#define CHILD_FILE "child_received.bin"
#define FINAL_FILE "parent_received.bin"
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

// Function to send file through FIFO
long transfer_file_send(const char* src_file, const char* fifo_name) {
    FILE* src = fopen(src_file, "rb");
    if (!src) {
        perror("Cannot open source file");
        return -1;
    }
   
    int fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Cannot open FIFO for writing");
        fclose(src);
        return -1;
    }
   
    char buffer[BUFFER_SIZE];
    long total_sent = 0;
    size_t bytes_read;
    ssize_t bytes_written;
   
    printf("Transferring data");
    fflush(stdout);
   
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        size_t total_written = 0;
        while (total_written < bytes_read) {
            bytes_written = write(fifo_fd, buffer + total_written, bytes_read - total_written);
            if (bytes_written == -1) {
                perror("Error writing to FIFO");
                fclose(src);
                close(fifo_fd);
                return -1;
            }
            total_written += bytes_written;
        }
        total_sent += bytes_read;
       
        if (total_sent % (100 * 1024 * 1024) == 0) {
            printf(".");
            fflush(stdout);
        }
    }
   
    printf(" Done\n");
    fclose(src);
    close(fifo_fd);
    return total_sent;
}

// Function to receive file through FIFO
long transfer_file_receive(const char* dst_file, const char* fifo_name) {
    int fifo_fd = open(fifo_name, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Cannot open FIFO for reading");
        return -1;
    }
   
    FILE* dst = fopen(dst_file, "wb");
    if (!dst) {
        perror("Cannot open destination file");
        close(fifo_fd);
        return -1;
    }
   
    char buffer[BUFFER_SIZE];
    long total_received = 0;
    ssize_t bytes_read;
   
    printf("Receiving data");
    fflush(stdout);
   
    while ((bytes_read = read(fifo_fd, buffer, BUFFER_SIZE)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
            perror("Error writing to file");
            break;
        }
        total_received += bytes_read;
       
        if (total_received % (100 * 1024 * 1024) == 0) {
            printf(".");
            fflush(stdout);
        }
    }
   
    printf(" Done\n");
    fflush(dst);
    fsync(fileno(dst));
    fclose(dst);
    close(fifo_fd);
   
    return total_received;
}

int main() {
    pid_t pid;
    int status;
    long bytes_transferred;
    clock_t start_time, end_time;
   
    printf("Robust 1GB FIFO File Transfer Program\n");
    printf("=====================================\n\n");
   
    if (access(ORIGINAL_FILE, R_OK) != 0) {
        printf("Error: %s not found.\n", ORIGINAL_FILE);
        printf("Create with: dd if=/dev/zero of=%s bs=1M count=1024\n", ORIGINAL_FILE);
        return 1;
    }
   
    if (access(FIFO1, F_OK) != 0 || access(FIFO2, F_OK) != 0) {
        printf("Error: FIFOs not found.\n");
        printf("Create with: mkfifo %s %s\n", FIFO1, FIFO2);
        return 1;
    }
   
    printf("Starting 1GB file transfer...\n");
    printf("File info:\n");
    system("ls -lh large_file.bin");
    printf("\n");
   
    start_time = clock();
   
    printf("Step 1: Parent sends 1GB file to Child via %s\n", FIFO1);
   
    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }
   
    if (pid == 0) {
        printf("Child: Ready to receive 1GB file...\n");
        bytes_transferred = transfer_file_receive(CHILD_FILE, FIFO1);
        printf("Child: Received %ld bytes (%.2f MB)\n", bytes_transferred, bytes_transferred / (1024.0 * 1024.0));
        if (bytes_transferred == -1) exit(1);
        exit(0);
    } else {
        printf("Parent: Sending 1GB file...\n");
        bytes_transferred = transfer_file_send(ORIGINAL_FILE, FIFO1);
        printf("Parent: Sent %ld bytes (%.2f MB)\n", bytes_transferred, bytes_transferred / (1024.0 * 1024.0));
        wait(&status);
        if (WEXITSTATUS(status) != 0) {
            printf("Child process failed in step 1\n");
            return 1;
        }
        printf("Step 1 completed successfully\n\n");
    }
   
    sleep(2);
   
    printf("Step 2: Child sends 1GB file back to Parent via %s\n", FIFO2);
   
    pid = fork();
    if (pid == -1) {
        perror("Second fork failed");
        return 1;
    }
   
    if (pid == 0) {
        printf("Child: Sending 1GB file back...\n");
        bytes_transferred = transfer_file_send(CHILD_FILE, FIFO2);
        printf("Child: Sent %ld bytes back (%.2f MB)\n", bytes_transferred, bytes_transferred / (1024.0 * 1024.0));
        if (bytes_transferred == -1) exit(1);
        exit(0);
    } else {
        printf("Parent: Ready to receive 1GB file back...\n");
        bytes_transferred = transfer_file_receive(FINAL_FILE, FIFO2);
        printf("Parent: Received %ld bytes back (%.2f MB)\n", bytes_transferred, bytes_transferred / (1024.0 * 1024.0));
        wait(&status);
        if (WEXITSTATUS(status) != 0) {
            printf("Child process failed in step 2\n");
            return 1;
        }
        printf("Step 2 completed successfully\n\n");
    }
   
    end_time = clock();
    double elapsed = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
   
    printf("\nPerformance Results:\n");
    printf("===================\n");
    printf("Transfer time: %.3f seconds\n", elapsed);
    printf("Data transferred: 2048 MB (1024MB x 2)\n");
    printf("Average rate: %.1f MB/s\n", 2048.0 / elapsed);

    printf("\nFinal file verification:\n");
    system("ls -lh large_file.bin child_received.bin parent_received.bin");

    printf("\nNow compare files manually using:\n");
    printf("cmp large_file.bin parent_received.bin\n");
    printf("If no output, files are identical.\n");
   
    return 0;
}
