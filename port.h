/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <iostream>
#include <string>
// Linux headers
#include <termios.h> // Contains POSIX terminal control definitions

#ifndef PORT_H_
#define PORT_H_


class port {

private:
    std::string m_portName;
	struct termios portSettings;

	int m_serialPort;
	/**
	 *
	 *
	 * @param portName
	 * @return
	 */
    int openPort(std::string portName);
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
    std::string charArrayToString(char * text,int size);
public:
	port();
    port(std::string portName);
    int writeToPort(std::string message);
    std::string readFromPort();
    int setPort(std::string portName);
    std::string getPort();
	virtual ~port();


};

#endif /* PORT_H_ */
