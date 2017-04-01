//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_JUGADOR_H
#define AIRWAR_JUGADOR_H

#include <allegro5/allegro.h>
#include "Elemento.h"
#include "Bala.h"
#include "math.h"
#include "Lista_Paginada.h"

class Jugador: public Elemento{
public:
    int vidas;
    int pantX;
    int pantY;
    Lista_Paginada balas;

    Jugador();
    void desplazar(int dir);
    void agregarBala();
    void agregarBala(int masX,int masY);
    void mover_Balas();
    void eliminar_Balas();
    void detectarColisionBalas(Lista_Paginada listA);
    void detectarColisionJugador(Lista_Paginada listA,int centro);
    void detectarColisionBalasEnemigas(Lista_Paginada listA,int radio);



};

Jugador::Jugador() {
    resistencia=200;
    posX=300;
    posY=300;
    vidas=3;
    velocidad=6;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/nave3.png");
    ataque=50;
    pantX=1300;
    pantY=690;
    balas=Lista_Paginada("/home/alfredo/Inicio/Documentos/balas.txt",5);
}

void Jugador::desplazar(int dir) {
    switch (dir){
        case 1:
            if(posY>=velocidad){
                posY-=velocidad;
            }
            break;
        case 2:
            if(posY<=pantY-100){
                posY+=velocidad;
            }
            break;
        case 3:
            if(posX<=pantX-100){
                posX+=velocidad;
            }
            break;
        case 4:
            if(posX>=velocidad){
                posX-=velocidad;
            }
            break;
    }
}

void Jugador::agregarBala() {
    balas.insertar(0,Bala(0,posX+50,posY));
}

void Jugador::agregarBala(int masX, int masY) {
    balas.insertar(0,Bala(0,posX+masX,posY+masY));
}

void Jugador::mover_Balas() {
    if(balas.tam>0){
        balas.moverse();
    }
}

void Jugador::eliminar_Balas() {
    for(int i=0;i<balas.tam;i++){
        if(balas.recorrer(i).posY<=0 || balas.recorrer(i).posY>=690){
            balas.remover(i);
        }
    }
}

void Jugador::detectarColisionBalas(Lista_Paginada listA) {
    for(int i=0;i<listA.tam;i++){
        Elemento tEnem=listA.recorrer(i);
        int limX=tEnem.posX+50;
        int limY=tEnem.posY+50;
        for(int j=0;j<balas.tam;j++){
            tEnem=balas.recorrer(j);
            if(limY-50<=tEnem.posY && tEnem.posY<=limY+50){
                if(limX-50<=tEnem.posX && tEnem.posX<=limX+50){
                    if(listA.bajarResistencia(i,ataque)){
                        balas.setPosY(j,-3);
                        listA.setPosY(i,1000);
                    }else{
                        balas.setPosY(j,-3);
                    }
                }
            }
        }
    }

}

void Jugador::detectarColisionJugador(Lista_Paginada listA,int centro) {
    int limJugX=posX+50;
    int limJugY=posY+50;
    for(int i=0;i<listA.tam;i++){
        Elemento eh=listA.recorrer(i);
        int limX=eh.posX+centro;
        int limY=eh.posY+centro;
        int dist=pow(limJugX-limX,2)+pow(limJugY-limY,2);
        dist=pow(dist,0.5);
        if(dist<(50*pow(2,0.5))){//100 por raiz de dos
            vidas--;
            listA.setPosY(i,1000);
            posX=650;
            posY=590;
        }
    }
}


void Jugador::detectarColisionBalasEnemigas(Lista_Paginada listA,int radio) {
    int limJugX=posX+50;
    int limJugY=posY+50;
    for(int i=0;i<listA.tam;i++){
        Elemento eh=listA.recorrer(i);
        int limX=eh.posX+radio;
        int limY=eh.posY+radio;
        int dist=pow(limJugX-limX,2)+pow(limJugY-limY,2);
        dist=pow(dist,0.5);
        if(dist<(50*pow(2,0.5))){//100 por raiz de dos
            resistencia-=eh.ataque;
            if(resistencia<=0){
                vidas--;
                resistencia=200;
                posX=650;
                posY=590;
            }
            listA.setPosY(i,1000);
        }
    }
}
#endif //AIRWAR_JUGADOR_H
