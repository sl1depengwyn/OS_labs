#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void INThandler() {
    exit(0);
}

int main() {
    char devname[] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    int keyboard = open(devname, O_RDONLY);
    struct input_event event;
    FILE* output_file = fopen("ex2.txt", "w");
    

    signal(SIGINT, INThandler);

    while (1)
    {
        read(keyboard, &event, sizeof(event));
        if (event.type == 1)
        {   
            if (event.value == 1) {
                printf("PRESSED %x (%i)\n", event.code, event.code);
                fprintf(output_file, "PRESSED %x (%i)\n", event.code, event.code);
            } else if (event.value == 0) {
                printf("RELEASED %x (%i)\n", event.code, event.code);
                fprintf(output_file, "RELEASED %x (%i)\n", event.code, event.code);
            }
            
        }
    }
}