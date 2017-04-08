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
#include "Escolta.h"
#include "Mina.h"


/**
 * @class Lista_Paginada
 * @brief clase que implementa la lista enlazada simple con limites de memoria mediante paginacion
 * @see Elemento
 */
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

/**
 * @brief Constructor de la clase Lista_Paginada
 */
Lista_Paginada::Lista_Paginada() { }


/**
 * @brief Constructor de la clase Lista_Paginada
 * @param nombreArchivo nombre del archivo de texto donde se guardan los datos almacenados en memoria.
 */
Lista_Paginada::Lista_Paginada(string nombreArchivo) {
    head=tail=NULL;
    tam=0;
    nom_archivo=nombreArchivo;
    verificarEstado();
}

/**
 * @brief Constructor de la clase Lista_Paginada
 * @param nombreArchivo nombre del archivo de texto donde se guardan los datos almacenados en memoria.
 * @param NumPaginas numero de paginas maximas que pueden estar cargadas en memoria.
 */
Lista_Paginada::Lista_Paginada(string nombreArchivo,int NumPaginas) {
    head=tail=NULL;
    tam=0;
    nom_archivo=nombreArchivo;
    verificarEstado();
    num_paginas=NumPaginas;
}

/**
 * @brief Metodo encargado de verificar si el archivo donde se guardaran los datos existe o no.
 * En caso de que no exista lo crea.
 */
void Lista_Paginada::verificarEstado() {
    if(tam==0){
        ofstream arq(nom_archivo);
        arq.close();
    }
}

/**
 * @brief Metodo encargado de escribir los atributos de un objeto de tipo Elemento en un archivo de texto.
 * @param enemigo objeto de tipo Elemento cuyos atributos seran guardados
 * @see Elemento
 */
void Lista_Paginada::escritura(Elemento enemigo) {
    enemigo.descargar(validar,nom_archivo);
    validar=false;
}

/**
 * @brief Metodo encargado de escribir los atributos de un objeto de tipo Elemento en un archivo de texto.
 * @param enemigo objeto de tipo Elemento cuyos atributos seran guardados.
 * @see Elemento
 */
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

/**
 * @brief Metodo encargado de eliminar una linea de un archivo de texto
 * @param linea numero de la linea que se desea eliminar
 * @param caracter char que representa que una linea ha sido borrada.
 */
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

/**
 * @brief Metodo encargado de cargar la informacion de una linea del documento de texto.
 * @param linea numero de la linea que se desea leer.
 * @param caracter char que representa cuales lineas se deben ignorar cuando se lee.
 * @return un objeto de tipo Elemento o una de sus clases derivadas.
 */
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
    }else if(id=="LS"){
        return Laser(resist,posicX,posicY);
    }else if(id=="MS"){
        return Misil(resist,posicX,posicY);
    }else if(id=="MN"){
        return Mina(resist,posicX,posicY);
    }else if(id=="JT"){
        return Jet(resist,posicX,posicY);
    }else if(id=="SC"){
        return Escolta(resist,posicX,posicY);
    }else if(id=="JK"){
        return JetKamikaze(resist,posicX,posicY);
    }else if(id=="BD") {
        return Bombardero(resist,posicX,posicY);
    }else if(id=="AM" || id=="AL" || id=="ES" || id=="AD"){
        return PowerUp(id,resist,posicX,posicY);
    }
    else{
        cout<<"Problemas con el ID: "<<id<<" en: "<<nom_archivo<<endl;
    }
}

/**
 * @brief Metodo encargado de remover el ultimo elemento de la lista.
 */
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

/**
 * @brief Metodo encargado de remover el primer elemento de la lista.
 */
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

/**
 * @brief Metodo encargado de insertar al inicio de la lista.
 * @param enemigo objeto de tipo Elemento que sera insertado en la lista
 * @see Elemento
 */
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

/**
 * @brief Metodo encargado de insertar al final de la lista.
 * @param enemigo objeto de tipo Elemento que sera insertado en la lista
 * @see Elemento
 */
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

/**
 * @brief Metodo encargado de insertar en la lista.
 * @param pPos posicion de la lista donde se insertara el elemento.
 * @param enemigo objeto de tipo Elemento que sera insertado en la lista
 * @see Elemento
 * @see insertarAlInicio
 * @insertarAlFinal
 */
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

/**
 * @brief Metodo encargado de recorrer los nodos de la lista.
 * @param pPos posicion de la lista que se desea buscar.
 * @return objeto de tipo Elemento
 * @see lectura
 */
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


/**
 * @brief Metodo encargado de eliminar un elemento en una posicion dada de la lista.
 * @param pPos posicion del elemento que se desea eliminar
 * @see removerAlInicio,removerAlFinal
 */
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

/**
 * @brief Metodo encargado de cambiar la posicion en el eje Y de un elemento de la lista.
 * @param pPos posicion del elemento en la lista.
 * @param nueva posicion en el eje Y del elemento.
 * @see Elemento
 * @see escritura
 */
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

/**
 * @brief Metodo encargado de cambiar el atributo resistencia de un objeto de tipo Elemento en la lista.
 * @param pPos posicion del elemento en la lista.
 * @param ataque numero que se le restara a la resistencia del objeto.
 */
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

/**
 * @brief Metodo encargado de mostrar la informacion contenida en cada nodo de la lista.
 * @see recorrer
 */
void Lista_Paginada::imprimir() {
    for(int i=0;i<tam;i++){
        cout<<recorrer(i).info()<<endl;
    }
}
/**
 * @brief Metodo encargado de leer una linea del archivo de texto
 * @param linea numero de linea que se desea leer;
 * @param caracter char que representa las lineas que han sido borradas
 * @return un puntero de tipo Elemento
 */
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
    }else if(id=="MN"){
        return new Mina(resist,posicX,posicY);
    }else if(id=="JT"){
        return new Jet(resist,posicX,posicY);
    }else if(id=="JK"){
        return new JetKamikaze(resist,posicX,posicY);
    }else if(id=="SC"){
        return new Escolta(resist,posicX,posicY);
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

/**
 * @brief Metodo encargado de llamar la funcion moverse de la clase Elemento de todos los elementos de la lista.
 * @param refX posicion de referencia en el eje X, usualmente corresponde a la del jugador
 * @param refY posicion de referencia en el eje Y, usualmente corresponde a la del jugador.
 * @see lecturaPTR
 * @see Elemento
 */
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
            }else if(pTemp->element.getID()=="SC"){
                ptr= new Escolta(pTemp->element.resistencia,pTemp->element.posX,pTemp->element.posY);
            }else{
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

/**
 * @brief Metodo encargado de llamar el metodo darPowerUp() de los objetos de tipo Elemento
 * @param pPos posicion del elemento en la lista.
 * @see lectura
 * @see Elemento
 */
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
