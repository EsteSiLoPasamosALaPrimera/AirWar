#ifndef AIRWAR_JETFIGHTER_H
#define AIRWAR_JETFIGHTER_H

#include <string>

class JetFighter {
private:
    std::string playerName;

    int totalHealth;
    int currentHealth;

    int xPosition;
    int yPosition;

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

