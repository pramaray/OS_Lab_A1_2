/* 
 * Group A1 Team 2
 * Team Leader   - Rishika Sur (002311001025)
 * Team Members  - Vidhi Mantry (002311001043)
 *               - Prama Ray (002311001033)
 * 
 * Assignment: 1B
 * Description: This program demonstrates how to get and set environment variables 
 * using system calls in a UNIX environment.
 * 
 * The program uses:
 * - getenv() to fetch the values of various environment variables like USER, HOME, HOST, etc.
 * - setenv() to set two new environment variables NEW_USER and NEW_HOST.
 * 
 * Input: None
 * 
 * Output:
 * - Displays the values of environment variables: USER, HOME, HOST, ARCH, DISPLAY, PRINTER, PATH.
 * - Sets two new environment variables NEW_USER and NEW_HOST and displays them.
 * 
 * Note: The program requires two command-line arguments to set the new environment variables.
 * Usage:  
 *  1. Compile the program using the command: gcc -o A1_02_1B A1_02_1B.c
 *  2. Run the program with two arguments: ./A1_02_1B User1 MyComputer 
 * 
 * Warning: No warnings during compilation.
 *
 * Example Output:
 * 
 * Program to GET and SET Environment Variables
 * 
 * Displaying predefined environment variables:
 * USER = be2343
 * HOME = /home/usr/student/ug/yr23/be2343
 * HOST is not set or empty
 * ARCH is not set or empty
 * DISPLAY is not set or empty
 * PRINTER is not set or empty
 * PATH = /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/be2343/.local/bin:/home/usr/student/ug/yr23/be2343/bin
 *
 * Setting new environment variables:
 * NEW_USER set to: User1
 * NEW_HOST set to: MyComputer
 *
 * Displaying newly set environment variables:
 * NEW_USER = User1
 * NEW_HOST = MyComputer
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Array of predefined environment variables to display
    const char *predefined_env_vars[] = {"USER", "HOME", "HOST", "ARCH", "DISPLAY", "PRINTER", "PATH"};
    const int predefined_var_count = sizeof(predefined_env_vars) / sizeof(predefined_env_vars[0]);
    int i; 

    // Display program header
    printf("\nProgram to GET and SET Environment Variables\n");

    // Displaying predefined environment variables using getenv()
    printf("\nDisplaying predefined environment variables:\n");
    for (i = 0; i < predefined_var_count; i++) 
    {
        // Fetching each environment variable's value using getenv
        const char *env_value = getenv(predefined_env_vars[i]);
        if (env_value != NULL) 
            // If the environment variable exists, print its value
            printf("%s = %s\n", predefined_env_vars[i], env_value);
        else 
            // If the environment variable does not exist, print an appropriate message
            printf("%s is not set or empty\n", predefined_env_vars[i]);
    }

    // Check if the user has provided the necessary command-line arguments
    if (argc < 3) 
    {
        // Display usage information if there are not enough arguments
        printf("\nUsage: ./A1_02_1B NEW_USER NEW_HOST\n");
        return 1; // Return an error code if not enough arguments are provided
    }

    // Names of the new environment variables to set
    const char *new_env_vars[] = {"NEW_USER", "NEW_HOST"};
    // Calculate the number of new environment variables
    const int new_var_count = sizeof(new_env_vars) / sizeof(new_env_vars[0]);

    // Set new environment variables using setenv()
    printf("\nSetting new environment variables:\n");
    for (i = 0; i < new_var_count; i++) 
    {
        // Set the new environment variable to the value passed as a command-line argument
        if (setenv(new_env_vars[i], argv[i + 1], 1) < 0)
        {
            // If there is an error setting the environment variable, print the error message
            perror("Error setting new environment variable");
        } 
        else
        {
            // If the environment variable is successfully set, print its new value
            printf("%s set to: %s\n", new_env_vars[i], getenv(new_env_vars[i]));
        }
    }

    // Display the newly set environment variables
    printf("\nDisplaying newly set environment variables:\n");
    for (i = 0; i < new_var_count; i++) 
    {
        // Fetch and display the newly set environment variable values
        const char *new_env_value = getenv(new_env_vars[i]);
        if (new_env_value != NULL)
            // If the environment variable is set, print its value
            printf("%s = %s\n", new_env_vars[i], new_env_value);
        else
            // If the environment variable is not set, print an appropriate message
            printf("%s is not set or empty\n", new_env_vars[i]);
    }

    return 0; 
}

