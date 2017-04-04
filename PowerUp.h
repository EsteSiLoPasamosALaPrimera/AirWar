//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_POWERUP_H
#define AIRWAR_POWERUP_H

#include <iostream>
using  namespace std;

class PowerUp:public Elemento{
public:
    PowerUp();
    PowerUp(string pID,float pPosX,float pPosY,float pPuntaje);
    void updateInfo(string pNombre,float pPosX,float pPosY,float pPuntaje);
};

PowerUp::PowerUp() {

}

PowerUp::PowerUp(string pID, float pPosX, float pPosY, float pPuntaje) {
    id=pID;
    posX=pPosX;
    posY=pPosY;
    resistencia=pPuntaje;
}

void PowerUp::updateInfo(string pNombre,float pPosX,float pPosY,float pPuntaje) {
    posX=pPosX;
    posY=pPosY;
    puntaje=pPuntaje;
    id=pNombre;
}
#endif //AIRWAR_POWERUP_H
