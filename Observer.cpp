#include "Observer.h"

void attach(Subject subject) {
    subjectList->add(subject);
    numberOfSubjects++;
}

void deattach(Subject subject) {
    subjectList->eliminate(subject);
    numberOfSubjects--;
}

void updateSubject() {
    updatedSubjects++;
    if(updatedSubjects >= numberOfSubjects) {
        checkForColittions();
    }
}

void checkForColittions() {

}
