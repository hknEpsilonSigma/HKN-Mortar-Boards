/*
 * uart.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#include "HKNHats.h"

/*
 * Uart Macros
 */
#define indexBoundaryCheck    if(uartReceiveLifoBuffer.indexPointer > LIFO_BUFFER_SIZE) \
        return; \
    else if(uartReceiveLifoBuffer.indexPointer < 0) \
        return; \

/*
 * Initialize uart for ZigBee operation
 */
void uartInit() {
    WDTCTL = WDTPW | WDTHOLD;               // Stop Watchdog

    // Configure GPIO
    P6SEL1 &= ~(BIT0 | BIT1);
    P6SEL0 |= (BIT0 | BIT1);                // USCI_A3 UART operation

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings

    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;           // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // Set all dividers
    CSCTL0_H = 0;                           // Lock CS registers

    EUSCI_A_UART_init( EUSCI_A3_BASE , &RFUartSettings);

    EUSCI_A_UART_enable( EUSCI_A3_BASE );

    EUSCI_A_UART_enableInterrupt( EUSCI_A3_BASE , EUSCI_A_UART_RECEIVE_INTERRUPT);

    __bis_SR_register(GIE);     // Enter LPM3, interrupts enabled
    __no_operation();
}

#pragma vector=EUSCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void)
{
    switch(__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            writeToUartReceiveLifoBuffer(); //Receive to LIFO buffer
            break;
        case USCI_UART_UCTXIFG:
//            while(!(UCA3IFG & UCTXIFG));
//            _no_operation();
            break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
        default: break;
    }
}

void writeToUartReceiveLifoBuffer(void)
{
    indexBoundaryCheck;
    uartReceiveLifoBuffer.lifoBuffer[uartReceiveLifoBuffer.indexPointer] = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
    uartReceiveLifoBuffer.indexPointer++;
}

char readFromUartReceiveLifoBuffer(void)
{
    uartReceiveLifoBuffer.indexPointer--;
    indexBoundaryCheck;
    return uartReceiveLifoBuffer.lifoBuffer[uartReceiveLifoBuffer.indexPointer];
}
