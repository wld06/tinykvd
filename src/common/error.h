//
// Created by walid on 26/11/2026.
//

#ifndef TINYKVD_ERROR_H
#define TINYKVD_ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//FATAL ERROR: prints the msg and aborts
static inline void die_at(const char *file, int line, const char *msg) {
    int err = errno;
    fprintf(stderr, "[FATAL] %s:%d: %s: %s (errno %d)\n",
        file, line, msg, strerror(err), err);
    abort();
}

//WARNING NON FATAL
static inline void msg_at(const char *file, int line, const char *msg) {
    fprintf(stderr, "[WARN] %s:%d: %s\n", file, line, msg);
}

//macros

#define die(msg) die_at(__FILE__, __LINE__, (msg))
#define msg(msg) msg_at(__FILE__, __LINE__, (msg))

#endif //TINYKVD_ERROR_H
