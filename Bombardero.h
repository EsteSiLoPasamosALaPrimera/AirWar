//
// Created by alfredo on 01/04/17.
//

#include "Elemento.h"

#ifndef AIRWAR_BOMBARDERO_H
#define AIRWAR_BOMBARDERO_H


/**
 * @class Bombardero
 * @brief Clase derivada que representa el avion bombardero.
 * @see Elemento
 */

class Bombardero:public Elemento{

public:
    Bombardero();
    Bombardero(int resist,int pPosX,float pPosY);
};

/**
 * @brief Constructor de la clase Bombardero
 * Inicializa los atributos necesarios para representar el avion bombardero graficamente con su movimiento caracteristico.
 * @see Elemento
 */
Bombardero::Bombardero() {
    resistencia=300;
    posX=rand()%1060+15;
    velocidad=3;
    id="BD";
    puntaje=10;
}

/**
 * @brief Constructor de la clase Bombardero
 * Actualiza los atributos necesarios para representar el avion bombardero graficamente con su movimiento caracteristico.
 * @param resist valor de la resistencia que tendra el bombarder.
 * @param pPosX valor de la posicion en el eje X donde se dibujara el bombardero.
 * @param pPosY valor de la posicion en el eje Y donde se dibujara el bombardero.
 * @see Elemento
 */
Bombardero::Bombardero(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posY=pPosY;
    posX=pPosX;
    velocidad=3;
    id="BD";
    puntaje=10;
}

#endif //AIRWAR_BOMBARDERO_H
