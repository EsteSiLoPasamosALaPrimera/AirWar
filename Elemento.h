//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_ENEMIGO_H
#define AIRWAR_ENEMIGO_H
#include<iostream>
#include "fstream"

using namespace std;

class Elemento{
public:
    int posX;
    float posY;
    float velocidad;
    int ataque;
    int resistencia;
    int puntaje;

    void descargar(bool iteracion,string nomArchivo);
    virtual void moverse(int refX,int refY){posY+=velocidad;}
    virtual string info();
    virtual string getID();
    virtual bool darPowerUp();

    Elemento();
    ~Elemento();

protected:
    string id="EN";
    string fillString(string txt,int max);

};

Elemento::Elemento() {
    posX=posY=0;
    ataque=0;
    velocidad=0;
    resistencia=0;
    puntaje=0;
}

string Elemento::fillString(string txt,int max) {
    while(txt.size()<max){
        txt="0"+txt;
    }
    if(txt.size()>max){
        txt=txt.substr(0,max);
    }
    return txt;
}

void Elemento::descargar(bool iteracion,string nomArchivo) {

    string infor=id+";"+fillString(to_string(resistencia),5)+";"+fillString(to_string(posX),5)+";"+fillString(to_string(posY),5)+";\n";
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
}

string Elemento::info() {
    string infor=id+";"+fillString(to_string(resistencia),5)+";"+fillString(to_string(posX),5)+";"+fillString(to_string(posY),5)+";";
    return infor;
}

string Elemento::getID() {
    return id;
}
bool Elemento::darPowerUp() {
    switch(rand()%2){
        case 0:
            return false;
            break;
        case 1:
            switch (rand()%4){
                case 0:
                    id="AM";
                    resistencia=(rand()%21)+5;
                    velocidad=0;
                    break;
                case 1:
                    id="AL";
                    resistencia=(rand()%16)+5;
                    velocidad=0;
                    break;
                case 2:
                    id="ES";
                    resistencia=12;
                    velocidad=0;
                    break;
                case 3:
                    id="AD";
                    resistencia=10;
                    velocidad=0;
                    break;
            }
            return true;
            break;
    }
}


#endif //AIRWAR_ENEMIGO_H
