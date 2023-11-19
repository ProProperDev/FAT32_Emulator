#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/statfs.h>

#include "commands.h"

#ifndef DISK_DIR
#define DISK_DIR "fat32disk"
#endif

#define MAX_PARAM_COUNT 5

extern const int CODE_OF_SUCCESS;

extern bool fat32_fs_build;
extern char curr_dir_on_disk[];
extern char* path_to_disk;
extern char curr_work_dir[];

enum command_name {
    LS,            // ls command
    FORMAT,        // format command
    TOUCH,         // touch command
    MKDIR,         // mkdir command
    CD,            // cd command
    HELP,          // help command
    EXIT,          // exit command
    UNKNOWN,       // unknown command
    EMPTY_COMMAND, // empty input
};

static char* input_params[MAX_PARAM_COUNT] = {NULL};
static char* input_command = NULL;

bool is_empty_string(const char* str);

void clear_string(char* str);

int command_resolving(const char* command);

void parse_command_and_param();

void input_processing(FILE* stream);
