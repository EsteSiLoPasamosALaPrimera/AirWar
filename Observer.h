#ifndef AIRWAR_OBSERVER_H
#define AIRWAR_OBSERVER_H


class Observer {
private:
    list<Subject>* subjectList;
    int numberOfSubjects;
    int updatedSubjects;
public:

    void attach(Subject subject);
    void deattach(Subject subject);
    void updateSubject();
    void checkForColittions();
};


#endif //AIRWAR_OBSERVER_H
