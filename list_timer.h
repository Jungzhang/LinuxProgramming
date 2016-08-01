/*************************************************************************
	> File Name: list_timer.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年08月01日 星期一 10时20分08秒
	> Description:
 ************************************************************************/
#ifndef _LIST_TIMER_H
#define _LIST_TIMER_H

#include <netinet/in.h>
#include <list>
#include <memory>

#ifndef _TIMER_MSG_BUFFER_SIZE_
#undef _TIMER_MSG_BUFFER_SIZE_
#define _TIMER_MSG_BUFFER_SIZE_ 255
#endif

struct client_data {
    struct sockaddr_in address;    //客户端IP地址
    int sockfd;             //客户端sockfd;
    char buf[_TIMER_MSG_BUFFER_SIZE_];
};

class util_timer {

    friend class list_timer;

private:
    //时间到时的回调函数
    void (*cb_func)(const client_data *);

public:
    util_timer(const time_t expire, client_data user_data, decltype(cb_func) func)
                : expire(expire), user_data(user_data), cb_func(func) {}

private:
    const time_t expire;    //任务超时时间,使用绝对时间
    client_data user_data;     //回调函数的参数
};

class list_timer {
private :
    std::list<util_timer> timers;
public :
    void add_timer(util_timer &timer);
    decltype(timers.begin()) del_timer(util_timer &timer);
    void tick();
};
#endif
