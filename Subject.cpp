#include "Subject.h"

Subject::Subject(int xPosition, int yPosition, int radius) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->radius = radius;
    this->active = true;
}

Subject::~Subject(){

}

void Subject::notifyObserver() {
    std::cout << "observador notificado\n";
    observer->notify();
}

Observer* Subject::getObserver() {
    return observer;
}

void Subject::setObserver(Observer *observer) {
    Subject::observer = observer;
}

int Subject::getXPosition() {
    return xPosition;
}

void Subject::setXPosition(int xPosition) {
    Subject::xPosition = xPosition;
}

int Subject::getYPosition() {
    return yPosition;
}

void Subject::setYPosition(int yPosition) {
    Subject::yPosition = yPosition;
}

int Subject::getRadius() {
    return radius;
}

void Subject::setRadius(int radius) {
    Subject::radius = radius;
}

bool Subject::isActive() const {
    return active;
}

void Subject::setActive(bool active) {
    Subject::active = active;
}
