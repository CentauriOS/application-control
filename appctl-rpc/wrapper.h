#ifndef CENTAURI_WRAPPER_H
#define CENTAURI_WRAPPER_H

int is_process_wrapper();

const char *get_process_wrapper_container();

const char *get_process_wrapper_path();

int wrap(const char *filename, const char *container, const char *path);

#endif
