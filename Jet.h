//
// Created by alfredo on 01/04/17.
//

#ifndef AIRWAR_JET_H
#define AIRWAR_JET_H

#include <allegro5/allegro.h>
#include "Elemento.h"

class Jet:public Elemento{
public:
    Jet();
    Jet(int resist,int pPosX,int pPosY);
};

Jet::Jet() {
    ataque=50;
    resistencia=500;
    posX=rand()%1160+15;
    velocidad=6;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/jet.png");
    id="JT";
}

Jet::Jet(int resist, int pPosX, int pPosY) {
    ataque=50;
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    velocidad=6;
    id="JT";
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/jet.png");
}


#endif //AIRWAR_JET_H
