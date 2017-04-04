//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_LASER_H
#define AIRWAR_LASER_H

class Laser:public Elemento{
public:
    Laser(int resist,int pPosX,int pPosY);

};

Laser::Laser(int resist, int pPosX, int pPosY) {
    ataque=100;
    posX=pPosX;
    posY=pPosY;
    velocidad=-4;
    id="LS";

}

#endif //AIRWAR_LASER_H
