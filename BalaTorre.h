//
// Created by alfredo on 01/04/17.
//

#include "Elemento.h"

#ifndef AIRWAR_BALATORRE_H
#define AIRWAR_BALATORRE_H

class BalaTorre: public Elemento{
public:
    BalaTorre(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};

BalaTorre::BalaTorre(int resist, int pPosX, float pPosY) {
    ataque=50;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=4;
    id="BT";
}

void BalaTorre::moverse(int refX,int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;
}

#endif //AIRWAR_BALATORRE_H
