#include <stdio.h>
#include <string.h>

#define MAX_FILES_PER_DIRECTORY 10

typedef struct {
    char filename[50];
    int start_block;
    int num_blocks;
} FileEntry;

typedef struct Directory {
    char dirname[50];
    struct Directory *subdirectories;
    FileEntry files[MAX_FILES_PER_DIRECTORY];
    int num_files;
} Directory;

Directory root_directory = {"root", NULL, {}, 0};

void create_directory(Directory *parent, const char *dirname) {
    Directory *new_directory = (Directory *)malloc(sizeof(Directory));
    strcpy(new_directory->dirname, dirname);
    new_directory->subdirectories = NULL;
    new_directory->num_files = 0;
    parent->subdirectories = new_directory;
}

void create_file(Directory *parent, const char *filename, int start_block, int num_blocks) {
    strcpy(parent->files[parent->num_files].filename, filename);
    parent->files[parent->num_files].start_block = start_block;
    parent->files[parent->num_files].num_blocks = num_blocks;
    parent->num_files++;
}

void display_directory(Directory *directory) {
    printf("Directory: %s\n", directory->dirname);
    for (int i = 0; i < directory->num_files; i++) {
        printf("Filename: %s, Start Block: %d, Number of Blocks: %d\n", directory->files[i].filename, directory->files[i].start_block, directory->files[i].num_blocks);
    }
    if (directory->subdirectories != NULL) {
        display_directory(directory->subdirectories);
    }
}

int main() {
    create_directory(&root_directory, "directory1");
    create_file(&root_directory, "file1.txt", 0, 3);
    create_file(&root_directory, "file2.txt", 3, 2);
    display_directory(&root_directory);
    return 0;
}
