/*************************************************************************
	> File Name: signal.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月29日 星期五 09时59分14秒
	> Description: signal函数使用
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void print(int sg)
{
    printf("Hello Linux\n");
}

int main(int argc, char *argv[])
{

    while(1) {
        signal(SIGINT, print);
        printf("Hello World\n");
        sleep(1);
    }

    return EXIT_SUCCESS;
}
