/*
 * gpio.h
 *
 *  Created on: 13. 8. 2021
 *      Author: martinek
 */

#ifndef GPIO_H_
#define GPIO_H_

class gpio {
public:
	gpio(int pin);
	enum{GPIO_IN,GPIO_OUT};
	int setPin(int io);
	int getPin();
	virtual ~gpio();
private:
	int exportPin(int pin);
	bool m_exported=false;
	int m_fd=-1;
};

#endif /* GPIO_H_ */
