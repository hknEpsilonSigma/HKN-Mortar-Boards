

#ifndef XBEE3_H_
#define XBEE3_H_

#include <msp430.h>
#include <eusci_a_uart.h>

#define ENTER_AT_COMMAND_MODE "+++"

void xbee3_initialize();

void xbee3_broadcast(char *);

void xbee3_uart_receive_string(char *);

void xbee3_uart_transmit(char *);


#endif /* XBEE3_H_ */
