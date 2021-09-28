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

int comp(const void *first, const void *second);

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

    // qsort(processes, n, sizeof(process), comp); I assume user input process in order of arrival, but if no, just remove '//'

    processes[0].completion_time = processes[0].burst_time + processes[0].arrival_time;
    processes[0].turn_around_time = processes[0].burst_time;
    processes[0].waiting_time = 0;

    for (int i = 1; i < n; ++i) {
        processes[i].completion_time = max(processes[i - 1].completion_time, processes[i].arrival_time) + processes[i].burst_time;
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    }

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");

    float sum_turn_around = 0;
    float sum_waiting = 0;

    for (int i = 0; i < n; ++i) {

        sum_turn_around += processes[i].turn_around_time;
        sum_waiting += processes[i].waiting_time;

        printf("P%u\t%u\t%u\t%u\t%u\t%u\n",
               processes[i].index,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turn_around_time,
               processes[i].waiting_time);
    }

    printf("Average Turnaround time = %f\n", sum_turn_around / n);
    printf("Average Waiting Time = %f\n", sum_waiting / n);

}

int comp(const void *first, const void *second) {
    process first_process = *((process *) first);
    process second_process = *((process *) second);

    if (first_process.arrival_time > second_process.arrival_time) return 1;
    if (first_process.arrival_time < second_process.arrival_time) return -1;

    return 0;
}