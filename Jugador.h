//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_JUGADOR_H
#define AIRWAR_JUGADOR_H

#include <allegro5/allegro.h>
#include "Enemigo.h"

class Jugador: public Enemigo{
public:
    int vidas;
    int pantX;
    int pantY;
    Lista_Paginada balas;

    Jugador();
    void desplazar(int dir);
    void agregarBala();

};

Jugador::Jugador() {
    posX=300;
    posY=300;
    vidas=3;
    velocidad=4.0;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/nave3.png");
    ataque=50;
    pantX=1300;
    pantY=690;
}

void Jugador::desplazar(int dir) {
    switch (dir){
        case 1:
            if(posY>=velocidad){
                posY-=velocidad;
            }
            break;
        case 2:
            if(posY<=pantY-velocidad){
                posY+=velocidad;
            }
            break;
        case 3:
            if(posX>=velocidad){
                posX+=velocidad;
            }
            break;
        case 4:
            if(posX<=pantX-velocidad){
                posX-=velocidad;
            }
            break;
    }
}

void Jugador::agregarBala() {



}



#endif //AIRWAR_JUGADOR_H
