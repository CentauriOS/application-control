#ifndef CENTAURI_STRING_H
#define CENTAURI_STRING_H

int streq(const char *s1, const char *s2);

char *strcpy(char *dest, const char *src);

size_t strlen(const char *str);

void writestr(int fd, const char *str);

#endif
