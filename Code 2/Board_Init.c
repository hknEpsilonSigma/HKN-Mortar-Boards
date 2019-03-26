/*
 * Board_Init.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#include "HKNHats.h"

/*
 * Only function that will be called by main,
 * which holds all board initializations, including uart, Xbee, ...
 */
int boardInit() {
    WDTCTL = WDTPW | WDTHOLD;               // Stop Watchdog

    //initialize uart

    uartInit();

    //initialize ZigBee
    return 1;//xBee3_init();
}
