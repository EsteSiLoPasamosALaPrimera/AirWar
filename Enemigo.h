//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_ENEMIGO_H
#define AIRWAR_ENEMIGO_H
#include<iostream>
#include <allegro5/bitmap.h>
#include "fstream"

using namespace std;

class Enemigo{
public:
    int posX;
    int posY;
    int velocidad;
    int ataque;
    int resistencia;

    void descargar(bool iteracion);
    void moverse();
    string info();

    Enemigo();
    ~Enemigo();
    ALLEGRO_BITMAP* imagen=NULL;

protected:
    string id="EN";
    string fillString(string txt,int max);

};

Enemigo::Enemigo() {
    posX=posY=0;
    ataque=0;
    velocidad=0;
    resistencia=0;
    imagen=NULL;
}

string Enemigo::fillString(string txt,int max) {
    while(txt.size()<max){
        txt="0"+txt;
    }
    return txt;
}

void Enemigo::descargar(bool iteracion) {

    string infor=id+";"+fillString(to_string(resistencia),4)+";"+fillString(to_string(posX),4)+";"+fillString(to_string(posY),4)+";\n";
    if(iteracion==true){
        ofstream archivo("/home/alfredo/Inicio/Documentos/torres.txt");
        archivo<<infor;
        archivo.close();
    }else{
        ofstream archivo("/home/alfredo/Inicio/Documentos/torres.txt",ios::app);
        archivo<<infor;
        archivo.close();
    }
}

Enemigo::~Enemigo() {
    //al_destroy_bitmap(imagen);
}

void Enemigo::moverse() {
    posY+=velocidad;
}

string Enemigo::info() {
    string infor=id+";"+fillString(to_string(resistencia),4)+";"+fillString(to_string(posX),4)+";"+fillString(to_string(posY),4)+";\n";
    return infor;
}
#endif //AIRWAR_ENEMIGO_H
