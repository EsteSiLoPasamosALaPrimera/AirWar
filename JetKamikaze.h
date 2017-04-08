//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_JETKAMIKAZE_H
#define AIRWAR_JETKAMIKAZE_H

#include "Elemento.h"

/**
 * @class JetKamikaze
 * @brief Clase que representa el jet kamikaze.
 * @see JetKamikaze
 */
class JetKamikaze: public Elemento{
public:
    JetKamikaze();
    JetKamikaze(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};

/**
 * @brief Constructor de la clase JetKamikaze
 */
JetKamikaze::JetKamikaze() {
    resistencia=150;
    posX=rand()%1060+15;
    velocidad=6;
    id="JK";
    puntaje=20;
}

/**
 * @brief Constructor de la clase JetKamikaze
 * @param resist valor de la resistencia del jet kamikaze
 * @param pPosX posicion en el eje X del jet kamikaze.
 * @param pPosY posicion en el eje Y del jet kamikaze.
 * @see Elemento
 */
JetKamikaze::JetKamikaze(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    id="JK";
    velocidad=6;
    puntaje=20;
}

/**
 * @brief Metodo que contiene la logica de movimiento del JetKamikaze.
 * @refX Posicion en el eje X de referencia para ejecutar el rastreo de ser necesario, representa la posicion en X del jugador.
 * @refY Posicion en el eje Y de referencia para ejecutar el rastreo de ser necesario, representa la posicion en Y del jugador.
 * @see Elemento
 */
void JetKamikaze::moverse(int refX, int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;
}

#endif //AIRWAR_JETKAMIKAZE_H
