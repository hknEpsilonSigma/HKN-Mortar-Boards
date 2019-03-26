/*
 * Node.c
 *
 *  Created on: Mar 26, 2019
 *      Author: Catalyst
 */

#include "Node.h"
#include <math.h>

/*
 * Get Distance from RSSI
 */
float getDistance(uint16_t RSSI) {
    return pow(10, abs(A - RSSI) / 10*n);
}

/*
 * call this to set node.x after setting d0n, d1n, d2n
 */
int16_t getX(node_t node) {
    return (pow(node.d01, 2) + pow(node.d0n, 2) - pow(node.d1n, 2)) / (-2 * pow(node.d01, 2));
}

/*
 * call this to set node.y after setting the 3 above and node2_x and node2_y
 */
int16_t getY(node_t node) {
    float preY = pow(pow(node.d0n, 2) - pow(node.x, 2), 0.5);

    uint8_t sign;
    float y2_yn = (pow(node2_x - node.x, 2) + pow(node2_y, 2) + pow(preY, 2) - pow(node.d2n, 2)) / 2;
    if (y2yn >= 0)
        sign = 1;
    else
        sign = -1;

    return preY * sign;
}


