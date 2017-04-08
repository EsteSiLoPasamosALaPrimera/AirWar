//
// Created by alfredo on 21/03/17.
//

#ifndef AIRWAR_NODO_H
#define AIRWAR_NODO_H


/**
 * @class Nodo
 * @brief Clase generica que representa un nodo para un estructura enlazada simple
 */
template<typename E>
class Nodo{
public:
    Nodo<E>* next=NULL;
    E element;
    int posX=0;
    int posY=0;

    Nodo(E pElement,Nodo<E>* pNext=NULL);
};

/**
 * @brief Constructor de la clase Nodo
 */
template<typename E>
Nodo<E>::Nodo(E pElement, Nodo<E> *pNext) {
    element=pElement;
    next=pNext;
}


#endif //AIRWAR_NODO_H
