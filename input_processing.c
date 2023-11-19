#include "input_processing.h"

bool is_empty_string(const char* str) {
    if (str != NULL) {
        return str[0] == '\0';
    }

    return true;
}

void clear_string(char* str) {
    if (!is_empty_string(str)) {
        memset(str, '\0', strlen(str));
    }
}

int command_resolving(const char* command) {
    if (is_empty_string(command)) {
        return EMPTY_COMMAND;
    }
    if (!strncmp(command, "ls", 2)) {
        return LS;
    }
    if (!strncmp(command, "format", 6)) {
        return FORMAT;
    }
    if (!strncmp(command, "touch", 5)) {
        return TOUCH;
    }
    if (!strncmp(command, "mkdir", 5)) {
        return MKDIR;
    }
    if (!strncmp(command, "cd", 2)) {
        return CD;
    }
    if (!strncmp(command, "help", 4)) {
        return HELP;
    }
    if (!strncmp(command, "exit", 4)) {
        return EXIT;
    }
    
    return UNKNOWN;
}

void parse_command_and_param() {
    char input_buffer[255] = {0};
    char* comm_and_params[MAX_PARAM_COUNT + 1] = {NULL}; // [0] - command, [1-5] - params

    fgets(input_buffer, sizeof(input_buffer), stdin);

    char* ptr_on_space = NULL;
    int index = 0;
    
    // Игнорируем пробелы в начале ввода, если они есть
    while (input_buffer[index] == ' ' && input_buffer[index] != '\n') {
        ++index;
    }
    
    comm_and_params[0] = &input_buffer[index];

    // Парсим команду и введённые параметры в comm_and_params
    index = 0;
    while (ptr_on_space = strchr(comm_and_params[index], ' ')) {
        *(ptr_on_space) = '\0';

    // Обрабатываем пробелы, идущие подряд, если они есть
        while (*(ptr_on_space + 1) == ' ') {
            *(++ptr_on_space) = '\0';     
        }
       
       comm_and_params[++index] = ptr_on_space + 1;  
    }

    // Заменяем в последнем считанном параметре '\n' на '\0'
    comm_and_params[index][strlen(comm_and_params[index])-1] = '\0';

    // Поскольку команда вводится первой, её индекс в считанных параметрах [0]
    if (!is_empty_string(comm_and_params[0])) {
        input_command = comm_and_params[0];
    }

    // Параметры записаны в comm_and_params начиная с [1]
    index = 0;
    while (!is_empty_string(comm_and_params[index + 1])) {
        input_params[index++] = comm_and_params[index];
    }
}

void input_processing(FILE* stream) {

    getcwd(curr_work_dir, 255);
    sprintf(curr_work_dir, "%s/%s", curr_work_dir, DISK_DIR);
    printf("curr_work_dir: %s\n", curr_work_dir);
    printf("path_to_disk: %s\n", path_to_disk);

    while (true) {
        // Сброс на '0' используемых переменных
        clear_string(&input_command);
        for (int ind = 0; ind < sizeof(input_params)/sizeof(input_params[0]); ++ind) {
            clear_string(&input_params[ind]);
        }
        errno = (int) NULL;

        fprintf(stdout, "%s:%s>", DISK_DIR, curr_dir_on_disk);

        parse_command_and_param(); // command will stored in "input_command", params in "input_params"
  
        const enum command_name command = command_resolving(input_command);

        if (command == EMPTY_COMMAND) {
            continue;
        }
        if (command == UNKNOWN) {
            printf("Unknown command\n");
            continue;
        }
        if (command == FORMAT) {
            if (format_disk(input_params) != CODE_OF_SUCCESS) {
                printf("Error to format disk with command <format>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            } else {
                printf("Ok\n");
            }
            continue;
        }
        if (command == HELP) {
            if (print_help(input_params) != CODE_OF_SUCCESS) {
                printf("Error to print help message with command <help>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            }
            continue;
        }
        if (command == EXIT) {
            if (leave_emulator(input_params) != CODE_OF_SUCCESS) {
                printf("Error to leave emulator with command <exit>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            } else {
                printf("Goodbye!\n"); 
            }
            break;
        }
        if (!fat32_fs_build) {
            printf("Unknown disk format. Try formatting the disk with <format> command\n");
            continue;
        }
        if (command == LS) {
            if (list_content(input_params) != CODE_OF_SUCCESS) {
                printf("Error to list content with command <ls>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            }
            continue;
        }
        if (command == TOUCH) {
            if (make_file(input_params) != CODE_OF_SUCCESS) {
                printf("Error to create file with command <touch>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            } else {
                printf("Ok\n");
            }
            continue;
        }
        if (command == MKDIR) {
            if (make_dir(input_params) != CODE_OF_SUCCESS) {
                printf("Error to create directory with command <mkdir>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            } else {
                printf("Ok\n");
            }
            continue;
        }
        if (command == CD) {
            if (change_dir(input_params) != CODE_OF_SUCCESS) {
                printf("Error to change directory with command <cd>\n");
                printf("Reason: %s [%d]\n", strerror(errno), errno);
            }
            continue;
        }
    }
}
