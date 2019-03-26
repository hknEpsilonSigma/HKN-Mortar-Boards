/*
 * xBee3.c
 *
 */

#include "HKNHats.h"

char received_string[10];

/***********************************************************Level 1 Functions ******************************************************/

/*
 * transmit a message from uC to xBee through UART
 */
void uart_xBee3_transmit(char * data) {
    while(*data != 0) {
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, *data);
        data++;
    }
}

/*
 * Check for "OK\r" from UART
 * Return 0 if fail, return 1 if succeed
 */
uint32_t xBee3_uart_check_OK() {
    //compare receive buffer to "OK\r"
    uint32_t timeout = 9000000;
    while(timeout--)
    {
        if(receive_buffer[(buffer_position - 1) & (buffer_size - 1)] == 0xD)
        {
            if((receive_buffer[(buffer_position - 3) & (buffer_size - 1)] == 0x4F) && (receive_buffer[(buffer_position - 2) & (buffer_size - 1)] == 0x4B))
            {
                //if success, return 1
                return 1;
            }
            else
            {
                break;
            }
        }
    }

    //if fail, return 1
    return 0;
}

/***********************************************************Level 2 Functions ******************************************************/

/*
 * Enter command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_enter_command_mode() {
    uart_xBee3_transmit("+++");
    return 1;
}

/*
 * Exit command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_exit_command_mode() {
    char *pointer = "ATCN";
    uart_xBee3_transmit(pointer);

//    if(!xBee3_uart_receive_OK())
//        return 0;

    //_delay_cycles(1000000);
    return 1;
}

/*
 * Send command only, return 1 if success and 0 otherwise
 */
int uart_xBee3_send_command_only(char *pointer) {
    uart_xBee3_transmit(pointer);
    return 1;
}

/***********************************************************Level 3 Functions ******************************************************/


/*
 * initialize xBee settings locally through uart
 */
int xBee3_init() {
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
 * Send a single whole command with enter and exit
 */
//int uart_xBee3_send_command(char *pointer) {
//    if (!uart_xBee3_enter_command_mode())
//        return 0;
//
//    if (!uart_xBee3_send_command_only(pointer))
//        return 0;
//
//    if (!uart_xBee3_exit_command_mode())
//        return 0;
//
//    return 1;
//}

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee3_radio_transmit(char *message)
{
    uart_xBee3_transmit(message);
}

uint32_t xBee3_change_destination_address(char * destination_high, char * destination_low)
{
    UART_XBEE3_SEND_COMMAND(ENTER_COMMAND_MODE);
    if(!xBee3_uart_check_OK()) {return 0;}
    UART_XBEE3_SEND_COMMAND_WITH_PARAMETER(DESTINATION_ADDRESS_HIGH,destination_high);
    if(!xBee3_uart_check_OK()) {return 0;}
    UART_XBEE3_SEND_COMMAND_WITH_PARAMETER(DESTINATION_ADDRESS_LOW,destination_low);
    if(!xBee3_uart_check_OK()) {return 0;}
    UART_XBEE3_SEND_COMMAND(WRITE_FIRMWARE); //remove from function and add a seperate write function
    if(!xBee3_uart_check_OK()) {return 0;}
    UART_XBEE3_SEND_COMMAND(EXIT_COMMAND_MODE);

    return 1;
}
