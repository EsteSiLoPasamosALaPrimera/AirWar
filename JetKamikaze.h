//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_JETKAMIKAZE_H
#define AIRWAR_JETKAMIKAZE_H

#include "Elemento.h"

class JetKamikaze: public Elemento{
public:
    JetKamikaze();
    JetKamikaze(int resist,int pPosX,float pPosY);
    void moverse(int refX,int refY);
};

JetKamikaze::JetKamikaze() {
    resistencia=150;
    posX=rand()%1060+15;
    velocidad=6;
    id="JK";
    puntaje=20;
}

JetKamikaze::JetKamikaze(int resist, int pPosX, float pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    id="JK";
    velocidad=6;
    puntaje=20;
}

void JetKamikaze::moverse(int refX, int refY) {
    if(posX>refX){
        posX-=velocidad;
    }else{
        posX+=velocidad;
    }
    posY+=velocidad;
}

#endif //AIRWAR_JETKAMIKAZE_H
