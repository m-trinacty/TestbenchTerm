/*
 * gpio.cpp
 *
 *  Created on: 13. 8. 2021
 *      Author: martinek
 */

#include "gpio.h"
//C++ headers
#include <iostream>


//C headers
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include <string.h>
#include <errno.h>

using namespace std;


#define MAX_DIGITS	3
#define	EXPORT_PATH	"/sys/class/gpio/gpio"

gpio::gpio(int pin) {
	// TODO Auto-generated constructor stub

}

int gpio::setPin(int io){

}
int gpio::getPin(){

}


int gpio::exportPin(int pin){
	int fd;
	char const * charPin = to_string(pin).c_str();
	fd = open(EXPORT_PATH,O_WRONLY);
	if(fd<=0){
		cout<< "ERROR Unable to open export file"<< endl;
		return EXIT_FAILURE;
	}
	if (write(fd,charPin,strlen(charPin))) {
		if (errno!=EBUSY) {
			cout<<"ERROR Pin was already exported"<<endl;
			close(fd);
			return EXIT_FAILURE;
		}
		cout<<"ERROR Unable to export file"<<endl;
	}
	cout<<"Exported succesfully"<<endl;

	close(fd);
	return EXIT_SUCCESS;

}

gpio::~gpio() {
	// TODO Auto-generated destructor stub
}

