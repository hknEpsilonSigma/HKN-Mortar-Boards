/*
 * Board_Init.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#ifndef BOARD_INIT_H_
#define BOARD_INIT_H_

#include "HKNHats.h"

/*
 * Only function that will be called by main,
 * which holds all board initializations, including uart, Zigbee, ...
 */
int boardInit(void);

#endif /* BOARD_INIT_H_ */
