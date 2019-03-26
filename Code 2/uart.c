/*
 * uart.c
 *
 */

#include "HKNHats.h"

/*
 * Initialize UART for ZigBee operation
 */
void uartInit() {
    // Configure GPIO
    P6SEL1 &= ~(BIT0 | BIT1);
    P6SEL0 |= (BIT0 | BIT1);                // USCI_A3 UART operation

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings

    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;           // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // Set all dividers
    CSCTL0_H = 0;                           // Lock CS registers

    EUSCI_A_UART_init( EUSCI_A3_BASE , &RFUartSettings);

    EUSCI_A_UART_enable( EUSCI_A3_BASE );

    EUSCI_A_UART_enableInterrupt( EUSCI_A3_BASE , EUSCI_A_UART_RECEIVE_INTERRUPT);

    __bis_SR_register(GIE);     // interrupts enabled
    __no_operation();
}
