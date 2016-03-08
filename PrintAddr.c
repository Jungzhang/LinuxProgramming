/*************************************************************************
	> File Name: PrintAddr.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2016年03月08日 星期二 22时15分45秒
	> Description: 打印程序的文本段、初始化数据段、未初始化数据段尾地址的
    下一个地址
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    extern char etext, edata, end;

    printf("%p\n%p\n%p\n", &etext, &edata, &end);
    
    return EXIT_SUCCESS;
}
