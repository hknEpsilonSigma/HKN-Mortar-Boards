/*
 * XBee.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#include "HKNHats.h"

/***********************************************************Level 1 Functions ******************************************************/

/*
 * transmit a message from uC to xBee through uart
 */
void uart_xBee_transmit(char *message) {
    while(*message != 0) {
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, *message);
        message++;
    }
}

/*
 * Receive an "OK" string from UART
 * Return 0 if fail, return 1 if succeed
 */
int xBee3_uart_receive_OK(void) {
    //compare received string with "OK\r"
    char *OK_string = "OK\r";

    //if any char comparisons fail, return 0
    for (uint8_t i = 0; i < 3; i++) {
        if (EUSCI_A_UART_receiveData(EUSCI_A3_BASE) != OK_string[i])
            return 0;
    }

    //if success, return 1
    return 1;
}

/***********************************************************Level 2 Functions ******************************************************/

/*
 * Enter command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_enter_command_mode() {
    char *pointer = "+++";
    uart_xBee_transmit(pointer);
    return xBee3_uart_receive_OK();
    _delay_cycles(9000000);
}

/*
 * Exit command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_exit_command_mode() {
    char *pointer = "ATCN";
    uart_xBee_transmit(pointer);
    return xBee3_uart_receive_OK();
    _delay_cycles(1000000);
}

/*
 * Send command only, return 1 if success and 0 otherwise
 */
int uart_xBee3_send_command_only(char *pointer) {
    uart_xBee_transmit(pointer);
    return xBee3_uart_receive_OK();
    _delay_cycles(1000000);
}

/***********************************************************Level 3 Functions ******************************************************/


/*
 * initialize xBee settings locally through uart
 */
int xBee_init() {
    if (!uart_xBee3_enter_command_mode())
        return 0;

    if (!uart_xBee3_send_command_only("ATDH 0\r"))
        return 0;

    if (!uart_xBee3_send_command_only("ATDL FFFF\r"))
        return 0;

    if (!uart_xBee3_send_command_only("ATWR\r"))
        return 0;

    if (!uart_xBee3_exit_command_mode())
        return 0;

    return 1;
}

/*
 * Send a single whole command with auto-enter and exit
 */
int uart_xBee3_send_command(char *pointer) {
    if (!uart_xBee3_enter_command_mode())
        return 0;

    if (!uart_xBee3_send_command_only(pointer))
        return 0;

    if (!uart_xBee3_exit_command_mode())
        return 0;

    return 1;
}

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee_radio_transmit(char *message) {
    uart_xBee_transmit(message);
}







