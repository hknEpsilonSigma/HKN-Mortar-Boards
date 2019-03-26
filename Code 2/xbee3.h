
#ifndef XBEE3_H_
#define XBEE3_H_

#define UART_XBEE3_SEND_COMMAND(command) uart_xBee3_transmit(command)
#define UART_XBEE3_SEND_COMMAND_WITH_PARAMETER(command, parameter) \
{ \
    uart_xBee3_transmit(command); \
    uart_xBee3_transmit(parameter); \
    uart_xBee3_transmit("\r"); \
}

#define ENTER_COMMAND_MODE "+++"
#define EXIT_COMMAND_MODE "ATCN\r"
#define WRITE_FIRMWARE "ATWR\r"
#define DESTINATION_ADDRESS_HIGH "ATDH"
#define DESTINATION_ADDRESS_LOW "ATDL"

#include "HKNHats.h"

/***********************************************************Level 1 Functions ******************************************************/

/*
 * transmit a message from uC to xBee through UART
 */
void uart_xBee3_transmit(char *);

/*
 * Receive an "OK" string from UART
 */
uint32_t xBee3_uart_check_OK(void);

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
//int uart_xBee3_send_command_only(char *);

/***********************************************************Level 3 Functions ******************************************************/
/*
 * initialize xBee settings locally through UART
 */
int xBee3_init(void);

/*
 * Send a single whole command with auto-enter and exit
 */
int uart_xBee3_send_command(char *);

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee3_radio_transmit(char *);

uint32_t xBee3_change_destination_address(char *,char *);

#endif /* XBEE3_H_ */
