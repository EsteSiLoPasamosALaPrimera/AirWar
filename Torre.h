//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORRE_H
#define AIRWAR_TORRE_H


#include "Elemento.h"

/**
 * @class Torre
 * @brief Clase derivada que representa las torres.
 * @see Elemento
 */
class Torre : public Elemento{
public:
    Torre();
    Torre(int pResistencia,int pPosX,float pPosY);
};

/**
 * @class Constructor de la clase Torre
 */
Torre::Torre() {
    resistencia=200;
    posX=(rand()%12)*100;
    id="TR";
    velocidad=10*(1.0/60);
    puntaje=5;
}

/**
 * @brief Constructor de la clase Torre
 * Inicializa los atributos necesarios para representar las torres graficamente con su movimiento caracteristico.
 * @param resist valor de la resistencia que tendra la torre.
 * @param pPosX valor de la posicion en el eje X donde se dibujara la torre.
 * @param pPosY valor de la posicion en el eje Y donde se dibujara la torre.
 * @see Elemento
 */
Torre::Torre(int pResistencia, int pPosX, float pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    velocidad=10*(1.0/60);
    id="TR";
    puntaje=5;
}


#endif //AIRWAR_TORRE_H
