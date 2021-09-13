/*
 * port.h
 *
 *  Created on: 9. 8. 2021
 *      Author: martinek
 */
//#include <cstring>
#include <iostream>
#include <string>
// Linux headers
#include <termios.h> // Contains POSIX terminal control definitions

#ifndef PORT_H_
#define PORT_H_

using namespace std;


class port {

private:
	string m_portName;
	struct termios portSettings;

	int m_serialPort;
	/**
	 *
	 *
	 * @param portName
	 * @return
	 */
	int openPort(string portName);
	/**
	 * closePort
	 * Closing port used for communication, after close, the port needs to be reopen.
	 * @return
	 */
	int closePort();
	int setInterfaceAttribs(int fd, int speed, int parity);
	void setBlocking(int fd, int shouldBlock);
	/**
	 * charArrayToString
	 * Convert char array returned from read() to string for easy output
	 * @param text Returned text
	 * @param size Size of returned text
	 * @return
	 */
	string charArrayToString(char * text,int size);
public:
	port();
	port(string portName);
	int writeToPort(string message);
	string readFromPort();
	int setPort(string portName);
	string getPort();
	virtual ~port();


};

#endif /* PORT_H_ */
