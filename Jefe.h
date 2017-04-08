//
// Created by alfredo on 07/04/17.
//

#ifndef AIRWAR_JEFE_H
#define AIRWAR_JEFE_H

#include "Elemento.h"

/**
 * @class Jefe
 * @brief Clase derivada que representa los enemigos finales de cada nivel.
 * @see Elemento
 */
class Jefe: public Elemento{
public:
    Jefe();
    Jefe(int nivel);
    void moverse(int refX,int refY);
};

/**
 * @brief Constructor de la clase Jefe
 */
Jefe::Jefe() { }


/**
 * @brief Constructor de la clase Jefe
 * @param nivel numero que indica el nivel en el que se encuentra el jugador, tambien define la dificultad del jefe
 * @see Elemento
 */
Jefe::Jefe(int nivel) {
    resistencia=1500*nivel;
    posX=-15;
    velocidad=5;
}


/**
 * @brief Metodo que contiene la logica de movimiento del Jefe.
 * @refX Posicion en el eje X de referencia para ejecutar el rastreo de ser necesario, representa la posicion en X del jugador.
 * @refY Posicion en el eje Y de referencia para ejecutar el rastreo de ser necesario, representa la posicion en Y del jugador.
 * @see Elemento
 */
void Jefe::moverse(int refX, int refY) {
    if(posX+velocidad==900){
        velocidad=-5;
    }else if(posX+velocidad==0){
        velocidad=5;
    }
    posX+=velocidad;

}
#endif //AIRWAR_JEFE_H
