//
// Created by alfredo on 08/04/17.
//

#ifndef AIRWAR_ESCOLTA_H
#define AIRWAR_ESCOLTA_H

#include "Elemento.h"


/**
 * @class Escolta
 * @brief clase que representa a el avion escolta.
 */
class Escolta: public Elemento{
public:
    Escolta();
    Escolta(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};

/**
 * @brief Constructor de la clase Escolta
 */
Escolta::Escolta() {
    resistencia=150;
    velocidad=3;
    id="SC";
    puntaje=5;
    posX=rand()%4+599;
}

/**
 * @brief Constructor de la clase Escolta
 * @param resist valor de la resistencia
 * @param pPosX valor de la posicion en el eje X
 * @param pPosY valor de la posicion en el eje Y
 */
Escolta::Escolta(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    puntaje=5;
    id="SC";
    velocidad=3;
}

/**
 * @brief Metodo que contiene la logica del movimiento de los escoltas.
 * @param refX posicion de referencia en el eje X, generalmente corresponde a las posicion en X del jugador.
 * @param refY posicion de referencia en el eje Y, generalmente corresponde a las posicion en Y del jugador.
 */
void Escolta::moverse(int refX, int refY) {
    if(posX<=600){
        if(posX>0 && posY<=300){
            posX-=velocidad;
        }else{
            posX+=velocidad;
        }
    }else{
        if(posX<=1100 && posY<=300){
            posX+=velocidad;
        }else{
            posX-=velocidad;
        }
    }
    posY+=2;

}

#endif //AIRWAR_ESCOLTA_H
