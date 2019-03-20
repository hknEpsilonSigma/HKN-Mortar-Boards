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
    //initialize uart
    uartInit();

    //initialize ZigBee
    return xBee3_init();
}
