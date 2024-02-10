#include <stdio.h>

#define MAX_BLOCKS 100

int disk[MAX_BLOCKS] = {0}; // 0 indicates free block, 1 indicates allocated block

int allocate_blocks(int num_blocks) {
    int start_block = -1;
    int count = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i] == 0) {
            if (start_block == -1) {
                start_block = i;
            }
            count++;
            if (count == num_blocks) {
                for (int j = start_block; j < start_block + num_blocks; j++) {
                    disk[j] = 1;
                }
                return start_block;
            }
        } else {
            start_block = -1;
            count = 0;
        }
    }
    return -1; // Not enough contiguous blocks available
}

void deallocate_blocks(int start_block, int num_blocks) {
    for (int i = start_block; i < start_block + num_blocks; i++) {
        disk[i] = 0;
    }
}

void display_disk() {
    printf("Disk Status:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

int main() {
    int start_block;

    // Allocate blocks for a file
    start_block = allocate_blocks(3);
    if (start_block != -1) {
        printf("File allocated starting from block %d\n", start_block);
    } else {
        printf("Not enough contiguous blocks available.\n");
    }
    display_disk();

    // Deallocate the allocated blocks
    deallocate_blocks(start_block, 3);
    printf("Blocks deallocated.\n");
    display_disk();

    return 0;
}
