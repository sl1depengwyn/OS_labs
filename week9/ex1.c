#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int age;
} page;


int main() {
    int num_of_pages = 0;
    int NUM_OF_BITS = 16;

    printf("Input the number of pages: ");
    scanf("%d", &num_of_pages);
    page pages[num_of_pages];

    for (int i = 0; i < num_of_pages; ++i) {
        pages[i].id = -1;
        pages[i].age = 0;
    }

    int is_in_memory[1024];
    for (int i = 0; i < 1024; ++i) {
        is_in_memory[i] = 0;
    }

    float hits = 0;
    float misses = 0;

    FILE *input = fopen("input.txt", "r");
    int next_page;
    while (fscanf(input, "%d", &next_page) != EOF) {

        for (int i = 0; i < num_of_pages; ++i) {
            printf("%d\t%d\n", pages[i].id, pages[i].age);
        }
        printf("next page is %d\n\n", next_page);

        if (is_in_memory[next_page] == 1) {
            hits++;
        } else {
            misses++;
            int min_age = INT_MAX;
            int min_page_id = -1;
            for (int i = 0; i < num_of_pages; ++i) {
                if (pages[i].id == -1) {
                    min_page_id = i;
                    min_age = -1;
                    break;
                }
                if (pages[i].age < min_age) {
                    min_age = pages[i].age;
                    min_page_id = i;
                }
            }

            if (min_age != -1) is_in_memory[pages[min_page_id].id] = 0;
            is_in_memory[next_page] = 1;
            pages[min_page_id] = (page) {.id = next_page, .age = 0};
        }

        for (int i = 0; i < num_of_pages; ++i) {
            if (pages[i].id == next_page) {
                pages[i].age |= 1 << (NUM_OF_BITS - 1);
            } else {
                pages[i].age >>= 1;
            }
        }
    }

    for (int i = 0; i < num_of_pages; ++i) {
        printf("%d\t%d\n", pages[i].id, pages[i].age);
    }

    printf("Hits = %.0f Misses = %.0f Hit/Miss ratio = %f", hits, misses, hits / misses);

    fclose(input);

    return 0;
}

