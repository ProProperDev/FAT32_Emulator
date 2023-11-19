#include "open-close_functions.h"

int mount_disk(const char* diskpath) {
    char mount_command[255] = {0};
    struct stat dir_status;
               
    if (!stat(DISK_DIR, &dir_status)) {
        if (!S_ISDIR(dir_status.st_mode)) {
            return errno; // Not a directory (ENOTDIR)
        }
    } else {
        if (mkdir(DISK_DIR, 0744) != CODE_OF_SUCCESS) {
            return errno;
        }
    }
    printf("Mounting... disk in %s\n", diskpath);

    sprintf(mount_command, "mount -t vfat -o loop %s %s", diskpath, DISK_DIR);
    if (system(mount_command) != CODE_OF_SUCCESS) {
        return errno;
    }

    printf("\033[100mMounting disk...success\033[0m\n");

    return CODE_OF_SUCCESS;
}

int umount_disk(const char* diskpath) {

    if (umount(DISK_DIR) != CODE_OF_SUCCESS) {
        return errno;
    }
    printf("\033[100mUnmounting disk %s ... success\033[0m\n", DISK_DIR);

    if (rmdir(DISK_DIR) != CODE_OF_SUCCESS) {
        return errno;
    }
    printf("Removing disk dir %s ... success\n", DISK_DIR);

    return CODE_OF_SUCCESS;
}

int open_disk(const char* diskpath) {
    char info_message[255] = {0};
    int file_desc = open(diskpath, O_CREAT|O_EXCL|O_SYNC|O_RDWR, S_IRUSR|S_IWUSR);

    if (file_desc == -1) {
        if (errno == EEXIST) {
            sprintf(info_message, "%s%s", "File for fat32 disk is already exist. Path: ", diskpath);
        } else {
            return errno;
        }
    } else {
        sprintf(info_message, "%s%s", "File for fat32 disk created. Path: ", diskpath);
    }

    printf("%s\n", info_message);
    // Устанавливаем требуемый размер
    if (truncate(diskpath, DEFAULT_DISK_SIZE) != CODE_OF_SUCCESS) {
        return errno;
    }
    printf("File %s have size: %d bytes\n", diskpath, get_file_size(diskpath));
    close(file_desc);   

    if (mount_disk(diskpath) == CODE_OF_SUCCESS) {
        fat32_fs_build = true;
    } else {
        printf("Error to mount disk in %s\n", diskpath);
        printf("Reason: %s [%d]\n", strerror(errno), errno);
    }

    return CODE_OF_SUCCESS;
}

int get_file_size(const char* filepath) {
    struct stat file_status;
    if (stat(filepath, &file_status) != CODE_OF_SUCCESS) {
        printf("Can`t obtain information about %s file\n", filepath);
        return -1;      
    }
    return file_status.st_size;
}

