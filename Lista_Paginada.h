//
// Created by alfredo on 30/03/17.
//

#ifndef AIRWAR_LISTA_PAGINADA_H
#define AIRWAR_LISTA_PAGINADA_H

#include "Enemigo.h"
#include "Nodo.h"
#include "TorreMisil.h"

class Lista_Paginada{
public:
    int tam;
    string nom_archivo;
    Nodo<Enemigo>* head;
    Nodo<Enemigo>* tail;

    Lista_Paginada();
    void insertar(int pPos, Enemigo enemigo);
    void remover(int pPos);
    Enemigo recorrer(int pPos);
    void moverse();
    void imprimir();

private:
    int num_paginas=4;
    void insertarAlInicio(Enemigo enemigo);
    void insertarAlFinal(Enemigo enemigo);
    void removerAlInicio();
    void removerAlFinal();
    void escritura(Enemigo enemigo);
    void escritura(Enemigo enemigo,int pPos);
    Enemigo lectura(int linea,string caracter);
    void eliminar(int linea,string caracter);
    bool validar=true;

};

Lista_Paginada::Lista_Paginada() {
    head=tail=NULL;
    tam=0;
    nom_archivo="/home/alfredo/Inicio/Documentos/torres.txt";
}

void Lista_Paginada::escritura(Enemigo enemigo) {
    enemigo.descargar(validar);
    validar=false;
}

void Lista_Paginada::escritura(Enemigo enemigo, int pPos) {
    fstream archivo(nom_archivo);
    pPos=pPos-num_paginas;
    string texto="";
    int ref=0;
    while(pPos>=0){
        if(pPos==0){
            ref=archivo.tellp();
        }
        getline(archivo,texto);
        pPos--;
    }
    archivo.seekp(ref);
    archivo<<enemigo.info();
    archivo.close();

}

void Lista_Paginada::eliminar(int linea,string caracter) {
    fstream archivo(nom_archivo);
    string texto="";
    linea=linea-num_paginas;
    while(linea>=0){
        getline(archivo,texto);
        if(linea-1==0){
            archivo<<caracter;
        }
        linea--;
    }
}

Enemigo Lista_Paginada::lectura(int linea,string caracter) {
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
    int posicY=stoi(texto.substr(0,texto.find(';')));

    if(id=="TM"){
        return TorreMisil(resist,posicX,posicY);
    }else if(id=="TR"){
        return Torre(resist,posicX,posicY);
    }else if(id=="BA"){
        return
    }else{
        cout<<"Problemas con el ID"<<endl;
    }
}


void Lista_Paginada::removerAlFinal() {
    if(tail!=NULL){
        if(head==tail){
            head=NULL;
            delete tail;
            tail=head;
        }else{
            Nodo<Enemigo>* temp=head;
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
            Nodo<Enemigo>* temp=head;
            head=head->next;
            delete temp;
        }
        tam--;
    }else{
        cout<<"Lista vacia,imposible eliminar"<<endl;
    }
}

void Lista_Paginada::insertarAlInicio(Enemigo enemigo) {
    if(tam==0){
        head=tail=new Nodo<Enemigo>(enemigo);
    }else{
        Nodo<Enemigo>* curr=new Nodo<Enemigo>(enemigo,head);
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

void Lista_Paginada::insertarAlFinal(Enemigo enemigo) {
    if(tam==0){
        head=tail=new Nodo<Enemigo>(enemigo);
    }else{
        if(tam>=num_paginas){
            escritura(enemigo);
        }else{
            tail->next=new Nodo<Enemigo>(enemigo);
            tail=tail->next;
        }
    }
    tam++;
}

void Lista_Paginada::insertar(int pPos, Enemigo enemigo) {
    if(pPos>=0 && pPos<tam){
        if(tam<num_paginas){
            if(pPos==0){
                insertarAlInicio(enemigo);
            }else if(pPos==tam-1){
                insertarAlFinal(enemigo);
            }else{
                Nodo<Enemigo>* temp=head;
                while(pPos!=1){
                    temp=temp->next;
                    pPos--;
                }
                temp->next=new Nodo<Enemigo>(enemigo,temp->next);
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
                Nodo<Enemigo>* temp=head;
                while(pPos!=1){
                    temp=temp->next;
                    pPos--;
                }
                temp->next=new Nodo<Enemigo>(enemigo,temp->next);
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
    }else if(tam==0){
     insertarAlInicio(enemigo);
    }
    else{
        cout<<"Posicion fuera de rango"<<endl;
    }
}

Enemigo Lista_Paginada::recorrer(int pPos) {
    if(pPos>=0 && pPos<tam){
        if(pPos<num_paginas){
            Nodo<Enemigo>* temp=head;
            while(pPos!=0){
                pPos--;
                temp=temp->next;
            }
            return temp->element;
        }else{
            return lectura(pPos,"+");
        }
    }else{
        cout<<"Posicion invalida"<<endl;
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
                Nodo<Enemigo>*curr=head;
                Nodo<Enemigo>*temp=NULL;
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
                tam--;
            }else if(pPos==tam-1){
                tail->element=lectura(num_paginas,"+");
                eliminar(num_paginas,"+");
                tam--;
            }else{
                if(pPos<num_paginas){
                    Nodo<Enemigo>* pTemp=head;
                    while(pPos!=0){
                        pPos--;
                        pTemp=pTemp->next;
                    }
                    pTemp->element=lectura(num_paginas,"+");
                    eliminar(num_paginas,"+");
                    tam--;
                }else{
                    eliminar(pPos,"+");
                    tam--;
                }
            }
        }else{
            cout<<"Error al remover"<<endl;
        }
    }else{
        cout<<"Posicion invalida"<<endl;
    }
}

void Lista_Paginada::moverse() {
    Nodo<Enemigo>* pTemp=head;
    Enemigo eTemp;
    for(int i=0;i<tam;i++){
        if(i<num_paginas){
            pTemp->element.moverse();
            pTemp=pTemp->next;
        }else{
            eTemp=lectura(i,"+");
            eTemp.moverse();
            escritura(eTemp,i);
        }
    }


}



void Lista_Paginada::imprimir() {
    for(int i=0;i<tam;i++){
        cout<<recorrer(i).info();
    }
}


#endif //AIRWAR_LISTA_PAGINADA_H
