#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define NOSHORTCUTS 3

void INThandler() {
    exit(0);
}

typedef struct {
    char message[512];
    unsigned short key_codes[6];
    unsigned short no_keys;
    unsigned short printed_last;
} shortcut;


int main() {
    char devname[] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    int keyboard = open(devname, O_RDONLY);
    struct input_event event;
    FILE* output_file = fopen("ex3.txt", "w");

    unsigned short keys_status[65536];

    for (int i = 0; i < 65536; ++i) {
        keys_status[i] = 0;
    }

    shortcut shortcuts[NOSHORTCUTS];

    shortcut cappuchino_shortcut = {.message = "Get some cappuccino!", .key_codes = {25, 30, 46}, .no_keys = 3, .printed_last = 0};
    shortcuts[0] = cappuchino_shortcut;

    shortcut exam_shortcut = {.message = "I passed the Exam!", .key_codes = {18, 25}, .no_keys = 2, .printed_last = 0};
    shortcuts[1] = exam_shortcut;

    shortcut my_shortcut = {.message = "I love you!", .key_codes = {2, 4, 5}, .no_keys = 3, .printed_last = 0};
    shortcuts[2] = my_shortcut;



    signal(SIGINT, INThandler);

    while (1)
    {
        read(keyboard, &event, sizeof(event));
        keys_status[event.code] = event.value;

        for (int i = 0; i < NOSHORTCUTS; ++i) {
            int is_active = 1;
            for (int j = 0; j < shortcuts[i].no_keys; ++j) {
                if (keys_status[shortcuts[i].key_codes[j]] == 0) {
                    is_active = 0;
                    shortcuts[i].printed_last = 0;
                    break;
                }
            }

            if (is_active && !shortcuts[i].printed_last) {
                shortcuts[i].printed_last = 1;
                printf("%s\n", shortcuts[i].message);
                fprintf(output_file, "%s\n", shortcuts[i].message);
            }
        }
    }
}