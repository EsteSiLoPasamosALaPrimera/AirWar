//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_JET_H
#define AIRWAR_JET_H

#include "Elemento.h"

class Jet:public Elemento{
public:
    Jet();
    Jet(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};

Jet::Jet() {
    resistencia=200;
    posX=rand()%1060+15;
    velocidad=4;
    id="JT";
    puntaje=5;
}

Jet::Jet(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=4;
    id="JT";
    puntaje=5;
}

void Jet::moverse(int refX,int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;
}

#endif //AIRWAR_JET_H
