//
// Created by alfredo on 02/04/17.
//

#ifndef AIRWAR_ENEMYFACTORY_H
#define AIRWAR_ENEMYFACTORY_H

#include "Torre.h"
#include "TorreMisil.h"
#include "Jet.h"
#include "JetKamikaze.h"
#include "Bombardero.h"
#include "Mina.h"

/**
 * @class EnemyFactory
 * @brief Clase basada en el patron de diseño Factory
 */

class EnemyFactory {
public:
    EnemyFactory();
    ~EnemyFactory();
    Elemento getTorreEnemiga();
    Elemento getNaveEnemiga();
};


/**
 * @brief Constructor de la clase EnemyFactory
 */
EnemyFactory::EnemyFactory() {

}

/**
 * @brief Destructor de la clase EnemyFactory
 */
EnemyFactory::~EnemyFactory() {

}

/**
 * @brief Metodo que devuelve una instancia de las clases Torre,Mina o TorreMisil
 * @return un objeto de una clases derivada de Elemento, ya sea Torre,Mina o TorreMisil
 * @see Torre
 * @see TorreMisil
 * @see Elemento
 */
Elemento EnemyFactory::getTorreEnemiga(){
    int opc=rand()%3;
    if(opc==0){
        return Torre();
    }else if(opc==1){
        return TorreMisil();
    }else{
        return Mina();
    }
}

/**
 * @brief Metodo que devuelve una instancia de las clases Jet,JetKamikaze,Escolta y Bombardero
 * @return un objeto de una clase derivada de Elemento , ya sea Jet,JetKamikaze,Escolta o Bombardero.
 * @see Jet
 * @see JetKamikaze
 * @see Escolta
 * @see Bombardero
 * @see Elemento
 */
Elemento EnemyFactory::getNaveEnemiga() {
    int opc=rand()%4;
    if(opc==0){
        return Jet();
    }else if(opc==1){
        return JetKamikaze();
    }else if(opc==2){
        return Bombardero();
    }else{
        return Escolta();
    }
}

#endif //AIRWAR_ENEMYFACTORY_H
