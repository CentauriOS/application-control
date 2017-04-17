#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <appctl-rpc/wrapper.h>

// These two variables will be set at compile time with dd, then again at runtime with wrap()
extern char container_name[PATH_MAX];
char container_name[PATH_MAX] = " ";

extern char process_path[PATH_MAX];
char process_path[PATH_MAX] = " ";

// These two variables will be set at compile time with dd
extern int container_name_offset;
int container_name_offset = -1;

extern int process_path_offset;
int process_path_offset = -1;

int is_process_wrapper() {
    return *container_name != 0 && *process_path != 0;
}

const char *get_process_wrapper_container() {
    return (const char *) container_name;
}

const char *get_process_wrapper_path() {
    return (const char *) process_path;
}

int wrap(const char *filename, const char *container, const char *path) {
    int cfd = open(filename, O_RDONLY);
    if (cfd < 0) {
        printf("Unable to open %s for reading\n", filename);
        return -1;
    }
    int filename_len = strlen(filename);
    char *new_filename = (char *) malloc(filename_len + 2);
    strcpy(new_filename, filename);
    new_filename[filename_len] = '~';
    new_filename[filename_len + 1] = 0;
    int nfd = open(new_filename, O_RDWR | O_CREAT);
    if (nfd < 0) {
        printf("Unable to open %s for writing\n", new_filename);
        if (close(cfd) < 0) {
            printf("Unable to close %s\n", filename);
        }
        return -1;
    }
    char buffer[4096];
    int r = read(cfd, buffer, sizeof(buffer));
    while (r > 0) {
        if (write(nfd, buffer, r) < 0) {
            printf("Unable to write to %s\n", new_filename);
            if (close(cfd) < 0) {
                printf("Unable to close %s\n", filename);
            }
            if (close(nfd) < 0) {
                printf("Unable to close %s\n", new_filename);
            }
            return -1;
        }
        r = read(cfd, buffer, sizeof(buffer));
    }
    if (r < 0) {
        printf("Unable to read from %s\n", filename);
        if (close(cfd) < 0) {
            printf("Unable to close %s\n", filename);
        }
        if (close(nfd) < 0) {
            printf("Unable to close %s\n", new_filename);
        }
        return -1;
    }
    if (close(cfd) < 0) {
        printf("Unable to close %s\n", filename);
        return -1;
    }
    if (lseek(nfd, container_name_offset, SEEK_SET) < 0) {
        puts("Unable to find container name");
        return -1;
    }
    if (write(nfd, container, strlen(container)) < 0) {
        puts("Unable to write container name");
        return -1;
    }
    if (lseek(nfd, process_path_offset, SEEK_SET) < 0) {
        puts("Unable to find process path");
        return -1;
    }
    if (write(nfd, path, strlen(path)) < 0) {
        puts("Unable to write process path");
        return -1;
    }
    if (close(nfd) < 0) {
        printf("Unable to close %s\n", new_filename);
        return -1;
    }
    struct stat info;
    if (stat(filename, &info) < 0) {
        printf("Unable to stat %s\n", filename);
        return -1;
    }
    if (chmod(new_filename, (info.st_mode & 0555) | S_ISUID | S_ISGID) < 0) {
        puts("Unable to update file permissions");
        return -1;
    }
    if (unlink(filename) < 0) {
        printf("Unable to delete %s\n", filename);
        return -1;
    }
    if (rename(new_filename, filename) < 0) {
        printf("Unable to rename %s to %s\n", new_filename, filename);
        return -1;
    }
    return 0;
}
