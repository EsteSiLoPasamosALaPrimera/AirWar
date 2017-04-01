//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_ENEMIGO_H
#define AIRWAR_ENEMIGO_H
#include<iostream>
#include <allegro5/bitmap.h>
#include "fstream"

using namespace std;

class Elemento{
public:
    int posX;
    int posY;
    int velocidad;
    int ataque;
    int resistencia;

    void descargar(bool iteracion,string nomArchivo);
    virtual void moverse();
    void diagonalIzq();
    void diagonalDer();
    string info();
    string getID();

    Elemento();
    ~Elemento();
    ALLEGRO_BITMAP* imagen=NULL;

protected:
    string id="EN";
    string fillString(string txt,int max);

};

Elemento::Elemento() {
    posX=posY=0;
    ataque=0;
    velocidad=0;
    resistencia=0;
    imagen=NULL;
}

string Elemento::fillString(string txt,int max) {
    while(txt.size()<max){
        txt="0"+txt;
    }
    return txt;
}

void Elemento::descargar(bool iteracion,string nomArchivo) {

    string infor=id+";"+fillString(to_string(resistencia),4)+";"+fillString(to_string(posX),4)+";"+fillString(to_string(posY),4)+";\n";
    if(iteracion==true){
        ofstream archivo(nomArchivo);
        archivo<<infor;
        archivo.close();
    }else{
        ofstream archivo(nomArchivo,ios::app);
        archivo<<infor;
        archivo.close();
    }
}

Elemento::~Elemento() {
    //al_destroy_bitmap(imagen);
}

void Elemento::moverse() {

}


void Elemento::diagonalIzq() {
    posY+=velocidad;
    posX-=velocidad;
}


void Elemento::diagonalDer() {
    posY+=velocidad;
    posX+=velocidad;
}


string Elemento::info() {
    string infor=id+";"+fillString(to_string(resistencia),4)+";"+fillString(to_string(posX),4)+";"+fillString(to_string(posY),4)+";";
    return infor;
}

string Elemento::getID() {
    return id;

}
#endif //AIRWAR_ENEMIGO_H
