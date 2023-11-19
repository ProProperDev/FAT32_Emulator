#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "commands.h"

int make_dir(const char* params[]) {
    // В данной версии эмулятора  для команды mkdir поддерживается только 1 параметр
    if (is_empty_string(params[0]) || !is_empty_string(params[1])) {
        errno = is_empty_string(params[0]) ? EINVAL : E2BIG;
        return errno; 
    }

    char new_folder[255] = {0};
    sprintf(new_folder, "%s", params[0]);

    struct stat dir_status = {0};

    char new_dir_path[255]= {0};
    
    (strlen(curr_dir_on_disk) == 1) ?
        sprintf(new_dir_path, "%s%s%s", curr_work_dir, curr_dir_on_disk, new_folder)
        : sprintf(new_dir_path, "%s%s/%s", curr_work_dir, curr_dir_on_disk, new_folder);

    if (stat(new_dir_path, &dir_status) != CODE_OF_SUCCESS) {
        if(mkdir(new_dir_path, 0744) != CODE_OF_SUCCESS) {
            return errno;
        } 
    } else {
        return errno; // Already exist (EEXIST)
    }

    return CODE_OF_SUCCESS;
}

int make_file(const char* params[]) {
    // В данной версии эмулятора  для команды touch поддерживается только 1 параметр
    if (is_empty_string(params[0]) || !is_empty_string(params[1])) {
        errno = is_empty_string(params[0]) ? EINVAL : E2BIG;
        return errno;
    }

    char new_file[255] = {0};
    sprintf(new_file, "%s", params[0]);
    char new_file_path[255] = {0};

    (strlen(curr_dir_on_disk) == 1) ?
        sprintf(new_file_path, "%s%s%s", curr_work_dir, curr_dir_on_disk, new_file)
        : sprintf(new_file_path, "%s%s/%s", curr_work_dir, curr_dir_on_disk, new_file);

    int file_descr = open(new_file_path, O_CREAT|O_EXCL|O_SYNC|O_RDWR, S_IRUSR|S_IWUSR);

    if (file_descr == -1) {
        return errno;
    }

    close(file_descr);
    
    return CODE_OF_SUCCESS;
}

int list_content(const char* params[]) {
    // В данной версии эмулятора наличие параметров для ls не предполагается
    if (!is_empty_string(params[0])) {
        errno = E2BIG;
        return errno; // Argumet list too long
    }

    DIR* dir;
    char buffer[255] = {0};

    struct dirent *dir_info;
/* Little manual for struct dirent
    struct dirent {
               ino_t          d_ino;       // Inode number 
               off_t          d_off;       // Not an offset; see below 
               unsigned short d_reclen;    // Length of this record 
               unsigned char  d_type;      // Type of file; not supported
                                              by all filesystem types 
               char           d_name[256]; // Null-terminated filename 
    };
*/
    sprintf(buffer, "%s%s", curr_work_dir, curr_dir_on_disk);

    if ((dir = opendir(buffer)) == NULL) {
        return errno;
    }

    while (dir_info = readdir(dir)) {
        if (dir_info->d_type == DT_DIR) {
            print_dirname(dir_info->d_name);
        } else {
            print_filename(dir_info->d_name);
        }
    }
    closedir(dir);
    
    return CODE_OF_SUCCESS;
}

int change_dir(const char* params[]) {
     // В данной версии эмулятора  для команды cd поддерживается только 1 параметр
    if (is_empty_string(params[0]) || !is_empty_string(params[1])) {
        errno = is_empty_string(params[0]) ? EINVAL : E2BIG;
        return errno; 
    }

    char path_to_dir[255] = {0};
    sprintf(path_to_dir, "%s", params[0]);

    char full_path_to_dir[255] = {0};
    struct stat dir_status = {0};

    sprintf(full_path_to_dir, "%s%s", curr_work_dir, path_to_dir);

    if (stat(full_path_to_dir, &dir_status) == CODE_OF_SUCCESS) {
        if (S_ISDIR(dir_status.st_mode)) {               
            sprintf(curr_dir_on_disk, "%s", path_to_dir);           
        } else {
            errno = ENOTDIR; 
            return errno; // Not a directory
        }
    } else {
       return errno;
    }
    
    return CODE_OF_SUCCESS;
}

int format_disk(const char* params[]) {
    // В данной версии эмулятора наличие параметров для format не предполагается
    if (!is_empty_string(params[0])) {
        errno = E2BIG;
        return errno; // Argumet list too long
    }

    char answer[3] = {0};
    char build_fs_command[255] = {0};
    printf("Disk space will be formatted!\nContinue? Type:(Y or N)\n");
    fgets(answer, sizeof(answer), stdin);
    if (strcasestr ("yes", answer) || answer[0] == 'Y' || answer[0] == 'y') {
        if (fat32_fs_build) {
            umount_disk(path_to_disk);
        }
        printf("path_to_disk in format: %s\n", path_to_disk);
        sprintf(build_fs_command, "mkfs -t vfat %s", path_to_disk);
        if(system(build_fs_command) != CODE_OF_SUCCESS) {
            return errno;
        }

        if (mount_disk(path_to_disk) == CODE_OF_SUCCESS) {
            fat32_fs_build = true;
        } else {
            printf("Error to mount disk in %s\n", path_to_disk);
            printf("Reason: %s [%d]\n", strerror(errno), errno);
        }   
    }
    
    return CODE_OF_SUCCESS; 
}

int leave_emulator(const char* params[]) {
     // В данной версии эмулятора наличие параметров для exit не предполагается
    if (!is_empty_string(params[0])) {
        errno = E2BIG;
        return errno; // Argumet list too long
    }

    if (fat32_fs_build) {
        if (umount_disk(path_to_disk) != CODE_OF_SUCCESS) {
            return errno;
        }
    }

    return CODE_OF_SUCCESS;
}

