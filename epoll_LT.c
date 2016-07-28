/*************************************************************************
	> File Name: epoll_LT.c
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
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>

#define MAXCLIENT 65535
#define BUFF_SIZE 255

int main(int argc, char *argv[])
{
    int new_fd, listen_fd, epoll_fd;
    int on = 1, retuval, cli_addr_len, recv_len, count = 0;
    char buf[BUFF_SIZE];
    struct sockaddr_in serv_addr, cli_addr; //定义套接字地址
    struct epoll_event events[MAXCLIENT], event;

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

    //创建epoll描述符
    epoll_fd = epoll_create(MAXCLIENT);
    
    //加入监控集合
    event.data.fd = listen_fd;
    event.events = EPOLLIN;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) < 0) {
        perror("Add listen fd");
        return EXIT_FAILURE;
    }
    ++count;

    while (1) {
        retuval = epoll_wait(epoll_fd, events, MAXCLIENT, -1);
        if (retuval == -1) {
            perror("epoll_wait");
            return EXIT_FAILURE;
        } else if (retuval > 0) {
            for (int i = 0; i < retuval; ++i) {
                if (events[i].events & EPOLLIN) {
                    if (events[i].data.fd != listen_fd) {
                        memset(buf, 0, BUFF_SIZE);
                        recv_len = recv(events[i].data.fd, buf, BUFF_SIZE-1, 0);
                        if (recv_len > 0) {
                            printf("客户端发数据啦~~\n");
                            printf("%s", buf);
                        } else if(recv_len == 0) {
                            --count;
                            printf("客户端断啦~~\n");
                            //关闭文件描述符会自动从epoll兴趣列表中清除
                            close(events[i].data.fd);  
                        } else {
                            perror("recv");
                        }
                    } else {
                        new_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
                        if (new_fd < 0) {
                            perror("accept");
                            continue;
                        }
                        event.data.fd = new_fd;
                        event.events = EPOLLIN;
                        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &event) < 0 || count >= MAXCLIENT) {
                            perror("Add listen fd");
                            printf("客户端未连接成功\n");
                            close(new_fd);
                        }
                        ++count;
                        printf("新的客户端连接啦~~\n");
                    }
                } else {
                    printf("发生了未知错误\n");
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
