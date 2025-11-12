/*
==============================================================================================================
Group No     : A1
Team No      : 02
Team Members : Rishika Sur (002311001025)
             : Vidhi Mantry (002311001043)
             : Prama Ray (002311001033)
             
Date: 30th October, 2025      
             
Assignment 8T: IPC using Named Pipe (FIFO) - Triple Transfer

Description:
Using the fork system call, create two Child Processes - Child1 and Child2.
Transfer 1GB file from the Parent Process to the Child1 Process using a FIFO (FIFO1).
Child1 process transfers the same file to Child2 Process using another FIFO (FIFO2).
Child2 process transfers the file back to Parent process using FIFO3.
Print the time required for this triple transfer.
Compare the original and final files to ensure integrity.
NO intermediate file copies are allowed in Child1 or Child2 processes.

Command: dd if=/dev/zero of=large_file.bin bs=1M count=1024
Output:
1024+0 records in
1024+0 records out
1073741824 bytes (1.1 GB, 1.0 GiB) copied, 0.324293 s, 3.3 GB/s

Compile Command: gcc A1_02_8T.c -o A1_02_8T

Command: mkfifo fifo1 fifo2 fifo3
         ls -l
Output:
total 2479976
-rw-rw-r-- 1 adminpc adminpc 1073741824 Oct 30 12:21 large_file.bin
prw-rw-r-- 1 adminpc adminpc          0 Oct 30 12:22 fifo1
prw-rw-r-- 1 adminpc adminpc          0 Oct 30 12:22 fifo2
prw-rw-r-- 1 adminpc adminpc          0 Oct 30 12:22 fifo3
-rw-rw-r-- 1 adminpc adminpc      10195 Oct 30 12:21 A1_02_8T.c
-rw-rw-r-- 1 adminpc adminpc      17832 Oct 30 12:21 A1_02_8T

Execution Command: ./A1_02_8T
Output:

Triple FIFO File Transfer Program 
==========================================================

File info:
-rw-rw-r-- 1 adminpc adminpc 1.0G Oct 30 12:21 large_file.bin

Starting triple transfer...

Parent -> Child1 -> Child2 -> Parent

Transfer in progress....................
Triple transfer completed!

Performance Results:
===================
Total transfer time: 1.168 seconds
Data transferred: 3072 MB (1024MB x 3)
Average throughput: 2629.1 MB/s

Final file verification:
-rw-rw-r-- 1 adminpc adminpc 1.0G Oct 30 12:21 large_file.bin
-rw-rw-r-- 1 adminpc adminpc 1.0G Oct 30 12:23 parent_received.bin

Now compare files manually using:
cmp large_file.bin parent_received.bin
If no output, files are identical.

Comparison command: cmp large_file.bin parent_received.bin
Output:

Output is empty indicating files are identical.

===============================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define BUFFER_SIZE 1048576  // 1MB buffer for optimal performance
#define ORIGINAL_FILE "large_file.bin"
#define FINAL_FILE "parent_received.bin"
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define FIFO3 "fifo3"

// Function to relay data from input FIFO to output FIFO (no file storage)
long relay_data(const char* input_fifo, const char* output_fifo) {
    int in_fd = open(input_fifo, O_RDONLY);
    if (in_fd == -1) {
        perror("Cannot open input FIFO");
        return -1;
    }
   
    int out_fd = open(output_fifo, O_WRONLY);
    if (out_fd == -1) {
        perror("Cannot open output FIFO");
        close(in_fd);
        return -1;
    }
   
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) {
        perror("Memory allocation failed");
        close(in_fd);
        close(out_fd);
        return -1;
    }
   
    long total_relayed = 0;
    ssize_t bytes_read, bytes_written;
   
    while ((bytes_read = read(in_fd, buffer, BUFFER_SIZE)) > 0) {
        size_t total_written = 0;
        while (total_written < bytes_read) {
            bytes_written = write(out_fd, buffer + total_written,
                                  bytes_read - total_written);
            if (bytes_written == -1) {
                perror("Error writing to output FIFO");
                free(buffer);
                close(in_fd);
                close(out_fd);
                return -1;
            }
            total_written += bytes_written;
        }
        total_relayed += bytes_read;
    }
   
    free(buffer);
    close(in_fd);
    close(out_fd);
    return total_relayed;
}

// Function to send file to FIFO
long send_file(const char* filename, const char* fifo) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Cannot open source file");
        return -1;
    }
   
    int fifo_fd = open(fifo, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Cannot open FIFO for writing");
        fclose(file);
        return -1;
    }
   
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        close(fifo_fd);
        return -1;
    }
   
    long total_sent = 0;
    size_t bytes_read;
   
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        size_t total_written = 0;
        while (total_written < bytes_read) {
            ssize_t bytes_written = write(fifo_fd, buffer + total_written,
                                          bytes_read - total_written);
            if (bytes_written == -1) {
                perror("Error writing to FIFO");
                free(buffer);
                fclose(file);
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
   
    free(buffer);
    fclose(file);
    close(fifo_fd);
    return total_sent;
}

// Function to receive file from FIFO
long receive_file(const char* filename, const char* fifo) {
    int fifo_fd = open(fifo, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Cannot open FIFO for reading");
        return -1;
    }
   
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Cannot open destination file");
        close(fifo_fd);
        return -1;
    }
   
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) {
        perror("Memory allocation failed");
        close(fifo_fd);
        fclose(file);
        return -1;
    }
   
    long total_received = 0;
    ssize_t bytes_read;
   
    while ((bytes_read = read(fifo_fd, buffer, BUFFER_SIZE)) > 0) {
        if (fwrite(buffer, 1, bytes_read, file) != bytes_read) {
            perror("Error writing to file");
            break;
        }
        total_received += bytes_read;
       
        if (total_received % (100 * 1024 * 1024) == 0) {
            printf(".");
            fflush(stdout);
        }
    }
   
    free(buffer);
    fflush(file);
    fsync(fileno(file));
    fclose(file);
    close(fifo_fd);
   
    return total_received;
}

int main() {
    pid_t child1_pid, child2_pid;
    struct timeval start_time, end_time;
   
    printf("\nTriple FIFO File Transfer Program \n");
    printf("==========================================================\n\n");
   
    // Check if source file exists
    if (access(ORIGINAL_FILE, R_OK) != 0) {
        printf("Error: %s not found.\n", ORIGINAL_FILE);
        printf("Create with: dd if=/dev/zero of=%s bs=1M count=1024\n", ORIGINAL_FILE);
        return 1;
    }
   
    // Check if FIFOs exist
    if (access(FIFO1, F_OK) != 0 || access(FIFO2, F_OK) != 0 || access(FIFO3, F_OK) != 0) {
        printf("Error: FIFOs not found.\n");
        printf("Create with: mkfifo %s %s %s\n", FIFO1, FIFO2, FIFO3);
        return 1;
    }
   
    printf("File info:\n");
    system("ls -lh large_file.bin");
    printf("\n");
   
    printf("Starting triple transfer...\n");
    printf("\nParent -> Child1 -> Child2 -> Parent\n\n");
    printf("Transfer in progress");
    fflush(stdout);
   
    // Start timing
    gettimeofday(&start_time, NULL);
   
    // Create Child1
    child1_pid = fork();
    if (child1_pid == -1) {
        perror("Failed to create Child1");
        return 1;
    }
   
    if (child1_pid == 0) {
        // Child1 process: relay from FIFO1 to FIFO2
        long bytes = relay_data(FIFO1, FIFO2);
        if (bytes == -1) {
            exit(1);
        }
        exit(0);
    }
   
    // Create Child2
    child2_pid = fork();
    if (child2_pid == -1) {
        perror("Failed to create Child2");
        kill(child1_pid, SIGTERM);
        return 1;
    }
   
    if (child2_pid == 0) {
        // Child2 process: relay from FIFO2 to FIFO3
        long bytes = relay_data(FIFO2, FIFO3);
        if (bytes == -1) {
            exit(1);
        }
        exit(0);
    }
   
    // Parent process: Send to FIFO1 and receive from FIFO3
    pid_t receiver_pid = fork();
    if (receiver_pid == -1) {
        perror("Failed to create receiver process");
        return 1;
    }
   
    if (receiver_pid == 0) {
        // Receiver subprocess: receive from FIFO3
        long bytes = receive_file(FINAL_FILE, FIFO3);
        if (bytes == -1) {
            exit(1);
        }
        exit(0);
    } else {
        // Parent: send to FIFO1
        long bytes = send_file(ORIGINAL_FILE, FIFO1);
        if (bytes == -1) {
            return 1;
        }
    }
   
    // Wait for all processes
    int status;
    waitpid(receiver_pid, &status, 0);
    waitpid(child1_pid, &status, 0);
    waitpid(child2_pid, &status, 0);
   
    // End timing
    gettimeofday(&end_time, NULL);
   
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
   
    printf("\nTriple transfer completed!\n\n");
   
    printf("Performance Results:\n");
    printf("===================\n");
    printf("Total transfer time: %.3f seconds\n", elapsed);
    printf("Data transferred: 3072 MB (1024MB x 3)\n");
    printf("Average throughput: %.1f MB/s\n", 3072.0 / elapsed);
    
    printf("\nFinal file verification:\n");
    system("ls -lh large_file.bin parent_received.bin");

    printf("\nNow compare files manually using:\n");
    printf("cmp large_file.bin parent_received.bin\n");
    printf("If no output, files are identical.\n");

    return 0;
}
	

