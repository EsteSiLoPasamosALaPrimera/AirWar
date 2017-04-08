//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_BALAMISIL_H
#define AIRWAR_BALAMISIL_H

#include "Elemento.h"

/**
 * @class BalaMisil
 * @brief Clase derivada que representa misiles que persiguen a el jugador.
 * @see Elemento
 */

class BalaMisil: public Elemento{
public:
    BalaMisil(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};


/**
 * @brief Constructor de la clase BalaMisil
 * Inicializa los atributos necesarios para representar los misiles graficamente con su movimiento caracteristico.
 * @param resist valor de la resistencia que tendra el misil.
 * @param pPosX valor de la posicion en el eje X donde se dibujara el misil.
 * @param pPosY valor de la posicion en el eje Y donde se dibujara el misil.
 * @see Elemento
 */
BalaMisil::BalaMisil(int resist, int pPosX, float pPosY) {
    ataque=100;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=4;
    id="BM";
}

/**
 * @brief Metodo que contiene la logica de movimiento del misil perseguidor.
 * @refX Posicion en el eje X de referencia para ejecutar el rastreo, representa la posicion en X del jugador.
 * @refY Posicion en el eje Y de referencia para ejecutar el rastreo, representa la posicion en Y del jugador.
 * @see Elemento
 */
void BalaMisil::moverse(int refX, int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;

}
#endif //AIRWAR_BALAMISIL_H
