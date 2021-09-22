/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include <iostream>
#include <string>
#include <memory>
#include <chrono>

#include <sstream>
#include <iomanip>
#include <thread>
//#include <unistd.h>

#include "oDrive.h"
#include "pps.h"

int main() {

    const int second = 1000000;
    std::string ppsFile = "/sys/class/pps/pps0/assert";
    //pps * ppsOut = new pps(ppsFile);
    const std::string portName = "/dev/ttyACM0";
    std::unique_ptr<oDrive> odrive(new oDrive(portName));
    odrive->setState(0,odrive->AXIS_STATE_CLOSED_LOOP_CONTROL);
    auto now=std::chrono::system_clock::now();
    auto nowTime =  std::chrono::system_clock::to_time_t(now);
    auto start = std::chrono::steady_clock::time_point();
    std::stringstream ss;
    ss<<std::put_time(std::localtime(&nowTime),"%Y-%m-%d %X");
    std::cout<<"sys_clock::now() = "<< ss.str()<<std::endl;
    std::cout<<"Setting velocity to 2"<<std::endl;
    odrive->setVelocity(0,2);
    while(1)
    {

        if(std::chrono::steady_clock::now() - start> std::chrono::seconds(1))
        {
            nowTime =  std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss<<std::put_time(std::localtime(&nowTime),"%Y-%m-%d %X");
            std::cout <<"Time: "<< ss.str()<<std::endl;
            std::cout<<"________________________________________________"<<std::endl<<std::endl;

            std::cout<<"Pos Circular"<<std::endl;
            odrive->getPosCircular(0);
            std::cout<<"______________________________"<<std::endl<<std::endl;

            std::cout<<"Pos Estimate"<<std::endl;
            odrive->getPosCircular(0);
            std::cout<<"______________________________"<<std::endl<<std::endl;

            std::cout<<"Pos Estimate Counts"<<std::endl;
            odrive->getPosCircular(0);
            std::cout<<"______________________________"<<std::endl<<std::endl;
        }
        if(std::chrono::steady_clock::now()- start> std::chrono::seconds(10))
        {
            break;
        }
    }
    std::cout<<"Setting velocity to -1"<<std::endl;
    odrive->setVelocity(0,-1);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout<<"Setting velocity to 0"<<std::endl;odrive->setVelocity(0,0);
    odrive->setState(0,odrive->AXIS_STATE_IDLE);

    //odrive->commandConsole();
    return 0;
};
