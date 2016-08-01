/*************************************************************************
	> File Name: list_timer.cpp
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年08月01日 星期一 11时50分03秒
	> Description:
 ************************************************************************/
#include <iostream>
#include <cstdlib>

#include "list_timer.h"

void list_timer::add_timer(util_timer &timer)
{
    auto it = timers.begin();
    
    while(it != timers.end()) {
        if (it->expire < timer.expire) {
            ++it;
        } else {
            break;
        }
    }
    
    timers.insert(it, timer);
}

decltype(list_timer::timers.begin()) list_timer::del_timer(util_timer &timer) 
{
    auto it = timers.begin();

    while(it != timers.end()) {
        if (it->expire == timer.expire && it->user_data.sockfd == timer.user_data.sockfd) {
            ++it;
        } else {
            break;
        }
    }
    return timers.erase(it);
}

void list_timer::tick()
{
    if (timers.size() == 0) {
        return;
    } else {
        time_t now = time(NULL);
        auto it = timers.begin();
        while (it != timers.end()) {
            if (now < it->expire) {
                break;
            } else {
                it->cb_func(&(it->user_data));
                it = this->del_timer(*it);
                std::cerr << it->user_data.sockfd << std::endl;
            }
        }
    }
}
