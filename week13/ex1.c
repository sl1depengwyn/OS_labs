#include <stdio.h>
#include <stdlib.h>

#define NO_PROCESSES 5
#define NO_RES_TYPES 3

int is_enough_resources(const int *requested, const int *free, int no_resources);

void free_resources(const int *current, int *free, int no_resources);

int main() {

    FILE *input_file = fopen("input.txt", "r");

    int exist[NO_RES_TYPES];

    int free[NO_RES_TYPES];

    int current[NO_RES_TYPES][NO_PROCESSES];

    int requested[NO_RES_TYPES][NO_PROCESSES];

    int is_finished[NO_PROCESSES];

    for (int i = 0; i < NO_RES_TYPES; ++i) {
        fscanf(input_file, "%d", &exist[i]);
    }

    for (int i = 0; i < NO_RES_TYPES; ++i) {
        fscanf(input_file, "%d", &free[i]);
    }

    for (int i = 0; i < NO_PROCESSES; ++i) {
        for (int j = 0; j < NO_RES_TYPES; ++j) {
            fscanf(input_file, "%d", &current[i][j]);
        }
        is_finished[i] = 0;
    }

    for (int i = 0; i < NO_PROCESSES; ++i) {
        for (int j = 0; j < NO_RES_TYPES; ++j) {
            fscanf(input_file, "%d", &requested[i][j]);
        }
    }

    for (int i = 0; i < NO_PROCESSES; ++i) {
        for (int process = 0; process < NO_PROCESSES; ++process) {
            if (is_finished[process] == 0 && is_enough_resources(requested[process], free, NO_RES_TYPES) == 1) {
                free_resources(current[process], free, NO_RES_TYPES);
                is_finished[process] = 1;
            }
        }
    }

    int is_deadlock = 0;
    for (int i = 0; i < NO_PROCESSES; ++i) {
        if (is_finished[i] == 0) {
            is_deadlock = 1;
            printf("Process %d is in deadlock\n", i);
        }
    }

    if (is_deadlock == 0) {
        printf("No deadlock is detected\n");
    }

    return EXIT_SUCCESS;
}

int is_enough_resources(const int *requested, const int *free, int no_resources) {
    for (int i = 0; i < no_resources; ++i) {
        if (requested[i] > free[i]) {
            return 0;
        }
    }
    return 1;
}

void free_resources(const int *current, int *free, int no_resources) {
    for (int i = 0; i < no_resources; ++i) {
        free[i] += current[i];
    }
}
