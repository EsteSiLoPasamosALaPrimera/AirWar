#ifndef AIRWAR_JETFIGHTER_H
#define AIRWAR_JETFIGHTER_H

#include <string>
#include "Enemigo.h"

class JetFighter:Enemigo {
private:
    std::string playerName;

    int totalHealth;
    int currentHealth;

    int ammunitionRounds;
    int fireRate;
    int bulletsPerShot;
    int gauge;

    int lazerPowerUp;
    int shieldPowerUp;
    int bombPowerUp;

    int enemiesDestroyed;
    int hitsTaken;
    int damageDeatl;
    int powerUpsCollected;

public:

};

#endif //AIRWAR_JETFIGHTER_H