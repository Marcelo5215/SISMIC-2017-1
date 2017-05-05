#include "estados.h"

/*
 * estados.c
 *
 *  Created on: 5 de mai de 2017
 *      Author: macel
 */

void init(void){
    //ENTRADAS CHAVES E PINO 2.5
    P1DIR &= ~(S2);            //Chave 2 -> ENTRADA
    P1REN = 0x00;
    P2DIR &= ~(S1 | LIM) ;   //Chave 1 e pino2.5 -> ENTRADA
    P2REN = 0x00;

    //SAIDAS LED1 E LED2
    P1DIR |= LED1;          //LED1 -> SAIDA
    P4DIR |= LED2;          //LED2 -> SAIDA
}

void hold_s(void){
    //desliga LED1 E LED2
    P1OUT &= ~(LED1);
    P4OUT &= ~(LED2);

    if(((P2IN & S1)==0) && ((P1IN & S2)!=0)){   //se S1 estiver precionada e S2 nao
        estadoAtual = abrindo;
    }
    else if(((P2IN & S1)!=0) && ((P1IN & S2)==0)){  //se S2 estiver precionada e S1 nao
        estadoAtual = fechando;
    }
    //TODO
    //talvez tratar caso com LIM

}

void abrindo(void){
    //liga o LED1
    P1OUT |= LED1;
    //desliga o LED2
    P4OUT &= ~(LED2);

    if((P2IN & LIM) == 0){      //se LIM for atingido
        estadoAtual = limiteInf;
    }
    else if(((P2IN & S1)!=0) && ((P1IN & S2)==0)){  //se S2 estiver precionada e S1 nao
        estadoAtual = fechando;
    }
    //TODO
}

void fechando(void){
    //desliga o LED1
    P1OUT &= ~(LED1);
    //liga o LED2
    P4OUT |= LED2;

    //TODO
}

void limiteInf(void){

}

void limiteSup(void){

}

