/*************************************************************************
	> File Name: 6_4.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2016年03月09日 星期三 21时15分28秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE

extern char **environ;

int main(int argc, char *argv[])
{
    char **p;
    int i;

    if (clearenv()) {
        printf("ClearError!\n");
    }

    for (i = 1; i < argc; ++i) {
        if (putenv(argv[i])) {
            printf("%s添加失败\n", argv[i]);
        }
    }

    if (setenv("GREET", "HelloWorld", 0) == -1) {
        printf("SetenvError!\n");
    }

    for (p = environ; p != NULL && *p != NULL; ++p) {
        printf("%s\n", *p);
    }

    
    return EXIT_SUCCESS;
}
