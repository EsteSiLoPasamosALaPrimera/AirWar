#ifndef AIRWAR_NODO_H
#define AIRWAR_NODO_H

#include <iostream>

using namespace std;

template<typename E>
class Nodo{
public:
    Nodo<E>* next=NULL;
    E element;
    int posX=0;
    int posY=0;

    Nodo(E pElement,Nodo<E>* pNext=NULL);
};

template<typename E>
Nodo<E>::Nodo(E pElement, Nodo<E> *pNext) {
    element=pElement;
    next=pNext;
}

#endif //AIRWAR_NODO_H

