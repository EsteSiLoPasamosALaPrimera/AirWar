//
// Created by alfredo on 31/03/17.
//

#ifndef AIRWAR_OBSERVER_H
#define AIRWAR_OBSERVER_H

#include "Lista_Paginada.h"

class Colisiones{
public:
    Colisiones();
    void verificarColision(Lista_Paginada listA,Lista_Paginada listB);

};

Colisiones::Colisiones() {

}

void Colisiones::verificarColision(Lista_Paginada listA, Lista_Paginada listB) {
    for(int i=0;i<listA.tam;i++){
        for(int j=0;j<listB.tam;j++){
            if(listA.recorrer(i).posY==listB.recorrer(j).posY){
                if(listA.recorrer(i).posX==listB.recorrer(j).posX){
                    listA.remover(i);
                    listB.remover(j);
                }
            }
        }
    }


}

#endif //AIRWAR_OBSERVER_H
