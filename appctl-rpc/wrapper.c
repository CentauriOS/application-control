#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <common/limits.h>
#include <appctl-rpc/string.h>
#include <appctl-rpc/wrapper.h>

#define TEMPORARY_FILE "appctl~"

#ifdef DEBUG
#define LOG(msg) writestr(STDOUT_FILENO, msg)
#else
#define LOG(msg)
#endif

// These two variables will be set at compile time with dd, then again at runtime with wrap()
extern char container_name[MAX_CONTAINER_NAME];
char container_name[MAX_CONTAINER_NAME] = " ";

extern char process_path[MAX_RPC_COMMAND_LENGTH];
char process_path[MAX_RPC_COMMAND_LENGTH] = " ";

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
        LOG("Unable to open ");
        LOG(filename);
        LOG(" for reading\n");
        return -1;
    }
    int nfd = open(TEMPORARY_FILE, O_RDWR | O_CREAT, 0600);
    if (nfd < 0) {
        LOG("Unable to open " TEMPORARY_FILE " for writing\n");
        if (close(cfd) < 0) {
            LOG("Unable to close ");
            LOG(filename);
            LOG("\n");
        }
        return -1;
    }
    char buffer[256];
    int r = read(cfd, buffer, sizeof(buffer));
    while (r > 0) {
        if (write(nfd, buffer, r) < 0) {
            LOG("Unable to write to " TEMPORARY_FILE "\n");
            if (close(cfd) < 0) {
                LOG("Unable to close ");
                LOG(filename);
                LOG("\n");
            }
            if (close(nfd) < 0) {
                LOG("Unable to close " TEMPORARY_FILE "\n");
            }
            return -1;
        }
        r = read(cfd, buffer, sizeof(buffer));
    }
    if (r < 0) {
        LOG("Unable to read from ");
        LOG(filename);
        LOG("\n");
        if (close(cfd) < 0) {
            LOG("Unable to close ");
            LOG(filename);
            LOG("\n");
        }
        if (close(nfd) < 0) {
            LOG("Unable to close " TEMPORARY_FILE "\n");
        }
        return -1;
    }
    if (close(cfd) < 0) {
        LOG("Unable to close ");
        LOG(filename);
        LOG("\n");
        return -1;
    }
    if (lseek(nfd, container_name_offset, SEEK_SET) < 0) {
        LOG("Unable to find container name\n");
        return -1;
    }
    if (write(nfd, container, strlen(container)) < 0) {
        LOG("Unable to write container name\n");
        return -1;
    }
    if (lseek(nfd, process_path_offset, SEEK_SET) < 0) {
        LOG("Unable to find process path\n");
        return -1;
    }
    if (write(nfd, path, strlen(path)) < 0) {
        LOG("Unable to write process path\n");
        return -1;
    }
    if (close(nfd) < 0) {
        LOG("Unable to close " TEMPORARY_FILE "\n");
        return -1;
    }
    struct stat info;
    if (stat(filename, &info) < 0) {
        LOG("Unable to stat ");
        LOG(filename);
        LOG("\n");
        return -1;
    }
    if (chmod(TEMPORARY_FILE, (info.st_mode & 0555) | S_ISUID | S_ISGID) < 0) {
        LOG("Unable to update file permissions");
        return -1;
    }
    if (unlink(filename) < 0) {
        LOG("Unable to delete ");
        LOG(filename);
        LOG("\n");
        return -1;
    }
    if (rename(TEMPORARY_FILE, filename) < 0) {
        LOG("Unable to rename " TEMPORARY_FILE " to ");
        LOG(filename);
        LOG("\n");
        return -1;
    }
    return 0;
}
