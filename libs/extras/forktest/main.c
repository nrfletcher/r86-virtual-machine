#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) { // Error occurred
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) { // Child process
        printf("Child process, PID: %d\n", getpid());
        
        // Execute your program in the child process
        char *const argv[] = {"./my_program", NULL}; // Path to your program
        execvp("./my_program", argv);
        
        // execvp() will only return if an error occurs
        perror("execvp"); // Print error message
        exit(EXIT_FAILURE); // Terminate child process with failure status
    } else { // Parent process
        printf("Parent process, child PID: %d\n", pid);
        
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }

    return 0;
}
