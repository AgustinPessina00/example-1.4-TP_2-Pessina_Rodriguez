#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

#define GAS_DETECTOR         0
#define OVER_TEMP_DETECTOR   1
#define A_BUTTON             2
#define B_BUTTON             3
#define C_BUTTON             4
#define D_BUTTON             5

int main()
{
    BusIn busPines(D2, D3, D4, D5, D6, D7);

    BusOut alarmLed(LED1);
    
    busPines.mode(PullDown);

    alarmLed.write(OFF);

    bool alarmState = OFF;

    while (true) {

        if ( busPines[GAS_DETECTOR] || busPines[OVER_TEMP_DETECTOR] ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        if ( busPines[A_BUTTON] && busPines[B_BUTTON] && !busPines[C_BUTTON] && !busPines[D_BUTTON] ) {
            alarmState = OFF;
        }
    }
}