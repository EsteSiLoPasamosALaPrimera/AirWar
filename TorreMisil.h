//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORREMISIL_H
#define AIRWAR_TORREMISIL_H

#include "Torre.h"

class TorreMisil: public Torre{
public:
    TorreMisil();
    TorreMisil(int pResistencia,int pPosX,int pPosY);

};

TorreMisil::TorreMisil() {
    ataque=3000;
    resistencia=3000;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA1.png");
    id="TM";
    velocidad=6;
}

TorreMisil::TorreMisil(int pResistencia, int pPosX, int pPosY) {
    ataque=3000;
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA1.png");
    id="TM";
    velocidad=6;


}
#endif //AIRWAR_TORREMISIL_H
