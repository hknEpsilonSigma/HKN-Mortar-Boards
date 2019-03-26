/*
 * XBee.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Catalyst
 */

#ifndef XBEE_H_
#define XBEE_H_

#include "HKNHats.h"

/***********************************************************Level 1 Functions ******************************************************/

/*
 * transmit a message from uC to xBee through uart
 */
void uart_xBee_transmit(char *message);

/*
 * Receive an "OK" string from UART
 */
int xBee3_uart_receive_OK(void);

/***********************************************************Level 2 Functions ******************************************************/

/*
 * Enter command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_enter_command_mode();

/*
 * Exit command mode, return 1 if success and 0 otherwise
 */
int uart_xBee3_exit_command_mode();

/*
 * Send command only, return 1 if success and 0 otherwise
 */
int uart_xBee3_send_command_only(char *pointer);

/***********************************************************Level 3 Functions ******************************************************/
/*
 * initialize xBee settings locally through uart
 */
int xBee_init(void);

/*
 * Send a single whole command with auto-enter and exit
 */
int uart_xBee3_send_command(char *pointer);

/*
 * transmit a message through radio waves to other Xbees
 */
void xBee_radio_transmit(char *message);

/*
 * get RSSI (not written)
 */
uint16_t xBee_get_RSSI();

//other necessary functions:
//get RSSI to compute distance
//Set destination address
//and then write code for LEDs, which will involve:
    //CPLD to make 32 (or so) bit shift register
    //an array that will hold which color each LED will have (GREEN, RED, etc)
    //then a function that converts that color into a pwm duty cycle, using 3 rows (RGB) and 32 columns for each LED
        //(say 10ms period) will just put a 5 there if 50% cycle, 7 if 70% cycle
            //if msCount < that value, output a 1 that will later go through the shift register, 0 otherwise. And then clk when youre done
            //and reset msCount


#endif /* XBEE_H_ */
