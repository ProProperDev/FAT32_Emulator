#pragma once

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

#ifndef DEFAULT_DISK_SIZE
#define DEFAULT_DISK_SIZE 0x1400000 // in off_t type; 20 MB
#endif

#ifndef DISK_DIR
#define DISK_DIR "fat32disk"
#endif

extern const int CODE_OF_SUCCESS;

extern bool fat32_fs_build;
extern char curr_work_dir[];
extern char curr_dir_on_disk[];
extern char* path_to_disk;

int mount_disk(const char* diskpath);

int umount_disk(const char* diskpath);

int open_disk(const char* diskpath);

int get_file_size(const char* filepath);
