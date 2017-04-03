//
// Created by alfredo on 01/04/17.
//

#include "Elemento.h"

#ifndef AIRWAR_BOMBARDERO_H
#define AIRWAR_BOMBARDERO_H

class Bombardero:public Elemento{

public:
    Bombardero();
    Bombardero(int resist,int pPosX,float pPosY);
};

Bombardero::Bombardero() {
    resistencia=300;
    posX=rand()%1060+15;
    velocidad=3;
    id="BD";
    puntaje=10;
}

Bombardero::Bombardero(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posY=pPosY;
    posX=pPosX;
    velocidad=3;
    id="BD";
    puntaje=10;
}

#endif //AIRWAR_BOMBARDERO_H
