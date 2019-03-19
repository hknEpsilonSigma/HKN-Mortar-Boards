/*
 * uart.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#ifndef UART_H_
#define UART_H_

#include "HKNHats.h"

/*************************************************** Function Declarations ******************************************************** */

/*
 * Initialize uart for ZigBee operation
 */
void uartInit(void);

/*************************************************** Struct Definitions *********************************************************** */

/*
 * Struct for declaring uart settings
 */
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

#endif /* UART_H_ */
