//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORREMISIL_H
#define AIRWAR_TORREMISIL_H

#include "Elemento.h"

class TorreMisil: public Elemento{
public:
    TorreMisil();
    TorreMisil(int pResistencia,int pPosX,float pPosY);

};

TorreMisil::TorreMisil() {
    resistencia=300;
    posX=(rand()%12)*100;
    id="TM";
    velocidad=10*(1.0/60);
    puntaje=10;
}

TorreMisil::TorreMisil(int pResistencia, int pPosX, float pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    id="TM";
    velocidad=10*(1.0/60);
    puntaje=10;
}
#endif //AIRWAR_TORREMISIL_H
