//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_BALA_H
#define AIRWAR_BALA_H

#include <allegro5/allegro.h>
#include "Elemento.h"

class Bala:public Elemento{
public:
    Bala(int resis,int pPosX,int pPosY);
};

Bala::Bala(int resist,int pPosX,int pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bala2.png");
    velocidad=-4;
    id="BA";
}

#endif //AIRWAR_BALA_H
