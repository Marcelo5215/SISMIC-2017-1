#include <msp430.h> 
#include "estados.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    init();
    estadoAtual = hold_s;

    for(;;){
        (*estadoAtual)();
    }
	
	return 0;
}
