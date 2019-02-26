#include <msp430.h>
#include <eusci_a_uart.h>


/**
 * main.c
 */

#define Aclk = 32768;//Need to double check this value
#define Baudrate = 9600;

uint16_t UartPrescale = 3; //(Aclk/Baudrate);

struct EUSCI_A_UART_initParam RFUartSettings = {

    //Set ACLK clocksource
    EUSCI_A_UART_CLOCKSOURCE_ACLK,
    //Prescale value Aclk/Baudrate
    3,
    //BRF value <- Not sure about this
    0x09,
    //BRS value <- Not sure about this
    0x08,
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


struct EUSCI_A_UART_initParam *RFUart = &RFUartSettings;


int main(void)
{
	
    EUSCI_A_UART_init( UCA3CTLW0, RFUart);


}

void initUART(void){




}




//Began writing without driverlib, decided to switch over
/*
void initUART(void){

    //Enter Reset mode
    UCA3CTLW1 = UCSWRST__ENABLE;

    //UART Config: UART; ASYNCHRONOUS; No Parity; LSB first; 8-Bit word; One Stop Bit;
    UCA3CTLW0 = UCMODE_0 | UCSYNC__ASYNC | UCPEN_0 | UCMSB_0 | UC7BIT__8BIT | UCSPB_0;

    //Baudrate control:
    CLKSpeed = ;
    TGTBaud = 9600;
    UCA3ABCTL = (CLKSpeed/TGTBaud);

}*/
