//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_JET_H
#define AIRWAR_JET_H

#include "Elemento.h"

/**
 * @class Jet
 * @brief Clase que representa los jets.
 * @see Elemento
 */

class Jet:public Elemento{
public:
    Jet();
    Jet(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};


/**
 * @brief Constructor de la clase Jet
 */
Jet::Jet() {
    resistencia=200;
    posX=rand()%1060+15;
    velocidad=4;
    id="JT";
    puntaje=5;
}

/**
 * @brief Constructor de la clase Jet
 * @param resist valor de la resistencia del jet
 * @param pPosX posicion en el eje X del jet.
 * @param pPosY posicion en el eje Y del jet
 * @see Elemento
 */
Jet::Jet(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=4;
    id="JT";
    puntaje=5;
}

/**
 * @brief Metodo que contiene la logica de movimiento del Jet.
 * @refX Posicion en el eje X de referencia para ejecutar el rastreo de ser necesario, representa la posicion en X del jugador.
 * @refY Posicion en el eje Y de referencia para ejecutar el rastreo de ser necesario, representa la posicion en Y del jugador.
 * @see Elemento
 */
void Jet::moverse(int refX,int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;
}

#endif //AIRWAR_JET_H
