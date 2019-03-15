#include <msp430.h>
#include <eusci_a_uart.h>

#ifndef XBEE3_H_
#define XBEE3_H_

#define ENTER_AT_COMMAND_MODE "+++"

void xbee3_initialize();

void xbee3_broadcast(char *);

void xbee3_uart_receive_string(char *);


#endif /* XBEE3_H_ */
