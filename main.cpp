class Subject;
#include "Observer.h"

int main() {
    Observer* observer = new Observer();
    Subject* subject1 = new Subject(1,0,0);
    Subject* subject2 = new Subject(1,0,0);
    Subject* subject3 = new Subject(1,0,0);
    Subject* subject4 = new Subject(1,0,0);


    observer->attach(subject1);
    observer->attach(subject2);
    observer->attach(subject3);
    observer->attach(subject4);

    std::cout << observer->getNumberOfSubjects() << " " << observer->getUpdatedSubjects() << "\n";
    subject1->notifyObserver();
    std::cout << observer->getNumberOfSubjects() << " " << observer->getUpdatedSubjects() << "\n";
    subject2->notifyObserver();
    std::cout << observer->getNumberOfSubjects() << " " << observer->getUpdatedSubjects() << "\n";
    subject3->notifyObserver();
    std::cout << observer->getNumberOfSubjects() << " " << observer->getUpdatedSubjects() << "\n";
    subject4->notifyObserver();
    std::cout << observer->getNumberOfSubjects() << " " << observer->getUpdatedSubjects() << "\n";

     return 0;
}