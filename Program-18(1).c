#include <stdio.h>
#include <string.h>

#define MAX_FILES 100

typedef struct {
    char filename[50];
    int start_block;
    int num_blocks;
} FileEntry;

FileEntry files[MAX_FILES];
int num_files = 0;

void create_file(const char *filename, int start_block, int num_blocks) {
    strcpy(files[num_files].filename, filename);
    files[num_files].start_block = start_block;
    files[num_files].num_blocks = num_blocks;
    num_files++;
}

void display_directory() {
    printf("Single Level Directory:\n");
    for (int i = 0; i < num_files; i++) {
        printf("Filename: %s, Start Block: %d, Number of Blocks: %d\n", files[i].filename, files[i].start_block, files[i].num_blocks);
    }
}

int main() {
    create_file("file1.txt", 0, 3);
    create_file("file2.txt", 3, 2);
    display_directory();
    return 0;
}
