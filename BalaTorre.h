//
// Created by alfredo on 01/04/17.
//

#include <allegro5/allegro.h>
#include "Elemento.h"

#ifndef AIRWAR_BALATORRE_H
#define AIRWAR_BALATORRE_H

class BalaTorre: public Elemento{
public:
    BalaTorre(int resist,int pPosX,int pPosY);
};

BalaTorre::BalaTorre(int resist, int pPosX, int pPosY) {
    ataque=50;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bala2.png");
    velocidad=4;
    id="BT";
}


#endif //AIRWAR_BALATORRE_H
