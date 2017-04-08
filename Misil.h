//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_MISIL_H
#define AIRWAR_MISIL_H

#include "Elemento.h"

/**
 * @class Misil
 * @brief Clase que representa el tipo de municion misil
 * @see Elemento
 */
class Misil: public Elemento{
public:
    Misil(int resist,int pPosX,int pPosY);
};

/**
* @brief Constructor de la clase Misil
* @param resist valor de resistencia del misil.
* @param pPosX valor de la posicion en el eje X del misil.
* @param pPosY valor de la posicion en el eje Y del misil.
*/
Misil::Misil(int resist, int pPosX, int pPosY) {
    ataque=75;
    posX=pPosX;
    posY=pPosY;
    velocidad=-4;
    id="MS";
}

#endif //AIRWAR_MISIL_H
