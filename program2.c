#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void alarm_handler(int sig) {
    printf("Alarm signal received. Killing child process.\n");
    kill(0, SIGKILL);
}

void child_death_handler(int sig) {
    printf("Child process terminated.\n");
}

int main() {
    pid_t pid;
    int status;

    signal(SIGALRM, alarm_handler);
    signal(SIGCHLD, child_death_handler);

    pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process started. PID: %d\n", getpid());
        execl("/bin/ls", "ls", NULL);  // Replace "/bin/ls" with your command
    } else if (pid > 0) {
        // Parent process
        printf("Parent process. Child PID: %d\n", pid);
        alarm(5);  // Set alarm for 5 seconds
        wait(&status);
    } else {
        // Fork failed
        printf("Fork failed.\n");
        return 1;
    }

    return 0;
}

