#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/statfs.h>
#include <sys/mount.h>

#include "open-close_functions.h"
#include "print_functions.h"

/*** Main Emulator Parameters ***/
#define DEFAULT_DISK_SIZE 0x1400000 // in off_t type; 20 MB
#define DISK_DIR "fat32disk"
/*******************************/

const int CODE_OF_SUCCESS = 0;

bool fat32_fs_build  = false;
char curr_work_dir[255] = {0};
char curr_dir_on_disk[255] = "/";
char* path_to_disk;


int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Error to open disk\n");
        printf("Reason: %s [%d]\n", strerror(EINVAL), EINVAL); // Invalid argument
        return 1;
    }
    
    path_to_disk = argv[1];
   
    if (open_disk(path_to_disk) != CODE_OF_SUCCESS) {
        printf("Error to open disk\n");
        printf("Reason: %s [%d]\n", strerror(errno), errno);
        return 1;
    }

    print_help(input_params);

    input_processing(stdin);

    return 0;
}

