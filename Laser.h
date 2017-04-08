//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_LASER_H
#define AIRWAR_LASER_H

/**
 * @class Laser
 * @brief Clase que representa el tipo de municion laser.
 * @see Elemento
 */
class Laser:public Elemento{
public:
    Laser(int resist,int pPosX,int pPosY);

};

/**
 * @brief Constructor de la clase Laser
 * @param resist valor de resistencia del laser
 * @param pPosX valor de la posicion en el eje X del laser.
 * @param pPosY valor de la posicion en el eje Y del laser.
 */
Laser::Laser(int resist, int pPosX, int pPosY) {
    ataque=100;
    posX=pPosX;
    posY=pPosY;
    velocidad=-4;
    id="LS";

}

#endif //AIRWAR_LASER_H
