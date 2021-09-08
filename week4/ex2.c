#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    for (int i = 0; i < 5; ++i) {
        pid = fork();
        sleep(5);
    }
    return EXIT_SUCCESS;
    return 0;
}

/*
Explanations:
On the firts line (one with init) we see  first app
and its 5 copies
after each invocation, like:
ex2-----here-----ex2----
          |
its copying of parent process, and it's copying with same state
of the loop due to fact that after fork child process has almost the
same meory and state
hence, it has 4 invocations on each copying the child like rucursive function
and so on till first process ends and all its children and children of children finish their
loops as well
*/

