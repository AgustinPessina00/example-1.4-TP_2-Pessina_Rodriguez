//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

#define GAS_DETECTOR         0
#define OVER_TEMP_DETECTOR   1
#define A_BUTTON             2
#define B_BUTTON             3
#define C_BUTTON             4
#define D_BUTTON             5

/**
* Llama a las funciones que inicializan las entradas y salidas del sistema
* Lee las entradas (detector de gas, temperatura) que activan la alarma
* (encendiendo el LED1), y una combinación de los botones A,B,C y D que la desactivan
* (apagando el LED)
* @param none
* @return El valor 0 retornado representa que la ejecución fue exitosa.
*/
int main()
{
    BusIn busPines(D2, D3, D4, D5, D6, D7); /**< Objeto asociado a las entradas de sensores y botones,
                                                 cada uno representa un bit */

    BusOut alarmLed(LED1);  /**< Objeto asociado a la salida de la alarma, representada por el primer bit del bus*/
    
    busPines.mode(PullDown);/**< Configuración como pulldown de las entradas */

    alarmLed.write(OFF); /**< Inicialización de la alarma apagada */

    bool alarmState = OFF;

/**< Ejecución del loop infinito. */
    while (true) {

        if ( busPines[GAS_DETECTOR] || busPines[OVER_TEMP_DETECTOR] ) {
            alarmState = ON;
            printf("%s%s\n", "El sensor de gas está ", busPines[GAS_DETECTOR] ? "ACTIVADO" : "DESACTIVADO");
            printf("%s%s\n", "El sensor de sobretemperatura está ", busPines[OVER_TEMP_DETECTOR] ? "ACTIVADO" : "DESACTIVADO");
            printf("%s\n" , "El estado de la alarma es ACTIVADO.");
        }

        alarmLed = alarmState;

        if ( busPines[A_BUTTON] && busPines[B_BUTTON] && !busPines[C_BUTTON] && !busPines[D_BUTTON] ) {
            for(int i = A_BUTTON; i <= D_BUTTON; i++) {
                printf("%s%c%s\n", "El botón ", 'A' + i - A_BUTTON, busPines[i] ? " está PULSADO" : " NO está PULSADO");
            }
            
            alarmState = OFF;
            printf("%s\n" , "El estado de la alarma es DESACTIVADO");
        }
    }

    return 0;
}