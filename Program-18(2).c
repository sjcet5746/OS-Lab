#include <stdio.h>
#include <string.h>

#define MAX_FILES_PER_DIRECTORY 10
#define MAX_DIRECTORIES 10

typedef struct {
    char filename[50];
    int start_block;
    int num_blocks;
} FileEntry;

typedef struct {
    char dirname[50];
    FileEntry files[MAX_FILES_PER_DIRECTORY];
    int num_files;
} Directory;

Directory directories[MAX_DIRECTORIES];
int num_directories = 0;

void create_directory(const char *dirname) {
    strcpy(directories[num_directories].dirname, dirname);
    directories[num_directories].num_files = 0;
    num_directories++;
}

void create_file(const char *filename, int start_block, int num_blocks, const char *dirname) {
    int dir_index = -1;
    for (int i = 0; i < num_directories; i++) {
        if (strcmp(directories[i].dirname, dirname) == 0) {
            dir_index = i;
            break;
        }
    }
    if (dir_index != -1) {
        strcpy(directories[dir_index].files[directories[dir_index].num_files].filename, filename);
        directories[dir_index].files[directories[dir_index].num_files].start_block = start_block;
        directories[dir_index].files[directories[dir_index].num_files].num_blocks = num_blocks;
        directories[dir_index].num_files++;
    }
}

void display_directory(const char *dirname) {
    printf("Directory: %s\n", dirname);
    int dir_index = -1;
    for (int i = 0; i < num_directories; i++) {
        if (strcmp(directories[i].dirname, dirname) == 0) {
            dir_index = i;
            break;
        }
    }
    if (dir_index != -1) {
        for (int i = 0; i < directories[dir_index].num_files; i++) {
            printf("Filename: %s, Start Block: %d, Number of Blocks: %d\n", directories[dir_index].files[i].filename, directories[dir_index].files[i].start_block, directories[dir_index].files[i].num_blocks);
        }
    }
}

int main() {
    create_directory("directory1");
    create_file("file1.txt", 0, 3, "directory1");
    create_file("file2.txt", 3, 2, "directory1");
    display_directory("directory1");
    return 0;
}
