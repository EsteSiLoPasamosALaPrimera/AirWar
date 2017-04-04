//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_JUGADOR_H
#define AIRWAR_JUGADOR_H

#include "math.h"
#include "Lista_Paginada.h"
#include "Pila_Paginada.h"

class Jugador: public Elemento{
public:
    int vidas;
    int pantX;
    int pantY;
    int cont_puntaje;
    string modo;
    int ammo_misil,ammo_laser,num_balas;
    float invulnerable;

    Lista_Paginada balas;
    Pila_Paginada powerUps;

    Jugador();
    void desplazar(int dir);
    void agregarBala();
    void mover_Balas();
    void eliminar_Balas();
    void detectarColisionBalas(Lista_Paginada listA);
    void detectarColisionJugador(Lista_Paginada listA,int centro);
    void detectarColisionBalasEnemigas(Lista_Paginada listA,int radio);
    void agregarVida();
    void usarPowerUp();
};

Jugador::Jugador() {
    resistencia=350;
    posX=300;
    posY=300;
    vidas=3;
    velocidad=6;
    ataque=50;
    pantX=1200;
    pantY=690;
    balas=Lista_Paginada("/home/alfredo/Inicio/Documentos/balas.txt",4);
    powerUps=Pila_Paginada("/home/alfredo/Inicio/Documentos/poderes.txt");
    cont_puntaje=1;
    modo="BA";
    ammo_misil=ammo_laser=0;
    invulnerable=0.0;
    num_balas=1;
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
    if(modo=="LS" && ammo_laser>0){
        if(num_balas==1){
            balas.insertar(balas.tam-1,Laser(0,posX+50,posY));
        }else if(num_balas==2){
            balas.insertar(balas.tam-1,Laser(0,posX+25,posY));
            balas.insertar(balas.tam-1,Laser(0,posX+75,posY));
        }else{
            balas.insertar(balas.tam-1,Laser(0,posX+30,posY));
            balas.insertar(balas.tam-1,Laser(0,posX+60,posY));
            balas.insertar(balas.tam-1,Laser(0,posX+90,posY));
        }
        ammo_laser--;
    }else if(modo=="MS" && ammo_misil>0){
        if(num_balas==1){
            balas.insertar(balas.tam-1,Misil(0,posX+50,posY));
        }else if(num_balas==2){
            balas.insertar(balas.tam-1,Misil(0,posX+25,posY));
            balas.insertar(balas.tam-1,Misil(0,posX+75,posY));
        }else{
            balas.insertar(balas.tam-1,Misil(0,posX+30,posY));
            balas.insertar(balas.tam-1,Misil(0,posX+60,posY));
            balas.insertar(balas.tam-1,Misil(0,posX+90,posY));
        }
        ammo_misil--;
    }else{
        if(num_balas==1){
            balas.insertar(balas.tam-1,Bala(0,posX+50,posY));
        }else if(num_balas==2){
            balas.insertar(balas.tam-1,Bala(0,posX+25,posY));
            balas.insertar(balas.tam-1,Bala(0,posX+75,posY));
        }else{
            balas.insertar(balas.tam-1,Bala(0,posX+30,posY));
            balas.insertar(balas.tam-1,Bala(0,posX+60,posY));
            balas.insertar(balas.tam-1,Bala(0,posX+90,posY));
        }
    }

}

void Jugador::mover_Balas() {
    if(balas.tam>0){
        balas.moverse(0,0);
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
                    if(listA.bajarResistencia(i,tEnem.ataque)){
                        balas.setPosY(j,-3);
                        if(!listA.darPowerUps(i)){
                            listA.setPosY(i,1000);
                        }
                        puntaje+=listA.recorrer(i).puntaje;
                    }else{
                        balas.setPosY(j,-3);
                    }
                }
            }
        }
    }
    agregarVida();
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
        if(dist<(50*pow(2,0.5))){

            if(eh.getID()=="AD" || eh.getID()=="AL" || eh.getID()=="AM" || eh.getID()=="ES"){
                powerUps.insertar(PowerUp(eh.getID(),eh.posX,eh.posY,eh.resistencia));
                listA.setPosY(i,1000);
            }else{
                puntaje+=eh.puntaje;
                if(!listA.darPowerUps(i)){
                    listA.setPosY(i,1000);
                }
                if(invulnerable<=0){
                    vidas--;
                    posX=650;
                    posY=590;
                    resistencia=350;
                    invulnerable=0.5;
                    num_balas=1;
                }
            }
        }
    }
    agregarVida();
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
        if(dist<(50*pow(2,0.5))){
            if(invulnerable<=0){
                resistencia-=eh.ataque;
                if(resistencia<=0){
                    vidas--;
                    resistencia=350;
                    posX=650;
                    posY=590;
                    num_balas=1;
                }
            }
            listA.setPosY(i,1000);
        }
    }
}

void Jugador::agregarVida() {
    if(puntaje>=cont_puntaje*100){
        vidas++;
        cont_puntaje++;
    }
}

void Jugador::usarPowerUp() {
    if(powerUps.tam>0){
        if(powerUps.head->element.getID()=="AL"){
            ammo_laser+=powerUps.head->element.resistencia;
        }else if(powerUps.head->element.getID()=="AM"){
            ammo_misil+=powerUps.head->element.resistencia;
        }else if(powerUps.head->element.getID()=="ES"){
            invulnerable+=powerUps.head->element.resistencia;
        }else{
            num_balas++;
        }
        powerUps.remover();
    }
}
#endif //AIRWAR_JUGADOR_H
