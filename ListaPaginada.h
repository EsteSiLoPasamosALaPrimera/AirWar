#ifndef AIRWAR_LISTAPAGINADA_H
#define AIRWAR_LISTAPAGINADA_H

#include <iostream>
#include "Nodo.h"

using namespace std;

template<typename E>
class ListaPaginada{
public:
    Nodo<E>* head;
    Nodo<E>* tail;
    int tam;
    int tam_limite=2;
    string nom_archivo;
    bool primero=true;

    ListaPaginada();
    ListaPaginada(E pElement);
    ~ListaPaginada();

    void insercionPaginada(int pPos,E pElement);
    void insercionPaginadaAlInicio(E pElement);
    void insercionPaginadaAlFinal(E pElement);
    void removerPag(int pPos);
    void removerPag(Nodo<E>* ptr);
    void removerPagAlInicio();
    void removerPagAlFinal();
    void descargar(Nodo<E>*ptr);
    void imprimir();

private:
    void insertar(int pPos,E pElement);
    void insertarAlInicio(E pElement);
    void insertarAlFinal(E pElement);
    void remover(int pPos);
    void remover(Nodo<E>* ptr);
    void removerAlInicio();
    void removerAlFinal();

};

template<typename E>
ListaPaginada<E>::ListaPaginada() {
    head=tail=NULL;
    tam=0;
    nom_archivo="/home/alfredo/Inicio/Documentos/torres.txt";
    primero=true;
}

template<typename E>
ListaPaginada<E>::ListaPaginada(E pElement) {
    head=tail=new Nodo<E>(pElement);
    tam=1;
    nom_archivo="/home/alfredo/Inicio/Documentos/torres.txt";
    primero=true;

}
template<typename E>
ListaPaginada<E>::~ListaPaginada() {

}

template <typename E>
void ListaPaginada<E>::descargar(Nodo<E> *ptr) {
    ptr->element.descargar(primero);
    if(primero){
        primero=false;
    }
    remover(ptr);
}

template<typename E>
void ListaPaginada<E>::insercionPaginada(int pPos, E pElement) {
    if(pPos==0){
        insercionPaginadaAlInicio(pElement);
    }if(pPos>=tam-1){
        insercionPaginadaAlFinal(pElement);
    }
}

template<typename E>
void ListaPaginada<E>::insertar(int pPos, E pElement) {
    if(tam==0){
        head=tail=new Nodo<E>(pElement);
        tam++;
    }else if(pPos>=0){
        if(pPos==0){
            insertarAlInicio(pElement);
        }else if(pPos>tam-1){
            insertarAlFinal(pElement);
        }else{
            Nodo<E>* temp=head;
            while(pPos!=1){
                temp=temp->next;
                pPos--;
            }
            temp->next=new Nodo<E>(pElement,temp->next);
            tam++;
            temp=NULL;
            delete temp;
        }
    }else{
        cout<<"Posicion no valida"<<endl;
    }
}

template<typename E>
void ListaPaginada<E>::insertarAlInicio(E pElement) {
    if(tam==0){
        head=tail=new Nodo<E>(pElement);
    }else{
        Nodo<E>* curr=new Nodo<E>(pElement,head);
        head=curr;
        curr=NULL;
        delete curr;
    }
    tam++;
}


template<typename E>
void ListaPaginada<E>::insercionPaginadaAlInicio(E pElement) {
    insertarAlInicio(pElement);
    if(tam>tam_limite){
        descargar(tail);
    }
}

template<typename E>
void ListaPaginada<E>::insertarAlFinal(E pElement) {
    if(tam==0){
        head=tail=new Nodo<E>(pElement);
    }else{
        tail->next=new Nodo<E>(pElement);
        tail=tail->next;
    }
    tam++;
}

template<typename E>
void ListaPaginada<E>::insercionPaginadaAlFinal(E pElement) {
    if(tam==tam_limite){
        if(primero==false){
            cout<<"False"<<endl;
        }
        pElement.descargar(primero);
        tam++;
        if(primero){
            primero=false;
        }
    }else{
        insertarAlFinal(pElement);
    }
}

template<typename E>
void ListaPaginada<E>::removerAlInicio() {
    if(head!=NULL){
        if(head==tail){
            head=NULL;
            delete tail;
            tail=head;
        }else{
            Nodo<E>* temp=head;
            head=head->next;
            delete temp;
        }
        tam--;
    }else{
        cout<<"Lista vacia,imposible eliminar"<<endl;
    }

}

template<typename E>
void ListaPaginada<E>::removerPagAlInicio() {

}

template<typename E>
void ListaPaginada<E>::removerAlFinal() {
    if(tail!=NULL){
        if(head==tail){
            head=NULL;
            delete tail;
            tail=head;
        }else{
            Nodo<E>* temp=head;
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

template<typename E>
void ListaPaginada<E>::removerPagAlFinal() {

}

template<typename E>
void ListaPaginada<E>::remover(Nodo<E> *ptr) {
    E result=ptr->element;
    if(ptr==head){
        removerAlInicio();
    }else if(ptr==tail){
        removerAlFinal();
    }else{
        Nodo<E>*temp=head;
        while(temp->next!=ptr){
            temp=temp->next;
        }
        temp->next=temp->next->next;
        delete ptr;
        temp=NULL;
        delete temp;
        tam--;
    }
}

template<typename E>
void ListaPaginada<E>::removerPag(Nodo<E> *ptr) {

}

template <typename E>
void ListaPaginada<E>::remover(int pPos) {
    if(tam>0 && head!=NULL){
        if(pPos==0){
           removerAlInicio();
        }else if(pPos>=tam-1){
            removerAlFinal();
        }else{
            Nodo<E>*curr=head;
            Nodo<E>*temp=NULL;
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
    }else{
        cout<<"Lista esta vacia, no se puede eliminar";
    }
}

template<typename E>
void ListaPaginada<E>::removerPag(int pPos) {

}
#endif //AIRWAR_LISTAPAGINADA_H
