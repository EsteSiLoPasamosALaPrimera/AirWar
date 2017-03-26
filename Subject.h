#ifndef AIRWAR_SUBJECT_H
#define AIRWAR_SUBJECT_H

#include "Observer.h"
class Observer;

class Subject {
private:
    Observer* observer;
    int xPosition;
    int yPosition;
    int radius;
    bool active;
public:
    Subject(int xPosition, int yPosition, int radius);
    ~Subject();
    void notifyObserver();
    Observer* getObserver();
    void setObserver(Observer *observer);
    int getXPosition();
    void setXPosition(int xPosition);
    int getYPosition();
    void setYPosition(int yPosition);
    int getRadius();
    void setRadius(int radius);
    bool isActive() const;
    void setActive(bool active);
};

#endif //AIRWAR_SUBJECT_H