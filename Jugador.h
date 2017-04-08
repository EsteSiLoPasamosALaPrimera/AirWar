//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_JUGADOR_H
#define AIRWAR_JUGADOR_H

#include "math.h"
#include "Lista_Paginada.h"
#include "Pila_Paginada.h"
#include "Jefe.h"



/**
 * @class Jugador
 * @brief Clase que representa al jugador
 * @see Jugador
 */
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
    void detectarColisionJefe(Elemento jefe);
    Jefe detectarColisionBalasJefe(Jefe jefe);
    void agregarVida();
    void usarPowerUp();
};


/**
 * @brief Constructor de la clase Jugador
 */
Jugador::Jugador() {
    resistencia=700;
    posX=300;
    posY=300;
    vidas=3;
    velocidad=6;
    ataque=50;
    pantX=1200;
    pantY=690;
    balas=Lista_Paginada("/home/alfredo/Inicio/Documentos/balas.txt",5);
    powerUps=Pila_Paginada("/home/alfredo/Inicio/Documentos/poderes.txt");
    cont_puntaje=1;
    modo="BA";
    ammo_misil=ammo_laser=0;
    invulnerable=0.0;
    num_balas=1;
}

/**
 * @brief Metodo encargado de actualizar la posicion en los ejes X y Y del jugador.
 * @param dir numero que representa la direccion a la cual se mueve el avion.
 */
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


/**
 * @brief Metodo encargado de agregar objetos de tipo Bala a la Lista_Paginada del jugador
 * Esto con el fin de representar los disparos que realiza el jugador.
 * @see Lista_Paginada
 * @see Bala
 */
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

/**
 * @brief Metodo encargado de actualizar las posiciones sobre los ejes X y Y de las balas disparadas por el jugador.
 * @see Lista_Paginada
 */
void Jugador::mover_Balas() {
    if(balas.tam>0){
        balas.moverse(0,0);
    }
}

/**
 * @brief Metodo encargador de eliminar los objetos de tipo Bala, cuyas posiciones
 * en el eje Y sobrepasan los de la pantalla del juego.
 */
void Jugador::eliminar_Balas() {
    for(int i=0;i<balas.tam;i++){
        if(balas.recorrer(i).posY<=0 || balas.recorrer(i).posY>=690){
            balas.remover(i);
        }
    }
}

/**
 * @brief Metodo encargado de detectar colisiones entre la Lista_Paginada de balas del jugador
 * y otra Lista_Paginada con objetos de tipo Elemento.
 * @see Lista_Paginada
 * @see Elemento
 */
void Jugador::detectarColisionBalas(Lista_Paginada listA) {
    for(int i=0;i<listA.tam;i++){
        Elemento tEnem=listA.recorrer(i);
        if(tEnem.getID()!="ES" && tEnem.getID()!="AL" && tEnem.getID()!="AM" && tEnem.getID()!="AD"){
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
}


/**
 * @brief Metodo encargado de detectar colisiones entre el jugador y un objeto de tipo Elemento.
 * @param jefe objeto de tipo Elemento con el cual se realiza el calculo de colision
 * @see Elemento
 */
void Jugador::detectarColisionJefe(Elemento jefe) {
    int dist=pow((posX+50)-(jefe.posX+200),2)+pow((posY+50)-(jefe.posY+200),2);
    dist=pow(dist,0.5);
    if(dist<210){
        if(invulnerable<=0){
            vidas--;
            posX=650;
            posY=590;
            resistencia=700;
            invulnerable=0.5;
            num_balas=1;
        }
    }

}

/**
 * @brief Metodo encargado de detectar colisiones entre el objeto Jugador
 * y otra Lista_Paginada con objetos de tipo Elemento.
 * @see Lista_Paginada
 * @see Elemento
 */
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
                    resistencia=700;
                    invulnerable=0.5;
                    num_balas=1;
                }
            }
        }
    }
    agregarVida();
}

/**
 * @brief Metodo encargado de detectar colisiones entre la Lista_Paginada de balas del jugador y el jefe
 * @param jefe un objeto de tipo Jefe sobre el cual se realizan las operaciones.
 * @return un objeto de tipo Jefe
 * @see Jefe
 * @see Lista_Paginada
 */
Jefe Jugador::detectarColisionBalasJefe(Jefe jefe) {
    for(int i=0;i<balas.tam;i++){
        Elemento bTemp=balas.recorrer(i);
        int dist=pow((bTemp.posX+10)-(jefe.posX+200),2)+pow((bTemp.posY+10)-(jefe.posY+200),2);
        dist=pow(dist,0.5);
        if(dist<100){
            jefe.resistencia-=bTemp.ataque;
            balas.setPosY(i,-3);
        }
    }


    return jefe;
}



/**
 * @brief Metodo encargado de detectar colisiones entre la Lista_Paginada de balas del jugador
 * y otro Lista_Paginada con objetos de tipo BalaTorre o BalaMisil.
 * @see Lista_Paginada
 * @see BalaTorre
 * @see BalaMisil
 */
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
                    resistencia=700;
                    posX=650;
                    posY=590;
                    num_balas=1;
                }
            }
            listA.setPosY(i,1000);
        }
    }
}

/**
 * @brief Metodo encargado de sumar vidas al jugador al haber alcanzado cierto puntaje
 * @see Elemento
 */
void Jugador::agregarVida() {
    if(puntaje>=cont_puntaje*100){
        vidas++;
        cont_puntaje++;
    }
}

/**
 * @brief Metodo encargado de agregar los efectos de los power-ups al jugador
 * @see Elemento
 */
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
