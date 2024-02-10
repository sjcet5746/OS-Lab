#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 4
#define FRAME_SIZE 1024 // in bytes
#define PAGE_SIZE 256 // in bytes
#define NUM_PAGES 16

typedef struct {
    int frame_number;
    int is_valid;
} PageTableEntry;

PageTableEntry page_table[NUM_PAGES];
char memory[NUM_FRAMES][FRAME_SIZE];

void initialize_page_table() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].frame_number = -1;
        page_table[i].is_valid = 0;
    }
}

void display_page_table() {
    printf("Page Table:\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("Page %d -> Frame %d, Valid: %s\n", i, page_table[i].frame_number,
               page_table[i].is_valid ? "Yes" : "No");
    }
}

void display_memory() {
    printf("Memory:\n");
    for (int i = 0; i < NUM_FRAMES; i++) {
        printf("Frame %d: ", i);
        for (int j = 0; j < FRAME_SIZE; j++) {
            printf("%c", memory[i][j]);
        }
        printf("\n");
    }
}

void simulate_paging(int pages[]) {
    initialize_page_table();

    for (int i = 0; i < NUM_PAGES; i++) {
        int page_number = pages[i];
        if (!page_table[page_number].is_valid) { // Page fault
            int frame_number = rand() % NUM_FRAMES; // Select a frame randomly
            page_table[page_number].frame_number = frame_number;
            page_table[page_number].is_valid = 1;

            // Simulate loading page data into memory
            for (int j = 0; j < PAGE_SIZE; j++) {
                memory[frame_number][j] = 'A' + page_number; // Assigning some data for demonstration
            }
        }
        display_page_table();
        display_memory();
        printf("\n");
    }
}

int main() {
    int pages[NUM_PAGES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    simulate_paging(pages);

    return 0;
}
