//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_ENEMIGO_H
#define AIRWAR_ENEMIGO_H
#include<iostream>
#include "fstream"

using namespace std;


/**
 * @class Elemento
 * @brief Clase base de los elementos que deben ser representados en la interfaz grafica.
 */
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


/**
 * @brief Constructor de la clase Elemento
 * Inicializa todos los atributos necesarios para representar el objeto graficamente.
 */
Elemento::Elemento() {
    posX=posY=0;
    ataque=0;
    velocidad=0;
    resistencia=0;
    puntaje=0;
}

/**
 * @brief Metodo que cambia el numero de caracteres que tiene un string.
 * @param txt variable de tipo string sobre la cual se realiza la operacion.
 * @param max nuevo tamaño que tendra el string.
 * @return el nuevo string con el tamaño modificado
 */
string Elemento::fillString(string txt,int max) {
    while(txt.size()<max){
        txt="0"+txt;
    }
    if(txt.size()>max){
        txt=txt.substr(0,max);
    }
    return txt;
}


/**
 * @brief Metodo que descarga la informacion de un objeto de tipo Elemento en un archivo de texto.
 * @param iteracion valor booleano que indica si se debe reiniciar el contenido del archivo o solo agregar al final.
 * @param nomArchivo nombre y direccion del archivo donde se realizara la descarga.
 */
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

/**
 * @brief Destructor de la clase Elemento.
 */
Elemento::~Elemento() {
}

/**
 * @brief Metodo que encapsula en un string los atributos principales de un objeto de tipo Elemento.
 * @return string con la informacion del objeto.
 * @see fillString
 */
string Elemento::info() {
    string infor=id+";"+fillString(to_string(resistencia),5)+";"+fillString(to_string(posX),5)+";"+fillString(to_string(posY),5)+";";
    return infor;
}
/**
 * @brief Metodo que devuelve el atributo id del objeto.
 * @return un string con el id del objeto.
 */
string Elemento::getID() {
    return id;
}

/**
 * brief Metodo que aletoriamente define si un objeto de tipo Elemento debe ser tratado como un power-up por la logica del juego o no.
 * @return true si el objeto se "convirtio en un power up" o false en caso contrario.
 */
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
