/*
 * XBee.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#ifndef XBEE_H_
#define XBEE_H_

#include "HKNHats.h"

/***********************************************************Level 1 Functions ******************************************************/

/*
 * transmit a message from uC to xBee through uart
 */
void uart_xBee_transmit(char *message);

/*
 * Receive an "OK" string from UART
 */
int xBee3_uart_receive_OK(void);

/***********************************************************Level 2 Functions ******************************************************/

/*
 * Enter command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_enter_command_mode();

/*
 * Exit command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_exit_command_mode();

/*
 * Send command only, return 1 if success and 0 otherwise
 */
int uart_xBee3_send_command_only(char *pointer);

/***********************************************************Level 3 Functions ******************************************************/
/*
 * initialize xBee settings locally through uart
 */
int xBee_init(void);

/*
 * Send a single whole command with auto-enter and exit
 */
int uart_xBee3_send_command(char *pointer);

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee_radio_transmit(char *message);


#endif /* XBEE_H_ */
