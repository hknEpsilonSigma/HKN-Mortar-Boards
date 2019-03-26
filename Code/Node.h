/*
 * Node.h
 *
 *  Created on: Mar 26, 2019
 *      Author: Catalyst
 */

#ifndef LIBRARIES_NODE_H_
#define LIBRARIES_NODE_H_

#include "HKNHats.h"

//data structure defintions
typedef struct Node {
    int16_t x;
    int16_t y;

    uint16_t d0n;
    uint16_t d1n;
    uint16_t d2n;
} node_t;

//global variables
float A; //error variable for RSSI
float n; //error variable for RSSI

uint16_t d01; //distance from node 0 to 1
int16_t node2_x; //x coord of node 2
int16_t node2_y; //y coord of node 2

/***********************************************************Functions ******************************************************/
/*
 * Get Distance from RSSI
 */
float getDistance(uint16_t RSSI);

/*
 * call this to set node.x after setting d0n, d1n, d2n
 */
int16_t getX(node_t node);

/*
 * call this to set node.y after setting the 3 above and node2_x and node2_y
 */
int16_t getY(node_t node);

#endif /* LIBRARIES_NODE_H_ */
