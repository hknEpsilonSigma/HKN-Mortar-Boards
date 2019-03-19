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
void boardInit() {
    //initialize uart
    uartInit();

    //initialize ZigBee
    xBee_init();
}
