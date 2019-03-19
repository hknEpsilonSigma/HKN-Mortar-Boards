/*
 * XBee.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#ifndef XBEE_H_
#define XBEE_H_

#include "HKNHats.h"

/*
 * initialize xBee settings locally through uart
 */
void xBee3_init(void);

/*
 * transmit a message from uC to xBee through uart
 */
void uart_xBee3_transmit(char *message);

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee3_radio_transmit(char *message);

/*
 * Receive a string from UART
 */
void xBee3_uart_receive_string(void);

/*
 * Receive an "OK" string from UART
 */
int xBee3_uart_receive_OK(void);

#endif /* XBEE_H_ */
