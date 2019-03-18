#include <msp430.h>
#include <eusci_a_uart.h>
#include <xbee.h>

void xbee3_initialize()
{

}

char receive_message[3];

void xbee3_uart_transmit(char *message)
{
    while(*message != 0)
    {
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, *message);
        //while(!UCTXCPTIFG);

        message++;
    }
}


void xbee3_broadcast(char *message)
{
    char *pointer = ENTER_AT_COMMAND_MODE;
    xbee3_uart_transmit(pointer);
    _delay_cycles(9000000);

    char *destination_address_high = "ATDH 0\r";

    xbee3_uart_transmit(destination_address_high);

    _delay_cycles(1000000);

    char *destination_address_low = "ATDL FFFF\r";

    xbee3_uart_transmit(destination_address_low);

    _delay_cycles(1000000);

    char *save_settings = "ATWR\r";

    xbee3_uart_transmit(save_settings);

    _delay_cycles(1000000);


    char *command_null = "ATCN\r";

    xbee3_uart_transmit(command_null);

    _delay_cycles(1000000);

    xbee3_uart_transmit(message);


}


void xbee3_uart_receive_string(char *receive_message)
{

    uint8_t data;
    uint8_t i = 0;
    while(data != 0){
        data = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
        receive_message[i++] = data;
    }
}

        //set Network ID
        /*
         *
         */

        //set Channel

        //read Serial High
        //read Serial Low

        //write Node Identifier **Optional**

        //Device Role



