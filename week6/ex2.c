#include <stdio.h>
#include <stdlib.h>

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct {
    unsigned int index;
    unsigned int arrival_time;
    unsigned int burst_time;
    unsigned int completion_time;
    unsigned int turn_around_time;
    unsigned int waiting_time;
} process;

process* short_job_next(process* processes, unsigned int length);

int main() {
    unsigned int n = 0;
    printf("Input the number of processes (natural number): ");
    scanf("%u", &n);
    process processes[n];

    for (int i = 0; i < n; ++i) {
        printf("Input the arrival time and burst time of %u process(in format <arrival_time> <burst_time>): ", i + 1);
        scanf("%u %u", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].index = i + 1;
    }

    process* ordered_processes = short_job_next(processes, n);

    ordered_processes[0].completion_time = ordered_processes[0].burst_time + ordered_processes[0].arrival_time;
    ordered_processes[0].turn_around_time = ordered_processes[0].burst_time;
    ordered_processes[0].waiting_time = 0;

    for (int i = 1; i < n; ++i) {
        ordered_processes[i].completion_time = max(ordered_processes[i - 1].completion_time, ordered_processes[i].arrival_time) + ordered_processes[i].burst_time;
        ordered_processes[i].turn_around_time = ordered_processes[i].completion_time - ordered_processes[i].arrival_time;
        ordered_processes[i].waiting_time = ordered_processes[i].turn_around_time - ordered_processes[i].burst_time;
    }

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");

    float sum_turn_around = 0;
    float sum_waiting = 0;

    for (int i = 0; i < n; ++i) {

        sum_turn_around += ordered_processes[i].turn_around_time;
        sum_waiting += ordered_processes[i].waiting_time;

        printf("P%u\t%u\t%u\t%u\t%u\t%u\n",
               ordered_processes[i].index,
               ordered_processes[i].arrival_time,
               ordered_processes[i].burst_time,
               ordered_processes[i].completion_time,
               ordered_processes[i].turn_around_time,
               ordered_processes[i].waiting_time);
    }
    free(ordered_processes);
    printf("Average Turnaround time = %f\n", sum_turn_around / n);
    printf("Average Waiting Time = %f\n", sum_waiting / n);

}

process* short_job_next(process* processes, unsigned int length) {

    short* is_taken = (short*) calloc(length, sizeof(short));
    process* ordered_processes = (process*) calloc(length, sizeof(process));
    if (!is_taken || !ordered_processes) {
        printf("Allocation error, probably not enough memory");
    }
    printf("%d \n", is_taken[1]);

    unsigned int time = INT_MAX; // initially time equals to the lesser arrival time 
    for (int i = 0; i < length; ++i) {
        if (processes[i].arrival_time < time) {
            time = processes[i].arrival_time;
        }
    }

    for (int i = 0; i < length; ++i) {
        unsigned int soonest_at = INT_MAX;
        for (int j = 0; j < length; ++j) {
            if (processes[j].arrival_time < soonest_at && is_taken[j] == 0) {
                soonest_at = processes[j].arrival_time;
            }
        }
        time = max(time, soonest_at);

        process next_process; // next process to execute
        unsigned int lowest_bt = INT_MAX;
        unsigned int index_of_next_process = -1; // id of next process in initial array processes

        for (int j = 0; j < length; ++j) {
            if (processes[j].arrival_time <= time && processes[j].burst_time < lowest_bt && is_taken[j] == 0) {
                next_process = processes[j];
                lowest_bt = processes[j].burst_time;
                index_of_next_process = j;
            }
        }

        ordered_processes[i] = next_process;
        is_taken[index_of_next_process] = 1;
        time += next_process.burst_time;
    }

    free(is_taken);
    return ordered_processes;
}