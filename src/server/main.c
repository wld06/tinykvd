//
// Created by walid on 14/11/2026.
//

#include <assert.h>

#include "../common/dynamic.h"
#include "../common/error.h"
#include "../common/connection.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 1234
#define WILDCARD_IP 0


static int32_t one_request(int connfd) {
    // 4 bytes header
    char rbuf[4 + K_MAX_MSG];
    errno = 0;
    int32_t err = read_full(connfd, rbuf, 4);

    if (err) {
        msg(errno == 0 ? "EOF" : "read() error"); //if its an internal error, errno changes
        return err;
    }

    uint32_t len = 0;
    memcpy(&len, rbuf, 4);

    if (len > K_MAX_MSG) {
        msg("too long");
        return -1;
    }

    //request body
    err = read_full(connfd, &rbuf[4], len);
    if (err) {
        msg("read() error");
        return err;
    }

    //do something
    printf("client says: %.*s\n", (int)len, &rbuf[4]);

    //reply
    const char reply[] = "world";
    char wbuf[4 + sizeof(reply)];
    len = (uint32_t)strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(connfd, wbuf, 4 + len);
}

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //socket option
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    //bind address
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(WILDCARD_IP);
    int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) { die("bind()"); }

    //listen
    rv = listen(fd, SOMAXCONN);
    if (rv) {die("listen()");}

    while (1) {
        //accept
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);

        if (connfd < 0) {
            continue; //error
        }

        while (1) {
            int32_t err = one_request(connfd);
            if (err) {
                break;
            }
        }

        close(connfd);
    }
}