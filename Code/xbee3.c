/*
 * XBee.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#include "HKNHats.h"

char OK_message[3];
char received_string[10]; // Not size to make

/*
 * initialize xBee settings locally through uart
 */
void xBee3_init() 
{
    char *pointer = "+++";
    uart_xBee_transmit(pointer);
    _delay_cycles(9000000);

    char *destination_address_high = "ATDH 0\r";
    uart_xBee_transmit(destination_address_high);
    _delay_cycles(1000000);

    char *destination_address_low = "ATDL FFFF\r";
    uart_xBee_transmit(destination_address_low);
    _delay_cycles(1000000);

    char *save_settings = "ATWR\r";
    uart_xBee_transmit(save_settings);
    _delay_cycles(1000000);

    char *command_null = "ATCN\r";
    uart_xBee_transmit(command_null);
    _delay_cycles(1000000);
}

/*
 * transmit a message from uC to xBee through uart
 */
void uart_xBee3_transmit(char *message) 
{
    while(*message != 0) 
    {
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, *message);
        message++;
    }
}

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee3_radio_transmit(char *message) 
{
    uart_xBee_transmit(message);
}

/*
 * Receive a string from UART
 */
void xBee3_uart_receive_string(void)
{
    uint8_t data;
    uint8_t i = 0;
    while(data != 0)
    {
        data = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
        received_string[i++] = data;
    }
}

/*
 * Receive an "OK" string from UART
 */
int xBee3_uart_receive_OK(void)
{
    char *OK_string = "\rOK";

    OK_message[0] = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
    OK_message[1] = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
    OK_message[2] = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);

    for(uint8_t i = 0;i < 3;i++)
    {
        if(OK_message[i] != OK_string[i])
        {
            return 0;
        }
    }
    return 1;
}

