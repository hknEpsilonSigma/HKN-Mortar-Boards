
#include <msp430.h>
#include <driverlib.h>
#include <HKNHats.h>



int main(void)
{

    boardInit();

    char *command = "Hello World!";
        uart_xBee3_transmit(command);

    while(1);

}




