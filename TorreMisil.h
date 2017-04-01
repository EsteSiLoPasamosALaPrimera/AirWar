//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORREMISIL_H
#define AIRWAR_TORREMISIL_H

#include "Elemento.h"

class TorreMisil: public Elemento{
public:
    TorreMisil();
    TorreMisil(int pResistencia,int pPosX,int pPosY);

};

TorreMisil::TorreMisil() {
    resistencia=300;
    posX=rand()%1160+15;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA1.png");
    id="TM";
    velocidad=6;
}

TorreMisil::TorreMisil(int pResistencia, int pPosX, int pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA1.png");
    id="TM";
    velocidad=6;
}
#endif //AIRWAR_TORREMISIL_H
