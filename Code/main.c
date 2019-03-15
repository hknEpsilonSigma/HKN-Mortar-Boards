
#include <msp430.h>
#include <driverlib.h>
#include <xbee.h>




static EUSCI_A_UART_initParam RFUartSettings = {

    //Set ACLK clocksource
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,

    /*
    // Baud Rate calculation
    // 8000000/(16*9600) = 52.083
    // Fractional portion = 0.083
    // User's Guide Table 21-4: UCBRSx = 0x04
    // UCBRFx = int ( (52.083-52)*16) = 1
    UCA3BRW = 52;                           // 8000000/16/9600
    UCA3MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
    */

    //Prescale value smclk/Baudrate
    52,
    //BRF value <- Not sure about this
    0x01,
    //BRS value <- Not sure about this
    0x49,
    //No Parity
    EUSCI_A_UART_NO_PARITY,
    //LSB first
    EUSCI_A_UART_LSB_FIRST,
    //One stop bit
    EUSCI_A_UART_ONE_STOP_BIT,
    //UART mode
    EUSCI_A_UART_MODE,
    //Oversampling en
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

};


int main(void)
{

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


    char *command = "Hello World!";

    void xbee3_broadcast(command);


    __bis_SR_register(LPM3_bits | GIE);     // Enter LPM3, interrupts enabled
    __no_operation();


}

#pragma vector=EUSCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void)
{
    switch(__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            while(!(UCA3IFG&UCTXIFG));
            UCA3TXBUF = UCA3RXBUF;
            __no_operation();
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
        default: break;
    }
}


