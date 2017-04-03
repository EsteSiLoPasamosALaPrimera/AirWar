//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORRE_H
#define AIRWAR_TORRE_H


#include "Elemento.h"

class Torre : public Elemento{
public:
    Torre();
    Torre(int pResistencia,int pPosX,float pPosY);
};

Torre::Torre() {
    resistencia=200;
    posX=(rand()%12)*100;
    id="TR";
    velocidad=10*(1.0/60);
    puntaje=5;
}
Torre::Torre(int pResistencia, int pPosX, float pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    velocidad=10*(1.0/60);
    id="TR";
    puntaje=5;
}


#endif //AIRWAR_TORRE_H
