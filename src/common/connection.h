//
// Created by walid on 26/11/2026.
//

#ifndef TINYKVD_CONNECTION_H
#define TINYKVD_CONNECTION_H
#define K_MAX_MSG 4096

static inline  int32_t read_full(int fd, char *buf, size_t n) {
    while (n > 0) {
        ssize_t rv = read(fd, buf, n);
        if (rv <= 0){ return -1; }

        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }

    return 0;
}

static inline  int32_t write_all(int fd, const char *buf, size_t n) {
    while (n > 0) {
        ssize_t rv = write(fd, buf, n);
        if ( rv <= 0 ){ return -1; }

        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }

    return 0;
}
#endif //TINYKVD_CONNECTION_H
