#include <stdio.h>
#include <unistd.h>

int main() {
    int childPid;

    childPid = fork();

    if (childPid) {
        printf("Parent process\n");
    } else {
        printf("Child process\n");
        execl("/bin/ls", "ls", NULL);
    }

    return 0;
}