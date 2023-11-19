#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "input_processing.h"
#include "print_functions.h"

extern const int CODE_OF_SUCCESS;

extern bool fat32_fs_build;
extern char curr_dir_on_disk[];
extern char* path_to_disk;
extern char curr_work_dir[];

int make_dir(const char* params[]);

int change_dir(const char* params[]);

int make_file(const char* params[]);

int list_content(const char* params[]);

int format_disk(const char* params[]);

int leave_emulator(const char* params[]);

