#include "Observer.h"
#include <math.h>

Observer::Observer() {
    this -> subjectList = new ListaPaginada<Subject*>();
    this -> numberOfSubjects = 0;
    this -> updatedSubjects = 0;
}

void Observer::attach(Subject* subject) {
    subject->setObserver(this);
    subjectList->insertarAlInicio(subject);
    numberOfSubjects++;
}

void Observer::notify() {
    updatedSubjects++;
    if(updatedSubjects >= numberOfSubjects) {
        checkForCollisions();
    }
}

void Observer::checkForCollisions() {
    Nodo<Subject*>* node = subjectList->head;
    while(node != NULL && node->next != NULL) {
        Nodo<Subject*>* tmpNode = node->next;
        while(tmpNode != NULL) {
            if(collision(node->element,tmpNode->element)) {
                node->element->setActive(false);
                tmpNode->element->setActive(false);
                std::cout << "colision detectada\n";
            }
            tmpNode = tmpNode->next;
        }
        node = node->next;
    }
    cleanSubjectList();
    updatedSubjects = 0;
}

bool Observer::collision(Subject* subject1, Subject* subject2) {
    bool collision = false;
    if (distanceBetweenSubjects(subject1,subject2) <= sumOfSubjectsRadius(subject1,subject2)) {
        collision = true;
    }
    return collision;
}

int Observer::distanceBetweenSubjects(Subject* subject1, Subject* subject2) {
    return (int) sqrt(pow(subject1->getXPosition() - subject2->getXPosition(), 2) + pow(subject1->getYPosition() - subject2->getYPosition(), 2));
}

int Observer::sumOfSubjectsRadius(Subject* subject1, Subject* subject2) {
    return subject1->getRadius() + subject2->getRadius();
}

void Observer::cleanSubjectList() {
    Nodo<Subject*>* node = subjectList->head;
    while(node != NULL){
        if(!node->element->isActive()){
            Nodo<Subject*>* nodeToDelete = subjectList->head;
            node = node->next;
            delete(nodeToDelete->element);
            subjectList->remover(nodeToDelete);
            numberOfSubjects--;
        }
        else {
            node = node->next;
        }
    }
    std::cout << "lista de sujetos limpiada\n";
}

int Observer::getNumberOfSubjects() {
    return numberOfSubjects;
}

void Observer::setNumberOfSubjects(int numberOfSubjects) {
    Observer::numberOfSubjects = numberOfSubjects;
}

int Observer::getUpdatedSubjects() {
    return updatedSubjects;
}

void Observer::setUpdatedSubjects(int updatedSubjects) {
    Observer::updatedSubjects = updatedSubjects;
}
