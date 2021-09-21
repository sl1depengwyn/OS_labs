#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

void *my_thread(void* args) {
    int *arr = (int*)args;
    printf("Hello from thread %d!\n", arr[0]+1);
    arr[1] = 1;
    pthread_exit(NULL);
}

int main () {
    
    int n = 0;
    
    printf("Input the number of threads to be created: ");
    scanf("%d", &n);
    
    pthread_t thread[n];
    
    for (int i = 0; i < n; ++i) {
	int args[2];
	args[0] = i;
	args[1] = 0;
        if (pthread_create(&thread[i], NULL, my_thread, (void*)args)) {
            printf("ERROR while creating a thread!\n");
            pthread_exit(NULL);
            return EXIT_FAILURE;
        } else {
            printf(" >>The thread %d has just created!\n", i+1);
        }
	while (args[1] == 0) {}
	/* it waits until created thread finishes its work, and only then creates new thread */
    }

    pthread_exit(NULL);
    return EXIT_SUCCESS;
}



