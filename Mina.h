//
// Created by alfredo on 08/04/17.
//

#ifndef AIRWAR_MINA_H
#define AIRWAR_MINA_H

#include "Elemento.h"

/**
 * @class Mina
 * @brief Clase que representa a las minas
 */

class Mina: public Elemento{
public:
    Mina();
    Mina(int pResistencia,int pPosX,float pPosY);
};

/**
 * @brief Constructor de la clase Mina
 */
Mina::Mina() {
    resistencia=500;
    id="MN";
    velocidad=10*(1.0/60);
    puntaje=20;
    posX=100*(rand()%12);
}

/**
 * @brief Constructor de la clase Mina
 * @param pResistencia valor de la resistencia
 * @param pPosX valor de la posicion en el eje X
 * @param pPosY valor de la posicion en el eje Y
 */
Mina::Mina(int pResistencia, int pPosX, float pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    puntaje=20;
    velocidad=10*(1.0/60.0);
    id="MN";
}

#endif //AIRWAR_MINA_H
