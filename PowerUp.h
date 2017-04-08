//
// Created by alfredo on 03/04/17.
//

#ifndef AIRWAR_POWERUP_H
#define AIRWAR_POWERUP_H

#include <iostream>
using  namespace std;

/**
 * @class PowerUp
 * @brief Clase derivada que representa los poderes especiales
 * @see Elemento
 */

class PowerUp:public Elemento{
public:
    PowerUp();
    PowerUp(string pID,float pPosX,float pPosY,float pPuntaje);
    void updateInfo(string pNombre,float pPosX,float pPosY,float pPuntaje);
};

/**
 * @brief Constructor de la clase PowerUp
 */
PowerUp::PowerUp() {

}

/**
 * @brief Constructor de la clase PowerUp
 * @param pID id del power up.
 * @param pPosX posicion en el eje X del power up.
 * @param pPosY posicion en el eje Y del power up.
 * @param pPuntaje puntaje del power up.
 */
PowerUp::PowerUp(string pID, float pPosX, float pPosY, float pPuntaje) {
    id=pID;
    posX=pPosX;
    posY=pPosY;
    resistencia=pPuntaje;
}

/**
 * @brief Metodo encargado de actualizar la informacion del power up.
 * @param pNombre nombre del id del power up
 * @param pPosX posicion en el eje X del power up.
 * @param pPosY posicion en el eje Y del power up.
 * @param pPuntaje puntaje del power up.
 */
void PowerUp::updateInfo(string pNombre,float pPosX,float pPosY,float pPuntaje) {
    posX=pPosX;
    posY=pPosY;
    puntaje=pPuntaje;
    id=pNombre;
}
#endif //AIRWAR_POWERUP_H
