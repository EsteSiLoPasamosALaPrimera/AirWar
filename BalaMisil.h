//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_BALAMISIL_H
#define AIRWAR_BALAMISIL_H

#include <allegro5/allegro.h>
#include "Elemento.h"

class BalaMisil: public Elemento{
public:
    BalaMisil(int resist,int pPosX,int pPosY);
};

BalaMisil::BalaMisil(int resist, int pPosX, int pPosY) {
    ataque=100;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bala2.png");
    velocidad=4;
    id="BM";
}


#endif //AIRWAR_BALAMISIL_H
