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
    P1REN = 0xFF;              //resistor de pulldown
    P1OUT |= S2;
    P2DIR &= ~(S1 | LIM) ;     //Chave 1 e pino2.5 -> ENTRADA
    P2REN = 0xFF;              //resistor de pulldown
    P2OUT |= S1 | LIM;

    //SAIDAS LED1 E LED2
    P1DIR |= LED1;          //LED1 -> SAIDA
    P4DIR |= LED2;          //LED2 -> SAIDA

}

void hold_s(void){
    //desliga LED1 E LED2
    P1OUT &= ~(LED1);
    P4OUT &= ~(LED2);

    //S1 * ~S2
    if(((P2IN & S1)==0) && ((P1IN & S2)!=0)){   //se S1 estiver pressionada e S2 nao
        estadoAtual = open;
    }
    //~S1 * S2
    else if(((P2IN & S1)!=0) && ((P1IN & S2)==0)){  //se S2 estiver pressionada e S1 nao
        estadoAtual = close;
    }
    //Caso as entradas nao sejam essas estado continua o mesmo

}

void open(void){
    //liga o LED1
    P1OUT |= LED1;
    //desliga o LED2
    P4OUT &= ~(LED2);

    //L
    if((P2IN & LIM) == 0){      //se LIM for atingido
        estadoAtual = limTop;
    }
    //~S1 * S2
    else if(((P2IN & S1)!=0) && ((P1IN & S2)==0)){  //se S2 estiver pressionada e S1 nao
        estadoAtual = close;
    }
    //~S1 * ~S2
    else if(((P2IN & S1)!=0) && ((P1IN & S2)!=0)){  //se S2 S1 nao estiverem pressionadas
        estadoAtual = hold_s;
    }
    //Caso as entradas nao sejam essas estado continua o mesmo

}

void close(void){
    //desliga o LED1
    P1OUT &= ~(LED1);
    //liga o LED2
    P4OUT |= LED2;

    //L
    if((P2IN & LIM) == 0){      //se LIM for atingido
        estadoAtual = limTop;
    }
    //S1 * ~S2
    else if(((P2IN & S1)==0) && ((P1IN & S2)!=0)){  //se S1 estiver pressionada e S2 nao
        estadoAtual = open;
    }
    //~S1 * ~S2
    else if(((P2IN & S1)!=0) && ((P1IN & S2)!=0)){  //se S2 S1 nao estiverem pressionadas
        estadoAtual = hold_s;
    }
    //Caso as entradas nao sejam essas estado continua o mesmo
}

void limTop(void){
    //liga o LED1
    P1OUT |= LED1;
    //liga o LED2
    P4OUT |= LED1;

    //~L * ~S1 * ~S2
    if(((P2IN & LIM) != 0) && ((P2IN & S1)!=0) && ((P1IN & S2)!=0)){
        estadoAtual = hold_s;
    }
    //~L * s1 * ~S2
    else if(((P2IN & LIM) != 0) && ((P2IN & S1)==0) && ((P1IN & S2)!=0)){  //se S2 estiver pressionada e S1 nao
        estadoAtual = open;
    }
    //Caso as entradas nao sejam essas estado continua o mesmo
}

void limBot(void){
    //~L * ~S1 * ~S2
    if(((P2IN & LIM) != 0) && ((P2IN & S1)!=0) && ((P1IN & S2)!=0)){
        estadoAtual = hold_s;
    }
    //~L * s1 * ~S2
    else if(((P2IN & LIM) != 0) && ((P2IN & S1)!=0) && ((P1IN & S2)==0)){  //se S2 estiver pressionada e S1 nao
        estadoAtual = close;
    }
    //Caso as entradas nao sejam essas estado continua o mesmo
}

