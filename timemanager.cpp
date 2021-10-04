#include "timemanager.h"
#include <iostream>
#include <chrono>
#include <iomanip>

timeManager::timeManager()
{

}

void timeManager::sleep(int seconds)
{
    auto timer = std::chrono::seconds(1);
    auto now=std::chrono::system_clock::now();
    auto start = std::chrono::steady_clock::now();
    while(1)
    {

        if(std::chrono::steady_clock::now() - (start+timer) > std::chrono::seconds(1))
        {
            timer = timer+std::chrono::seconds(1);
            now=std::chrono::system_clock::now();
            }
        if(std::chrono::steady_clock::now()- start> std::chrono::seconds(seconds))
        {
            break;
        }
    }
}

/*template<typename F>
bool timeManager::stopWatch<F>(F f)
{
    std::cout<<"dw"<<std::endl;
}*/
