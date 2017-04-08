//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_BALA_H
#define AIRWAR_BALA_H

#include "Elemento.h"

/**
 * @class Bala
 * @brief Clase derivada que representa los disparos del jugador graficamente.
 * @see Elemento
 */


class Bala:public Elemento{
public:
    Bala(int resis,int pPosX,float pPosY);
};

/**
 * @brief Constructor de la clase Bala
 * Inicializa los atributos necesarios para representar los disparos graficamente con su movimiento caracteristico.
 * @param resist valor de la resistencia que tendra la bala.
 * @param pPosX valor de la posicion en el eje X donde se dibujara la bala.
 * @param pPosY valor de la posicion en el eje Y donde se dibujara la bala.
 * @see Elemento
 */

Bala::Bala(int resist,int pPosX,float pPosY) {
    ataque=50;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=-4;
    id="BA";
}

#endif //AIRWAR_BALA_H
