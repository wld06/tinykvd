//
// Created by walid on 14/11/2026.
//

#include "../common/dynamic.h"
#include "../common/error.h"
#include "../common/connection.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERV_PORT 1234

static int32_t query(int fd, const char *text) {
    uint32_t len = (uint32_t)strlen(text);
    if (len > K_MAX_MSG) {
        return -1;
    }

    //send request
    char wbuf[4 + K_MAX_MSG];
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], text, len);

    int32_t err = write_all(fd, wbuf, 4 + len);
    if (err) { return err; }

    //4 bytes header
    char rbuf[4 + K_MAX_MSG];
    errno = 0;
    err = read_full(fd, rbuf, 4);
    if (err) {
        msg(errno == 0 ? "EOF" : "read() error"); // temp, it is not a good idea
        return err;
    }

    memcpy(&len, rbuf, 4);
    if (len > K_MAX_MSG) {
        msg("too long");
        return -1;
    }

    //reply body
    err = read_full(fd, &rbuf[4], len);
    if (err) {
        msg("read() error");
        return err;
    }

    //do something
    printf("server says: $.*s\n", len, rbuf[4]);
    return 0;
}

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }

    struct sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = ntohs(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //127.0.0.1
    int rv = connect(fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (rv) {
        die("connect");
    }

    char msg[] = "hello";
    write(fd, msg, strlen(msg));

    char rbuf[64] = {};
    ssize_t n = read(fd, rbuf, sizeof(rbuf) -1);

    if (n < 0) {
        die("read");
    }

    printf("server says: %s\n", rbuf);
    close(fd);
}
