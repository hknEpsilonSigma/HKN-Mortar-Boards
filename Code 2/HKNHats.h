/*
 * HKNHats.h
 *
 *  Include this file in all .c files to eliminate additional headers
 */

#ifndef HKNHATS_H_
#define HKNHATS_H_

#include <msp430.h>
#include <driverlib.h>
#include <eusci_a_uart.h>
#include "uart.h"
#include "Board_Init.h"
#include "xbee3.h"

#define buffer_size 16

char receive_buffer[buffer_size];
uint32_t buffer_position;

#endif /* HKNHATS_H_ */
