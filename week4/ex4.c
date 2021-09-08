#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	char command[1024];
	char *c = command;
	size_t commSize = 1024;
	printf("Available length of command with its arguments is 1024 chracters, in case of more chracters expect unexpected behavior\n");
	for (;;) {
		printf("$ ");
		getline(&c, &commSize, stdin);
        	system(command);
    	}
	return EXIT_SUCCESS;
}

