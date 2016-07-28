/*************************************************************************
	> File Name: ChEnvOfPro.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2016年03月10日 星期四 13时19分11秒
	> Description: 验证子进程继承父进程的环境变量,和其环境变量的独立性
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    char **p;
    
    //为与系统环境变量区分开特在父进程中加入一个元系统中没有的环境变量
    putenv("Zhang = Jung");

    switch(pid) {
    case 0:
        {
            FILE *fp = fopen("./child.txt", "w");
            //清空从父进程继承而来的环境变量,如果没有此语句文件child.txt和parent.txt是相同的
            //足以说明父子进程的环境变量的更改互不影响对方
            clearenv();
            for (p = environ; p != NULL && *p!= NULL; ++p) {
                fprintf(fp, "%s\n", *p);
            }
            fclose(fp);
        }
        break;
    case -1:
        printf("失败\n");   break;
    default:
        {
            wait(NULL);
            FILE *fp = fopen("./parent.txt", "w");
            for (p = environ; p != NULL && *p!= NULL; ++p) {
                fprintf(fp, "%s\n", *p);
            }
            fclose(fp);
        }
        break;
    }
    
    return EXIT_SUCCESS;
}
