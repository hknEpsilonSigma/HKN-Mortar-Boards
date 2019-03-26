
#include <msp430.h>
#include <driverlib.h>
#include <HKNHats.h>

int main(void)
{

    boardInit();
    xBee3_change_destination_address("4444", "EEEE");
    char *command = "Hello World!";
    uart_xBee3_transmit(command);

    while(1);
}

#pragma vector=EUSCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void)
{
    switch(__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            receive_buffer[buffer_position++ & (buffer_size - 1)] = UCA3RXBUF;
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
        default: break;
    }
}


