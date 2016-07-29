/*************************************************************************
	> File Name: select.c
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
#include <sys/select.h>
#include <string.h>
#include <unistd.h>
#include "list.h"

typedef struct node {
    int fd;
    struct node *pNext;
}Node;

int main(int argc, char *argv[])
{
    int new_fd, listen_fd;
    int on = 1, retuval, cli_addr_len, recv_len;
    int maxfd = 0;
    char buf[255];
    struct sockaddr_in serv_addr, cli_addr; //定义套接字地址
    fd_set readfds, tmpfds;
    Node *pHead, *pTemp, *pNew;

    //创建socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_fd < 0) {
        perror("Socket open");
        return EXIT_FAILURE;
    }

    if (maxfd < listen_fd) {
        maxfd = listen_fd;
    }
    
    //创建链表
    list_creat(pHead, Node);
    pNew = (Node *)malloc(sizeof(Node));
    pNew->fd = listen_fd;
    add_tial(pHead, pNew, Node);
    
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
    
    FD_ZERO(&readfds);
    FD_SET(listen_fd, &readfds);
    tmpfds = readfds; 

    //加入监控集合
    while (1) {
        readfds = tmpfds;
        retuval = select(maxfd + 1,&readfds, NULL, NULL, NULL);
        
        if (retuval == -1) {
            perror("select");
            return EXIT_FAILURE;
        } else if (retuval > 0) {
            pTemp = pHead->pNext;
            while (pTemp) {
                if (FD_ISSET(pTemp->fd, &readfds)) {
                    if (pTemp->fd != listen_fd) {
                        memset(buf, 0, 255);
                        recv_len = recv(pTemp->fd, buf, 255, 0);
                        if (recv_len > 0) {
                            printf("客户端发数据啦~~\n");
                            printf("%s", buf);
                        } else if(recv_len == 0) {
                            printf("客户端断啦~~\n");
                            close(pTemp->fd);
                            FD_CLR(pTemp->fd, &tmpfds);
                            del_node(pHead, pTemp, Node);
                        } else {
                            perror("recv");
                        }
                    } else {
                        new_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
                        if (new_fd > maxfd) {
                            maxfd = new_fd;
                        }
                        if (new_fd < 0) {
                            perror("accept");
                            continue;
                        }
                        FD_SET(new_fd, &tmpfds);
                        pNew = (Node *)malloc(sizeof(Node));
                        pNew->fd = new_fd;
                        add_tial(pHead, pNew, Node);
                        printf("新的客户端连接啦~~\n");
                    }
                }
                pTemp = pTemp->pNext;
            }
        }
    }

    return EXIT_SUCCESS;
}
