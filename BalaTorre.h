//
// Created by alfredo on 01/04/17.
//

#include "Elemento.h"

#ifndef AIRWAR_BALATORRE_H
#define AIRWAR_BALATORRE_H

/**
 * @class BalaTorre
 * @brief Clase derivada que representa los disparos de las torres.
 * @see Elemento
 */

class BalaTorre: public Elemento{
public:
    BalaTorre(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};


/**
 * @brief Constructor de la clase BalaTorre
 * Inicializa los atributos necesarios para representar los disparos graficamente con su movimiento caracteristico.
 * @param resist valor de la resistencia que tendra el disparo.
 * @param pPosX valor de la posicion en el eje X donde se dibujara el disparo.
 * @param pPosY valor de la posicion en el eje Y donde se dibujara el disparo.
 * @see Elemento
 */
BalaTorre::BalaTorre(int resist, int pPosX, float pPosY) {
    ataque=50;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=4;
    id="BT";
}

/**
 * @brief Metodo que contiene la logica de movimiento del disparo de la torre.
 * @refX Posicion en el eje X de referencia para ejecutar el rastreo, representa la posicion en X del jugador.
 * @refY Posicion en el eje Y de referencia para ejecutar el rastreo, representa la posicion en Y del jugador.
 * @see Elemento
 */
void BalaTorre::moverse(int refX,int refY) {
    if(posX>600){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;
}

#endif //AIRWAR_BALATORRE_H
