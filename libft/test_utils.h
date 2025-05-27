#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stddef.h>  

typedef struct {
    char     name[32];
    size_t   passed;
    size_t   failed;
} FuncStats;

FuncStats *get_stats(const char *func_name);

#endif

