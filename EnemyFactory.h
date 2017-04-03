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

class EnemyFactory {
public:
    EnemyFactory();
    ~EnemyFactory();
    Elemento getTorreEnemiga();
    Elemento getNaveEnemiga();
};

EnemyFactory::EnemyFactory() {

}
EnemyFactory::~EnemyFactory() {

}

Elemento EnemyFactory::getTorreEnemiga(){
    int opc=rand()%2;
    if(opc==0){
        return Torre();
    }else{
        return TorreMisil();
    }
}

Elemento EnemyFactory::getNaveEnemiga() {
    int opc=rand()%3;
    if(opc==0){
        return Jet();
    }else if(opc==1){
        return JetKamikaze();
    }else{
        return Bombardero();
    }
}




#endif //AIRWAR_ENEMYFACTORY_H
