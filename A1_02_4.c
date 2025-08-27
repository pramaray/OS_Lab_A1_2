/*
 ============================================================================
 Group No     : A1
 Team No      : 02
 Team Members : Rishika Sur (002311001025)
              : Vidhi Mantry (002311001043)
              : Prama Ray (002311001033)
             
 Date: 21st August, 2025      

 Assignment  : 4 - Using mmap() and observing page faults

 Description :
     This program works with a large (~8GB) file and demonstrates page faults
     using the `mmap()` system call. Each loop iteration:
       1. Generate a random offset (0 to fileSize).
       2. Generate a random byte (0–255).
       3. Write it to the file with `pwrite()`.
       4. Map the file into memory with `mmap()`.
       5. Read back the value and verify correctness.
     Offsets are printed in hexadecimal.
     Run `sar -B 1` in another terminal to observe page faults.

 Notes:
     - Argument: filename (e.g., datafile.bin)
     - File must be created with: fallocate -l 8G datafile.bin
     - perror() is used for error reporting.

 Input Description: File name (command line argument)
 Output Description: Continuous offset and verification messages.
 
 File Preparation:
     fallocate -l 8G datafile.bin
   
 Compilation:
     gcc A1_02_4.c -o A1_02_4

 Execution:
     Terminal 1: sar -B 1
     Terminal 2: ./A1_02_4 datafile.bin

 Note: 
     Press Ctrl+C to stop execution for both the terminals.

 Sample Output (program):
    Verified successfully: 0x8c at offset: 0x14097fdce
    Verified successfully: 0x7 at offset: 0x146810570
    Verified successfully: 0x2c at offset: 0x7612da08
    Verified successfully: 0xb3 at offset: 0x65ae6f9d
    Verified successfully: 0x4d at offset: 0x105950f0b
    Verified successfully: 0xab at offset: 0x12bd53055
    Verified successfully: 0x6a at offset: 0x404e5233
    Verified successfully: 0x4d at offset: 0x2ea9ace7
    Verified successfully: 0xd5 at offset: 0x59a52d52
    Verified successfully: 0xd3 at offset: 0x6e5837ed
    Verified successfully: 0xa2 at offset: 0x11418ba3b
    Verified successfully: 0x12 at offset: 0x102d7689a


 Sample Output (sar -B 1):
    12:43:09 PM IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
    12:43:10 PM IST      0.00      0.00      6.00      0.00     60.00      0.00      0.00      0.00      0.00
    12:43:11 PM IST      0.00      0.00     16.00      0.00     23.00      0.00      0.00      0.00      0.00
    12:43:12 PM IST      0.00     28.00     51.00      0.00    217.00      0.00      0.00      0.00      0.00
    12:43:13 PM IST      0.00    140.00     47.00      0.00     72.00      0.00      0.00      0.00      0.00
    12:43:14 PM IST      0.00      0.00     87.00      0.00     55.00      0.00      0.00      0.00      0.00
    12:43:15 PM IST      0.00      8.00      0.00      0.00     67.00      0.00      0.00      0.00      0.00
    12:43:16 PM IST      0.00      0.00    207.00      0.00    422.00      0.00      0.00      0.00      0.00
    12:43:17 PM IST      0.00      0.00     91.00      0.00    375.00      0.00      0.00      0.00      0.00
    12:43:18 PM IST      0.00     28.00    122.00      0.00    219.00      0.00      0.00      0.00      0.00
    12:43:19 PM IST      0.00    180.00     11.00      0.00    103.00      0.00      0.00      0.00      0.00
    12:43:20 PM IST      0.00      0.00    210.00      0.00    919.00      0.00      0.00      0.00      0.00
    12:43:21 PM IST      0.00      8.00     62.00      0.00   4790.00      0.00      0.00      0.00      0.00
    12:43:22 PM IST      0.00      0.00      3.00      0.00     78.00      0.00      0.00      0.00      0.00
    12:43:23 PM IST      0.00     32.00      4.00      0.00    197.00      0.00      0.00      0.00      0.00
    12:43:24 PM IST      0.00      0.00     93.00      0.00    143.00      0.00      0.00      0.00      0.00
    12:43:25 PM IST      0.00    144.00     44.00      0.00     75.00      0.00      0.00      0.00      0.00
    12:43:26 PM IST     40.00     60.00   1439.00      1.00    303.00      0.00      0.00      0.00      0.00
    12:43:27 PM IST      0.00      8.00   2527.00      0.00    212.00      0.00      0.00      0.00      0.00
    12:43:28 PM IST      0.00      0.00     85.00      0.00    201.00      0.00      0.00      0.00      0.00
    12:43:29 PM IST      0.00      0.00     40.00      0.00     89.00      0.00      0.00      0.00      0.00
    12:43:30 PM IST      0.00      0.00    844.00      0.00   1252.00      0.00      0.00      0.00      0.00
    12:43:31 PM IST      0.00    596.00     18.00      0.00     36.00      0.00      0.00      0.00      0.00
    12:43:32 PM IST  25976.00    104.00   5441.00    198.00   4441.00      0.00      0.00      0.00      0.00
    12:43:33 PM IST      0.00      8.00     35.00      0.00    476.00      0.00      0.00      0.00      0.00
    12:43:34 PM IST      0.00      0.00     24.00      0.00     98.00      0.00      0.00      0.00      0.00
    12:43:35 PM IST      0.00      0.00      2.00      0.00     37.00      0.00      0.00      0.00      0.00
    12:43:36 PM IST      0.00      0.00    300.00      0.00    224.00      0.00      0.00      0.00      0.00
    12:43:37 PM IST      0.00    648.00    593.00      0.00    763.00      0.00      0.00      0.00      0.00
    12:43:38 PM IST      0.00      0.00    608.00      0.00   1087.00      0.00      0.00      0.00      0.00
    12:43:39 PM IST      0.00      8.00    296.00      0.00    464.00      0.00      0.00      0.00      0.00
    12:43:40 PM IST      0.00      0.00    662.00      0.00   3440.00      0.00      0.00      0.00      0.00
    12:43:41 PM IST      0.00      0.00    869.00      0.00   1034.00      0.00      0.00      0.00      0.00
    12:43:42 PM IST      0.00    868.00    522.00      0.00   4411.00      0.00      0.00      0.00      0.00
    12:43:43 PM IST      0.00      0.00    461.00      0.00    152.00      0.00      0.00      0.00      0.00
    12:43:44 PM IST      4.00      0.00    666.00      0.00    693.00      0.00      0.00      0.00      0.00
    12:43:45 PM IST      0.00      8.00    201.00      0.00    254.00      0.00      0.00      0.00      0.00
    12:43:46 PM IST      0.00      0.00    399.00      0.00    190.00      0.00      0.00      0.00      0.00
    12:43:47 PM IST      4.00    924.00    479.00      0.00    217.00      0.00      0.00      0.00      0.00
    12:43:48 PM IST      0.00      0.00    491.00      0.00    877.00      0.00      0.00      0.00      0.00
    12:43:49 PM IST      0.00      0.00    476.00      0.00    338.00      0.00      0.00      0.00      0.00


    ...
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <bigfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *fileName = argv[1];
    const long fileSize = 8L * 1024 * 1024 * 1024;  // 8 GB

    int fileDesc = open(fileName, O_RDWR);
    if (fileDesc == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));  // Seed random generator

    while (1) {
        // Random offset (0 to fileSize-1) and byte (0–255)
        off_t randomOffset = ((off_t)rand() << 32 | rand()) % fileSize;
        unsigned char randomValue = rand() % 256;

        // Write byte at offset
        if (pwrite(fileDesc, &randomValue, 1, randomOffset) != 1) {
            perror("pwrite");
            close(fileDesc);
            exit(EXIT_FAILURE);
        }

        // Map file into memory
        void *mapPtr = mmap(NULL, fileSize, PROT_READ, MAP_SHARED, fileDesc, 0);
        if (mapPtr == MAP_FAILED) {
            perror("mmap");
            close(fileDesc);
            exit(EXIT_FAILURE);
        }

        // Read back and verify
        unsigned char readValue = *((unsigned char *)mapPtr + randomOffset);
        if (randomValue != readValue) {
            fprintf(stderr, "Verification failed at offset: 0x%lx "
                            "(Wrote: 0x%x, Read: 0x%x)\n",
                    (unsigned long)randomOffset, randomValue, readValue);
            munmap(mapPtr, fileSize);
            close(fileDesc);
            exit(EXIT_FAILURE);
        } else {
            printf("Verified successfully: 0x%x at offset: 0x%lx\n",
                   randomValue, (unsigned long)randomOffset);
        }

        // Unmap memory and pause briefly
        if (munmap(mapPtr, fileSize) == -1) {
            perror("munmap");
            close(fileDesc);
            exit(EXIT_FAILURE);
        }
     
    }

    close(fileDesc);
    return 0;
}


