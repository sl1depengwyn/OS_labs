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
    unsigned int done_job; // number os seconds that process already worked
} process;

int comp(const void *first, const void *second);

int main() {
    unsigned int quantum = 0;
    unsigned int n = 0;
    printf("Input the quantum (natural number): ");
    scanf("%u", &quantum);
    printf("Input the number of processes (natural number): ");
    scanf("%u", &n);
    process processes[n];

    for (int i = 0; i < n; ++i) {
        printf("Input the arrival time and burst time of %u process(in format <arrival_time> <burst_time>): ", i + 1);
        scanf("%u %u", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].index = i + 1;
        processes[i].done_job = 0;
    }

    // qsort(processes, n, sizeof(process), comp); // I assume user input process in order of arrival, but if no, just remove '//'

    short is_in_queue[n];
    for (int i = 0; i < n; ++i) {
        is_in_queue[i] = 0;
    }

    unsigned int time = processes[0].arrival_time;
    // initially time equals to the lesser arrival time, it is the lesser since array sorted by arrival time

    int queue[n];
    unsigned int no_finished_processes = 0;
    unsigned int no_processes_in_queue = 0;
    for (int i = 0; i < n; ++i) {
        if (processes[i].arrival_time <= time) {
            is_in_queue[i] = 1;
            queue[no_processes_in_queue++] = i;
        }
    }

    while (1) {
        if (no_finished_processes == n) {
            break;
        }

        if (no_processes_in_queue == 0) { // means that process stalls until next process arrives
            for (int i = 0; i < n; ++i) {
                if (is_in_queue[i] == 0) {
                    time = processes[i].arrival_time;
                    break;
                }
            }

            for (int i = 0; i < n; ++i) {
                if (is_in_queue[i] == 0 && processes[i].arrival_time <= time) {
                    queue[no_processes_in_queue++] = i;
                }
            }
        }

        // In general code below imitate a queue using ordinary array

        for (int i = 0; i < no_processes_in_queue; ++i) {
            unsigned int this_quantum = quantum;
            short is_finished = 0;
            if (this_quantum >= processes[queue[i]].burst_time - processes[queue[i]].done_job) {
                time += processes[queue[i]].burst_time - processes[queue[i]].done_job;
                processes[queue[i]].completion_time = time;
                processes[queue[i]].turn_around_time = processes[queue[i]].completion_time - processes[queue[i]].arrival_time;
                processes[queue[i]].waiting_time = processes[queue[i]].turn_around_time - processes[queue[i]].burst_time;
                no_finished_processes++;
                is_finished = 1;
            } else {
                processes[queue[i]].done_job += this_quantum;
                time += this_quantum;
            }

            // check for processes that might arrive while cpu was busy with previous process
            unsigned int no_arrived_processes = 0;
            int arrived_processes[n];
            for (int j = 0; j < n; ++j) {
                if (processes[j].arrival_time <= time && is_in_queue[j] == 0) {
                    arrived_processes[no_arrived_processes++] = j;
                    is_in_queue[j] = 1;
                }
            }

            // and here we put all arrived process behind process that we just worked with (i.e. in the end of the queue)
            if (no_arrived_processes > 0) {
                for (int j = no_processes_in_queue - 1; j >= i + is_finished; --j) {
                    queue[j + no_arrived_processes - is_finished] = queue[j];
                }
                for (int j = 0; j < no_arrived_processes; ++j) {
                    queue[i++] = arrived_processes[j];
                    no_processes_in_queue++;
                }
            } else if (is_finished == 1) {
                for (int j = i; j < no_processes_in_queue - 1; ++j) {
                    queue[j] = queue[j + 1];
                }
            }

            if (is_finished == 1) {
                no_processes_in_queue--;
                --i;
            }
        }
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