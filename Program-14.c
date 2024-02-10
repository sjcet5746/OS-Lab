#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 3
#define NUM_PAGES 10

int frames[NUM_FRAMES];
int page_faults = 0;

void initialize_frames() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1; // Initialize frames with invalid page numbers
    }
}

void display_frames() {
    printf("Frames: ");
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == -1) {
            printf("[ ] "); // Empty frame
        } else {
            printf("[%d] ", frames[i]); // Occupied frame
        }
    }
    printf("\n");
}

int find_page_index(int page) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == page) {
            return i; // Page found in a frame
        }
    }
    return -1; // Page not found
}

void fifo(int pages[]) {
    initialize_frames();

    int index = 0; // Index to keep track of the frame to replace
    for (int i = 0; i < NUM_PAGES; i++) {
        int page = pages[i];
        if (find_page_index(page) == -1) { // Page fault
            frames[index] = page; // Replace the page at the current index
            index = (index + 1) % NUM_FRAMES; // Move to the next frame
            page_faults++;
        }
        display_frames();
    }
}

void lru(int pages[]) {
    initialize_frames();

    int recent_access[NUM_FRAMES] = {0};
    for (int i = 0; i < NUM_PAGES; i++) {
        int page = pages[i];
        int index = find_page_index(page);
        if (index == -1) { // Page fault
            int min_index = 0;
            for (int j = 1; j < NUM_FRAMES; j++) {
                if (recent_access[j] < recent_access[min_index]) {
                    min_index = j;
                }
            }
            frames[min_index] = page; // Replace the page with the least recent access
            page_faults++;
        }
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] != -1) {
                recent_access[j]++;
            }
        }
        recent_access[index] = 0; // Reset the recent access for the current page
        display_frames();
    }
}

void lfu(int pages[]) {
    initialize_frames();

    int access_count[NUM_FRAMES] = {0};
    for (int i = 0; i < NUM_PAGES; i++) {
        int page = pages[i];
        int index = find_page_index(page);
        if (index == -1) { // Page fault
            int min_index = 0;
            for (int j = 1; j < NUM_FRAMES; j++) {
                if (access_count[j] < access_count[min_index]) {
                    min_index = j;
                }
            }
            frames[min_index] = page; // Replace the page with the least access count
            page_faults++;
        }
        if (index != -1) {
            access_count[index]++; // Increment the access count for the current page
        }
        display_frames();
    }
}

int main() {
    int pages[NUM_PAGES] = {1, 3, 2, 4, 5, 1, 6, 3, 7, 8};

    printf("FIFO Page Replacement Algorithm:\n");
    fifo(pages);
    printf("Total page faults: %d\n\n", page_faults);

    page_faults = 0;
    printf("LRU Page Replacement Algorithm:\n");
    lru(pages);
    printf("Total page faults: %d\n\n", page_faults);

    page_faults = 0;
    printf("LFU Page Replacement Algorithm:\n");
    lfu(pages);
    printf("Total page faults: %d\n\n", page_faults);

    return 0;
}
