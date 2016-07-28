/*************************************************************************
	> File Name: poll.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月27日 星期三 16时33分07秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>
#include "list.h"

#define MAXCLIENT 65535

int main(int argc, char *argv[])
{
    int new_fd, listen_fd;
    int on = 1, retuval, cli_addr_len, recv_len;
    int count = 0;
    char buf[255];
    struct sockaddr_in serv_addr, cli_addr; //定义套接字地址
    struct pollfd fds[MAXCLIENT];

    //创建socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_fd < 0) {
        perror("Socket open");
        return EXIT_FAILURE;
    }
    
    //将端口设置可重用
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("Setsockopt");
        return EXIT_FAILURE;
    }

    //初始化地址信息
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;  //IPV4
    serv_addr.sin_port = htons(9000); //设置端口
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);   //监控所有网卡过来的数据

    //绑定端口
    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0) {
        perror("Bind");
        return EXIT_FAILURE;
    }

    //将套接字转化为监听套接字
    if (listen(listen_fd, 256) < 0) {
        perror("Listen");
        return EXIT_FAILURE;
    }
    fds[count].fd = listen_fd;
    fds[count].events = POLLIN;
    ++count;

    while (1) {
        retuval = poll(fds, count, -1);
        if (retuval == -1) {
            perror("poll");
            return EXIT_FAILURE;
        } else if (retuval > 0) {
            for (int i = 0; i < count; ++i) {
                if (fds[i].revents & POLLIN) {
                    if (fds[i].fd != listen_fd) {
                        memset(buf, 0, 255);
                        recv_len = recv(fds[i].fd, buf, 255, 0);
                        if (recv_len > 0) {
                            printf("客户端发数据啦~~\n");
                            printf("%s", buf);
                        } else if(recv_len == 0) {
                            printf("客户端断啦~~\n");
                            close(fds[i].fd);
                            fds[i] = fds[count - 1];
                            --count;
                            --i;
                        } else {
                            perror("recv");
                        }
                    } else {
                        new_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
                        if (new_fd < 0) {
                            perror("accept");
                            continue;
                        }
                        if (count >= MAXCLIENT) {
                            char msg[] = "很抱歉，暂时不能为您提供服务";
                            send(new_fd, msg, strlen(msg), 0);
                            close(new_fd);
                        }
                        fds[count].fd = new_fd;
                        fds[count].events = POLLIN;
                        ++count;
                        printf("新的客户端连接啦~~\n");
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
