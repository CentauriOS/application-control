#include <unistd.h>
#include <appctl-rpc/string.h>

int streq(const char *s1, const char *s2) {
    while (*s1 == *s2 && *s1 && *s2) {
        ++s1;
        ++s2;
    }
    return *s1 == *s2;
}

size_t strlen(const char *str) {
    size_t len = 0;
    while (*str++) {
        ++len;
    }
    return len;
}

void writestr(int fd, const char *str) {
    write(fd, str, strlen(str));
}
