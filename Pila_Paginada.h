//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_PILA_PAGINADA_H
#define AIRWAR_PILA_PAGINADA_H

#include <fstream>

/**
 * @class Pila_Paginada
 * @brief Clase que implementa una pila con manejo de memoria mediante paginacion.
 * @see PowerUp
 */

class Pila_Paginada{
public:
    Nodo<PowerUp>* head;
    Nodo<PowerUp>* tail;
    int tam;
    int num_paginas;
    string nom_archivo;
    Pila_Paginada();
    Pila_Paginada(string nombreArchivo);
    void insertar(PowerUp powerUp);
    void remover();

private:
    void insertarAlInicio(PowerUp powerUp);
    void descarga();
    void carga();
    bool validar;
};

/**
 * @brief Constructor de la clase Pila_Paginada
 */
Pila_Paginada::Pila_Paginada() {


}

/**
 * @brief Constructor de la clase Pila_Paginada
 * @param nombreArchivo nombre del archivo donde se descargan los datos almacenados.
 */
Pila_Paginada::Pila_Paginada(string nombreArchivo) {
    head=tail=NULL;
    tam=0;
    num_paginas=5;
    nom_archivo=nombreArchivo;
    validar=true;
    ofstream arquive(nombreArchivo);
    arquive.close();

}

/**
 * @brief Metodo que insertar al inicio de la pila
 * @param powerUp objeto de la clase PowerUp que sera almacenado en la pila.
 * @see PowerUp
 */
void Pila_Paginada::insertarAlInicio(PowerUp powerUp) {
    if(head==NULL){
        head=tail=new Nodo<PowerUp>(powerUp);
    }else{
        Nodo<PowerUp>* curr=new Nodo<PowerUp>(powerUp,head);
        head=curr;
        curr=NULL;
        delete curr;
    }
    tam++;
}

/**
 * @brief Metodo encargado de descargar las paginas de memoria al documento de texto
 */
void Pila_Paginada::descarga() {
    if(validar){
        fstream archivo(nom_archivo);
        archivo<<tail->element.info()<<endl;
        archivo.close();
        validar=false;
    }else{
        fstream archivo(nom_archivo,ios::app);
        archivo<<tail->element.info()<<endl;
        archivo.close();
    }
    Nodo<PowerUp>* temp=head;
    while(temp->next!=tail){
        temp=temp->next;
    }
    tail=temp;
    temp=temp->next;
    delete temp;
    tail->next=NULL;
}

/**
 * @brief Metodo encargado de insertar un objeto de tipo PowerUp en la pila verificando si se excede o no el limite de memoria
 * @param powerUp objeto de tipo PowerUp que sera almacenado en la pila
 * @see insertarAlInicio
 * @see descarga
 */
void Pila_Paginada::insertar(PowerUp powerUp) {
    if(tam>=num_paginas){
        insertarAlInicio(powerUp);
        descarga();
    }else{
        insertarAlInicio(powerUp);
    }
}

/**
 * @brief Metodo encargado de cargar en memoria los datos almacenados en el archivo de texto
 * @see PowerUp, updateInfo
 */
void Pila_Paginada::carga() {
    fstream archivo(nom_archivo);
    string texto="";
    int pPos=0;
    int max=tam-num_paginas;
    do{
        pPos=archivo.tellp();
        getline(archivo,texto);
        if(texto.find("+")!=0){
            max--;
        }
    }while(max>0);
    archivo.seekp(pPos);
    archivo<<"+";
    archivo.close();
    string nomb=texto.substr(0,texto.find(';'));
    texto=texto.substr(texto.find(';')+1);
    float aument=stof(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    float posicX=stof(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    float posicY=stof(texto.substr(0,texto.find(';')));

    tail->element.updateInfo(nomb,posicX,posicY,aument);
}

/**
 * @brief Metodo encargado de eliminar el primer elemento de la pila
 * @see carga
 */
void Pila_Paginada::remover() {
    if(head!=NULL){
        if(tam>num_paginas){
            tail->next=head;
            head=head->next;
            tail=tail->next;
            tail->next=NULL;
            carga();
        }else{
            if(head==tail){
                delete tail;
                head=tail=NULL;
            }else{
                Nodo<PowerUp>* temp=head;
                head=head->next;
                temp->next=NULL;
                delete temp->next;
                temp=NULL;
                delete temp;
            }
        }
        tam--;
    }else{
        cout<<"Lista vacia no se puede eliminar"<<endl;
    }
}

#endif //AIRWAR_PILA_PAGINADA_H
