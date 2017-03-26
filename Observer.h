#ifndef AIRWAR_OBSERVER_H
#define AIRWAR_OBSERVER_H

#include "Subject.h"
#include "ListaPaginada.h"
class Subject;

class Observer {
private:
    int numberOfSubjects;
    int updatedSubjects;
    ListaPaginada<Subject*>* subjectList;
public:
    Observer();
    void attach(Subject* subject);
    void notify();
    void checkForCollisions();
    bool collision(Subject* subject1, Subject* subject2);
    int distanceBetweenSubjects(Subject* subject1, Subject* subject2);
    int sumOfSubjectsRadius(Subject* subject1, Subject* subject2);
    void cleanSubjectList();

    int getNumberOfSubjects();
    void setNumberOfSubjects(int numberOfSubjects);
    int getUpdatedSubjects() ;
    void setUpdatedSubjects(int updatedSubjects);
};

#endif //AIRWAR_OBSERVER_H