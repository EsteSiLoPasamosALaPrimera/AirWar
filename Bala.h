//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_BALA_H
#define AIRWAR_BALA_H

#include "Elemento.h"

class Bala:public Elemento{
public:
    Bala(int resis,int pPosX,float pPosY);
};

Bala::Bala(int resist,int pPosX,float pPosY) {
    ataque=50;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=-4;
    id="BA";
}

#endif //AIRWAR_BALA_H
