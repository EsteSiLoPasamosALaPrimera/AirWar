//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_BALAMISIL_H
#define AIRWAR_BALAMISIL_H

#include "Elemento.h"

class BalaMisil: public Elemento{
public:
    BalaMisil(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};

BalaMisil::BalaMisil(int resist, int pPosX, float pPosY) {
    ataque=100;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=4;
    id="BM";
}

void BalaMisil::moverse(int refX, int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;

}

#endif //AIRWAR_BALAMISIL_H
