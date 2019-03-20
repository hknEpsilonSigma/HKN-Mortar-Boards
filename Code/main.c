
#include <msp430.h>
#include <driverlib.h>
#include <HKNHats.h>



int main(void)
{

    boardInit();

    char *command = "Hello World!";


        //while(1){
        //EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'C');

        /*EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '+');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '+');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '+');

        _delay_cycles(9000000);

        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'A');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'T');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'D');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'H');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, ' ');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'B');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '\r');

        _delay_cycles(1000000);

        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'A');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'T');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'W');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'R');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '\r');

        _delay_cycles(1000000);

        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'A');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'T');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'C');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, 'N');
        EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '\r');*/

        //EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '+');


        xbee3_broadcast(command);
        //_delay_cycles(15000000);
    //}

    while(1);



}


#pragma vector=EUSCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void)
{
    switch(__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG: break;
        case USCI_UART_UCTXIFG:
            while(!(UCA3IFG & UCTXIFG));
            _no_operation();
            break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
        default: break;
    }
}


