/*
 ============================================================================
 Group No     : A1
 Team No      : 02
 Team Members : Rishika Sur (002311001025)
              : Vidhi Mantry (002311001043)
              : Prama Ray (002311001033)
              
 Date: 7th August, 2025       
              
 Assignment  : 2A - Signal Handling using signal() system call
 
 Description :
     This program sets up a signal handler to catch SIGINT using the signal()
     system call. When the user presses Ctrl+C, instead of terminating, the
     program prints "Ha Ha, Not Stopping".

     The program uses perror() to handle and report any errors during the
     signal() system call.

 Note:
     - Command-line arguments are handled.
     - Warning-free compilation.
     - Program uses proper indentation and formatting.
     
 Input  : No input required 
 Output : On SIGINT (Ctrl+C), prints "Ha Ha, Not Stopping"                

 Compilation :
     gcc A1_02_2A.c -o A1_02_2A

 Execution :
     ./A1_02_2A
     
 Sample Output: Program running, Press Ctrl+C to test SIGINT handling.
                ^CHa Ha, Not Stopping
                Program running, Press Ctrl+C to test SIGINT handling.
                ^CHa Ha, Not Stopping
                Program running, Press Ctrl+C to test SIGINT handling.
                ^CHa Ha, Not Stopping
     
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
 * @brief Signal handler for SIGINT
 * @param signum Signal number (should be SIGINT)
 */
void sigint_handler(int signum) {
    (void)signum;  // Avoid unused parameter warning
    printf("Ha Ha, Not Stopping\n");
}

int main(int argc, char *argv[]) {

    // Handle command-line arguments 
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Set up signal handler for SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep program running and responsive to signals
    while (1) {
        printf("Program running, Press Ctrl+C to test SIGINT handling.\n");
        pause();  // Wait for a signal
    }

    return 0;
}

