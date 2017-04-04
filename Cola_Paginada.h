//
// Created by alfredo on 21/03/17.
//

#ifndef AIRWAR_COLA_PAGINADA_H
#define AIRWAR_COLA_PAGINADA_H

#include "Nodo.h"
#include "Elemento.h"
#include "Jet.h"
#include "JetKamikaze.h"
#include "Bombardero.h"

class Cola_Paginada{
public:
    Nodo<Elemento>* head;
    Nodo<Elemento>* tail;
    int tam;
    string nom_archivo;
    int num_paginas;

    Cola_Paginada();
    Cola_Paginada(string nomArchivo);
    void insertar(Elemento elemento);
    void remover();

private:
    void carga();
    void descarga(Elemento elemento);
    bool validar;
    void insertarAlFinal(Elemento elemento);
};

Cola_Paginada::Cola_Paginada() { }

Cola_Paginada::Cola_Paginada(string nomArchivo) {
    head=tail=NULL;
    tam=0;
    nom_archivo=nomArchivo;
    ofstream arquive(nom_archivo);
    arquive.close();
    validar=true;
}

void Cola_Paginada::carga() {
    fstream archivo(nom_archivo);
    string texto="";
    int pPos=0;
    do{
        pPos=archivo.tellp();
        getline(archivo,texto);
    }while(texto.find("+")==0);
    archivo.seekp(pPos);
    archivo<<"+";
    archivo.close();

    string nomb=texto.substr(0,texto.find(';'));
    texto=texto.substr(texto.find(';')+1);
    float resist=stof(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    float posicX=stof(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    float posicY=stof(texto.substr(0,texto.find(';')));

    if(nomb=="JT"){
        tail->element=Jet(resist,posicX,posicY);
    }else if(nomb=="JK"){
        tail->element=JetKamikaze(resist,posicX,posicY);
    }else if(nomb=="BD"){
        tail->element=Bombardero(resist,posicX,posicY);
    }else{
        cout<<"En cola paginada no se puedo identificar el id: "<<nomb<<endl;
    }
}

void Cola_Paginada::descarga(Elemento elemento) {
    if(validar){
        fstream archivo(nom_archivo);
        archivo<<elemento.info()<<endl;
        archivo.close();
        validar=false;
    }else{
        fstream archivo(nom_archivo,ios::app);
        archivo<<elemento.info()<<endl;
        archivo.close();
    }
    tam++;
}

void Cola_Paginada::insertarAlFinal(Elemento elemento) {
    if(tam==0){
        head=tail=new Nodo<Elemento>(elemento);
    }else{
        tail->next=new Nodo<Elemento>(elemento);
        tail=tail->next;
    }
    tam++;
}

void Cola_Paginada::insertar(Elemento elemento) {
    if(tam>=num_paginas){
        descarga(elemento);
    }else{
        insertarAlFinal(elemento);
    }
}

void Cola_Paginada::remover() {
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
                Nodo<Elemento>* temp=head;
                head=head->next;
                temp->next=NULL;
                delete temp->next;
                temp=NULL;
                delete temp;
            }
        }
        tam--;
    }else{
        cout<<"Error al remover en cola paginada con: "<<nom_archivo<<endl;
    }

}

#endif //AIRWAR_COLA_PAGINADA_H
