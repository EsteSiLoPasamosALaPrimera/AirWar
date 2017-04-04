//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_MISIL_H
#define AIRWAR_MISIL_H

#include "Elemento.h"

class Misil: public Elemento{
public:
    Misil(int resist,int pPosX,int pPosY);
};

Misil::Misil(int resist, int pPosX, int pPosY) {
    ataque=75;
    posX=pPosX;
    posY=pPosY;
    velocidad=-4;
    id="MS";
}

#endif //AIRWAR_MISIL_H
