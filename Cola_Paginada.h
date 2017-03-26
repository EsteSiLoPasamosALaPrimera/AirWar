//
// Created by alfredo on 21/03/17.
//

#ifndef AIRWAR_COLA_PAGINADA_H
#define AIRWAR_COLA_PAGINADA_H

#include <iostream>
#include "Nodo.h"

using namespace std;

template <typename E>
class Cola_Paginada{
public:
    Nodo<E>* head;
    Nodo<E>*tail;
    int tam=0;
    int tam_limite;


    ~Cola_Paginada();
    Cola_Paginada();
    Cola_Paginada(E pElement);
    void insertar(E pElement);
    void insertar(E pElement,int posX,int posY);
    E remover();
    void clear();
};

template <typename E>
Cola_Paginada<E>::Cola_Paginada() {
    head=tail=NULL;
    tam=0;
}

template <typename E>
Cola_Paginada<E>::Cola_Paginada(E pElement) {
    head=tail=new Nodo<E>(pElement);
    tam=1;
}

template<typename E>
void Cola_Paginada<E>::insertar(E pElement) {
    if(tam!=0){
        tail->next=new Nodo<E>(pElement);
        tail=tail->next;
    }else{
        head=tail=new Nodo<E>(pElement);
    }
    tam++;

}

template<typename E>
void Cola_Paginada<E>::insertar(E pElement, int posX, int posY) {
    if(tam!=0){
        tail->next=new Nodo<E>(pElement);
        tail=tail->next;
        tail->posX=posX;
        tail->posY=posY;
    }else{
        head=tail=new Nodo<E>(pElement);
        head->posX=posX;
        head->posY;
    }
    tam++;
}


template<typename E>
E Cola_Paginada<E>::remover() {
    if(tam!=0){
        E result=head->element;
        Nodo<E>* current=head;
        head=head->next;
        delete current;
        tam--;
        return result;
    }
}
template<typename E>
void Cola_Paginada<E>::clear() {
    while(tam!=0){
        remover();
    }
}

template <typename E>
Cola_Paginada<E>::~Cola_Paginada() {
    clear();
}

#endif //AIRWAR_COLA_PAGINADA_H
