//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_BALA_H
#define AIRWAR_BALA_H

#include <allegro5/allegro.h>
#include "Enemigo.h"

class Bala:public Enemigo{
public:

    bool borrar;
    Bala(int resis,int pPosX,int pPosY);
    void desplazar();
};

Bala::Bala(int resist,int pPosX,int pPosY) {
    resistencia=resist;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bala2.png");
    velocidad=4;
    borrar=false;
    id="BA";
}

void Bala::desplazar() {
    posY-=velocidad;
    if(posY<=0){
        borrar=true;
    }
}

#endif //AIRWAR_BALA_H
