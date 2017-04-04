//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_LISTA_PAGINADA_H
#define AIRWAR_LISTA_PAGINADA_H

#include "Nodo.h"
#include "Torre.h"
#include "TorreMisil.h"
#include "Bala.h"
#include "BalaTorre.h"
#include "BalaMisil.h"
#include "Jet.h"
#include "JetKamikaze.h"
#include "Bombardero.h"
#include "Laser.h"
#include "Misil.h"
#include "PowerUp.h"

class Lista_Paginada{
public:
    int tam;
    string nom_archivo;
    Nodo<Elemento>* head;
    Nodo<Elemento>* tail;
    int num_paginas=4;

    Lista_Paginada();
    Lista_Paginada(string nombreArchivo);
    Lista_Paginada(string nombreArchivo, int NumPaginas);
    void insertar(int pPos, Elemento enemigo);
    void remover(int pPos);
    Elemento recorrer(int pPos);
    void verificarEstado();
    void setPosY(int pPos,int pPosY);
    bool bajarResistencia(int pPos,int ataque);
    void moverse(int refX,int refY);
    void imprimir();
    bool darPowerUps(int pPos);

private:
    void insertarAlInicio(Elemento enemigo);
    void insertarAlFinal(Elemento enemigo);
    void removerAlInicio();
    void removerAlFinal();
    void escritura(Elemento enemigo);
    void escritura(Elemento enemigo,string caracter,int pPos);
    Elemento lectura(int linea,string caracter);
    Elemento* lecturaPTR(int linea,string caracter);
    void eliminar(int linea,string caracter);
    bool validar=true;

};

Lista_Paginada::Lista_Paginada() { }

Lista_Paginada::Lista_Paginada(string nombreArchivo) {
    head=tail=NULL;
    tam=0;
    nom_archivo=nombreArchivo;
    verificarEstado();
}

Lista_Paginada::Lista_Paginada(string nombreArchivo,int NumPaginas) {
    head=tail=NULL;
    tam=0;
    nom_archivo=nombreArchivo;
    verificarEstado();
    num_paginas=NumPaginas;
}

void Lista_Paginada::verificarEstado() {
    if(tam==0){
        ofstream arq(nom_archivo);
        arq.close();
    }
}

void Lista_Paginada::escritura(Elemento enemigo) {
    enemigo.descargar(validar,nom_archivo);
    validar=false;
}

void Lista_Paginada::escritura(Elemento enemigo,string caracter, int pPos) {
    fstream archivo(nom_archivo);
    pPos=pPos-num_paginas;
    string texto="";
    int ref=0;
    while(pPos>=0){
        if(pPos==0){
            ref=archivo.tellp();
        }
        getline(archivo,texto);
        if(texto.find(caracter)!=0){
            pPos--;
        }
    }
    archivo.seekp(ref);
    archivo<<enemigo.info()<<endl;
    archivo.close();
}

void Lista_Paginada::eliminar(int linea,string caracter) {
    fstream archivo(nom_archivo);
    string texto="";
    linea=linea-num_paginas;
    int sav=0;
    while(linea>=0){
        sav=archivo.tellg();
        getline(archivo,texto);
        if(texto.find(caracter)!=0){
            if(linea==0){
                archivo.seekg(sav);
                archivo<<caracter;
            }
            linea--;
        }
    }
    archivo.close();
    tam--;
}

Elemento Lista_Paginada::lectura(int linea,string caracter) {
    fstream archivo(nom_archivo);
    string texto="";
    linea=linea-num_paginas;
    while(linea>=0){
        getline(archivo,texto);
        if(texto.find(caracter)!=0){
            linea--;
        }
    }
    archivo.close();
    string id=texto.substr(0,texto.find(';'));
    texto=texto.substr(texto.find(';')+1);
    int resist=stoi(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    int posicX=stoi(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    float posicY=stof(texto.substr(0,texto.find(';')));

    if(id=="TM"){
        return TorreMisil(resist,posicX,posicY);
    }else if(id=="TR"){
        return Torre(resist,posicX,posicY);
    }else if(id=="BA"){
        return Bala(resist,posicX,posicY);
    }else if(id=="BT"){
        return BalaTorre(resist,posicX,posicY);
    }else if(id=="BM"){
        return BalaMisil(resist,posicX,posicY);
    }else if(id=="JT"){
        return Jet(resist,posicX,posicY);
    }else if(id=="JK"){
        return JetKamikaze(resist,posicX,posicY);
    }else if(id=="BD") {
        return Bombardero(resist,posicX,posicY);
    }else if(id=="LS"){
        return Laser(resist,posicX,posicY);
    }else if(id=="MS"){
        return Misil(resist,posicX,posicY);
    }else if(id=="AM" || id=="AL" || id=="ES" || id=="AD"){
        return PowerUp(id,resist,posicX,posicY);
    }
    else{
        cout<<"Problemas con el ID: "<<id<<" en: "<<nom_archivo<<endl;
    }
}


void Lista_Paginada::removerAlFinal() {
    if(tail!=NULL){
        if(head==tail){
            head=NULL;
            delete tail;
            tail=head;
        }else{
            Nodo<Elemento>* temp=head;
            while(temp->next!=tail){
                temp=temp->next;
            }
            delete tail;
            tail=temp;
            tail->next=NULL;
            temp=NULL;
            delete temp;
        }
        tam--;
    }else{
        cout<<"Lista vacia,imposible eliminar"<<endl;
    }
}

void Lista_Paginada::removerAlInicio() {
    if(head!=NULL){
        if(head==tail){
            head=NULL;
            delete tail;
            tail=head;
        }else{
            Nodo<Elemento>* temp=head;
            head=head->next;
            delete temp;
        }
        tam--;
    }else{
        cout<<"Lista vacia,imposible eliminar"<<endl;
    }
}

void Lista_Paginada::insertarAlInicio(Elemento enemigo) {
    if(tam==0){
        head=tail=new Nodo<Elemento>(enemigo);
    }else{
        Nodo<Elemento>* curr=new Nodo<Elemento>(enemigo,head);
        head=curr;
        curr=NULL;
        delete curr;
    }
    tam++;
    if(tam>num_paginas){
        escritura(tail->element);
        removerAlFinal();
        tam++;
    }
}

void Lista_Paginada::insertarAlFinal(Elemento enemigo) {
    if(tam==0){
        head=tail=new Nodo<Elemento>(enemigo);
    }else{
        if(tam>=num_paginas){
            escritura(enemigo);
        }else{
            tail->next=new Nodo<Elemento>(enemigo);
            tail=tail->next;
        }
    }
    tam++;
}

void Lista_Paginada::insertar(int pPos, Elemento enemigo) {
    if(tam==0){
        insertarAlInicio(enemigo);
    }else{
        if(pPos>=0 && pPos<tam){
            if(tam<num_paginas){
                if(pPos==0){
                    insertarAlInicio(enemigo);
                }else if(pPos==tam-1){
                    insertarAlFinal(enemigo);
                }else{
                    Nodo<Elemento>* temp=head;
                    while(pPos!=1){
                        temp=temp->next;
                        pPos--;
                    }
                    temp->next=new Nodo<Elemento>(enemigo,temp->next);
                    tam++;
                    temp=NULL;
                    delete temp;
                }
            }else if(tam>=num_paginas){
                if(pPos==0){
                    insertarAlInicio(enemigo);
                }else if(pPos==tam-1){
                    insertarAlFinal(enemigo);
                }else{
                    Nodo<Elemento>* temp=head;
                    while(pPos!=1){
                        temp=temp->next;
                        pPos--;
                    }
                    temp->next=new Nodo<Elemento>(enemigo,temp->next);
                    tam++;
                    temp=NULL;
                    delete temp;
                    escritura(tail->element);
                    removerAlFinal();
                    tam++;
                }
            }else{
                cout<<"Error al insertar"<<endl;
            }
        }
        else{
            cout<<"Posicion: "<<pPos<<" con tam: "<<tam<<" fuera de rango para insertar en:"<<nom_archivo<<endl;
        }
    }
}

Elemento Lista_Paginada::recorrer(int pPos) {
    if(pPos>=0 && pPos<tam){
        if(pPos<num_paginas){
            Nodo<Elemento>* temp=head;
            while(pPos!=0){
                pPos--;
                temp=temp->next;
            }
            return temp->element;
        }else{
            return lectura(pPos,"+");
        }
    }else{
        cout<<"Posicion invalida al recorrer:Fuera de rango con: "<<pPos<<" con: "<<tam<<endl;
    }
}


void Lista_Paginada::remover(int pPos) {
    if(pPos>=0 && pPos<tam){
        if(tam<=num_paginas){
            if(pPos==0){
                removerAlInicio();
            }else if(pPos==tam-1){
                removerAlFinal();
            }else{
                Nodo<Elemento>*curr=head;
                Nodo<Elemento>*temp=NULL;
                while(pPos!=1){
                    curr=curr->next;
                    pPos--;
                }
                temp=curr->next;
                curr->next=curr->next->next;
                delete temp;
                curr=NULL;
                delete curr;
                tam--;
            }
        }else if(tam>num_paginas){
            if(pPos==0){
                head->element=lectura(num_paginas,"+");
                eliminar(num_paginas,"+");
            }else if(pPos==tam-1){
                eliminar(pPos,"+");
            }else{
                if(pPos<num_paginas){
                    Nodo<Elemento>* pTemp=head;
                    while(pPos!=0){
                        pPos--;
                        pTemp=pTemp->next;
                    }
                    pTemp->element=lectura(num_paginas,"+");
                    eliminar(num_paginas,"+");
                }else{
                    eliminar(pPos,"+");
                }
            }
        }else{
            cout<<"Error al remover"<<endl;
        }
    }else{
        cout<<"Posicion invalida al remover, pos: "<<pPos<<endl;
    }
}

void Lista_Paginada::setPosY(int pPos, int pPosY) {
    if(pPos>=0 && pPos<tam){
        if(pPos<num_paginas){
            Nodo<Elemento>* temp=head;
            while(pPos!=0){
                pPos--;
                temp=temp->next;
            }
            temp->element.posY=pPosY;
        }else{
            Elemento enTempl=lectura(pPos,"+");
            enTempl.posY=pPosY;
            escritura(enTempl,"+",pPos);
        }
    }else{
        cout<<"Posicion invalida al cambiar posY"<<endl;
    }
}

bool Lista_Paginada::bajarResistencia(int pPos,int ataque) {
    if(pPos>=0 && pPos<tam){
        if(pPos<num_paginas){
            Nodo<Elemento>* temp=head;
            while(pPos!=0){
                pPos--;
                temp=temp->next;
            }
            if(temp->element.getID()!="AL" && temp->element.getID()!="AM" && temp->element.getID()!="AD" && temp->element.getID()!="ES"){
             temp->element.resistencia-=ataque;
            }
            if(temp->element.resistencia<=0){
                return true;
            }else{
                return false;
            }
        }else{
            Elemento enTempl=lectura(pPos,"+");
            if(enTempl.getID()!="AL" && enTempl.getID()!="AM" && enTempl.getID()!="AD" && enTempl.getID()!="ES"){
                enTempl.resistencia-=ataque;
                escritura(enTempl,"+",pPos);
            }
            if(enTempl.resistencia<=0){
                return true;
            }else{
                return false;
            }
        }
    }else{
        cout<<"Posicion invalida al reducir resistencia"<<endl;
    }
}

void Lista_Paginada::imprimir() {
    for(int i=0;i<tam;i++){
        cout<<recorrer(i).info()<<endl;
    }
}

Elemento* Lista_Paginada::lecturaPTR(int linea, string caracter) {
    fstream archivo(nom_archivo);
    string texto="";
    linea=linea-num_paginas;
    while(linea>=0){
        getline(archivo,texto);
        if(texto.find(caracter)!=0){
            linea--;
        }
    }
    archivo.close();
    string id=texto.substr(0,texto.find(';'));
    texto=texto.substr(texto.find(';')+1);
    int resist=stoi(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    int posicX=stoi(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    float posicY=stof(texto.substr(0,texto.find(';')));

    if(id=="TM"){
        return new TorreMisil(resist,posicX,posicY);
    }else if(id=="TR"){
        return new Torre(resist,posicX,posicY);
    }else if(id=="BA"){
        return new Bala(resist,posicX,posicY);
    }else if(id=="BT"){
        return new BalaTorre(resist,posicX,posicY);
    }else if(id=="BM"){
        return new BalaMisil(resist,posicX,posicY);
    }else if(id=="JT"){
        return new Jet(resist,posicX,posicY);
    }else if(id=="JK"){
        return new JetKamikaze(resist,posicX,posicY);
    }else if(id=="BD") {
        return new Bombardero(resist,posicX,posicY);
    }else if(id=="LS"){
        return new Laser(resist,posicX,posicY);
    }else if(id=="MS"){
        return new Misil(resist,posicX,posicY);
    }else if(id=="AM" || id=="AL" || id=="ES" || id=="AD"){
        return new PowerUp(id,resist,posicX,posicY);
    }
    else{
        cout<<"Problemas con el ID en PTR: "<<id<<" en: "<<nom_archivo<<endl;
    }
}

void Lista_Paginada::moverse(int refX,int refY) {

    Nodo<Elemento>* pTemp=head;
    Elemento* ptr=NULL;
    for(int i=0;i<tam;i++){
        if(i<num_paginas){
            if(pTemp->element.getID()=="JT"){
                ptr=new Jet(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }else if(pTemp->element.getID()=="BT"){
                ptr=new BalaTorre(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }else if(pTemp->element.getID()=="BM"){
                ptr=new BalaMisil(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }else if(pTemp->element.getID()=="JK"){
                ptr= new JetKamikaze(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }else if(pTemp->element.getID()=="BD"){
                ptr= new Bombardero(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }else if(pTemp->element.getID()=="MS"){
                ptr= new Misil(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }
            else{
                ptr=&pTemp->element;
            }
            ptr->moverse(refX,refY);
            pTemp->element=*ptr;
            pTemp=pTemp->next;
        }else{
            ptr=lecturaPTR(i,"+");
            ptr->moverse(refX,refY);
            escritura(*ptr,"+",i);
        }
    }
    pTemp=NULL;
    delete pTemp;
    ptr=NULL;
    delete ptr;
}


bool Lista_Paginada::darPowerUps(int pPos) {
    if(pPos>=0 && pPos<tam){
        bool respuesta=false;
        if(pPos<num_paginas){
            Nodo<Elemento>* temp=head;
            while(pPos!=0){
                pPos--;
                temp=temp->next;
            }

            respuesta=temp->element.darPowerUp();
        }else{
            Elemento enTempl=lectura(pPos,"+");
            respuesta=enTempl.darPowerUp();
            escritura(enTempl,"+",pPos);
        }
        return respuesta;
    }else{
        cout<<"Posicion invalida al convertir a power up"<<endl;
    }


}

#endif //AIRWAR_LISTA_PAGINADA_H
