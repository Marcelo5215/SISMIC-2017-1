/*
 * estados.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: macel
 */

#ifndef ESTADOS_H_
#define ESTADOS_H_

    #include "defines.h"
    #include <msp430.h>

    void (*estadoAtual)();

    //Inicializa pinos de entrada e saida para o programa
    void init(void);

    //Estados ......

    //Estado onde o vidro esta parado, e nao esta no limite
    void hold_s(void);

    //Vidro descendo, enquanto chave1 apertada e nao no limite
    void abrindo(void);

    //Vidro subindo, enquanto chave2 apertada e nao no limite
    void fechando(void);

    //Vidro no limite inferior
    void limiteInf(void);

    //Vidro no limite superior
    void limiteSup(void);



#endif /* ESTADOS_H_ */
