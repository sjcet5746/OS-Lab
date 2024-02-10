#include <stdio.h>

#define MAX_BLOCKS 100

int disk[MAX_BLOCKS] = {0}; // 0 indicates free block, 1 indicates allocated block

typedef struct Node {
    int block_number;
    struct Node *next;
} Node;

Node *files[MAX_BLOCKS] = {NULL};

int allocate_block() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            return i;
        }
    }
    return -1; // No free blocks available
}

void deallocate_blocks(Node *file) {
    Node *temp;
    while (file != NULL) {
        temp = file;
        file = file->next;
        disk[temp->block_number] = 0;
        free(temp);
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
    Node *file;

    // Allocate blocks for a file
    for (int i = 0; i < 5; i++) {
        int block_number = allocate_block();
        if (block_number != -1) {
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->block_number = block_number;
            new_node->next = NULL;
            if (files[i] == NULL) {
                files[i] = new_node;
            } else {
                Node *temp = files[i];
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_node;
            }
        } else {
            printf("Not enough blocks available.\n");
            break;
        }
    }
    printf("File allocated.\n");
    display_disk();

    // Deallocate the allocated blocks
    deallocate_blocks(files[0]);
    printf("Blocks deallocated.\n");
    display_disk();

    return 0;
}
