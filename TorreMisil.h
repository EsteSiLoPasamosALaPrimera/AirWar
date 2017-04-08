//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORREMISIL_H
#define AIRWAR_TORREMISIL_H

#include "Elemento.h"

/**
 * @class TorreMisil
 * @brief Clase derivada que representa las torres con misil
 * @see Elemento
 */


class TorreMisil: public Elemento{
public:
    TorreMisil();
    TorreMisil(int pResistencia,int pPosX,float pPosY);

};


/**
 * @brief Constructor de la clase Torre Misil
 */
TorreMisil::TorreMisil() {
    resistencia=300;
    posX=(rand()%12)*100;
    id="TM";
    velocidad=10*(1.0/60);
    puntaje=10;
}

/**
 * @brief Constructor de la clase TorreMisil
 * Inicializa los atributos necesarios para representar las torres misil graficamente con su movimiento caracteristico.
 * @param resist valor de la resistencia que tendra la torre misil.
 * @param pPosX valor de la posicion en el eje X donde se dibujara la torre misil.
 * @param pPosY valor de la posicion en el eje Y donde se dibujara la torre misil.
 * @see Elemento
 */
TorreMisil::TorreMisil(int pResistencia, int pPosX, float pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    id="TM";
    velocidad=10*(1.0/60);
    puntaje=10;
}
#endif //AIRWAR_TORREMISIL_H
