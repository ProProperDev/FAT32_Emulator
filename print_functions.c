#include "print_functions.h"

void print_filename(const char filename[]) {
    printf("%s%s%s\n", filename_color, filename, default_backgr_color);
}

void print_dirname(const char dirname[]) {
    printf("%s%s%s\n", dirname_color, dirname, default_backgr_color);
}

int print_help(const char* params[]) {
    // В данной версии эмулятора наличие параметров для help не предполагается
    if (!is_empty_string(params[0])) {
        errno = E2BIG;
        return errno; // Argumet list too long
    }

    printf("\nThis is FAT32 Emulator\n");
    printf("\nCommands as below are supported:\n"
           "ls                - list directory contents\n"
           "format            - format disk\n"
           "touch [FILE]      - create file \"FILE\"\n"
           "mkdir [DIRECTORY] - create directory \"DIRECTORY\"\n"
           "cd [PATH]         - change directory according \"PATH\"\n"
           "help              - show supported commands and description\n"
           "exit              - leave emulator\n"
          );

    return CODE_OF_SUCCESS;
}

