#ifndef AIRWAR_STACK_H
#define AIRWAR_STACK_H

#include "SimpleNode.h"

template <class T>
class Stack {
private:
    int numberOfElements;
    SimpleNode<T>* topElementPtr;
public:
    Stack();
    Stack(T* dataPtr);
    ~Stack();
    void push(T* dataPtr);
    T* pop ();
    T* peek();
    int getNumberOfElements();
};

template <class T>
Stack<T>::Stack() {
    this -> numberOfElements = 0;
}

template <class T>
Stack<T>::Stack(T* dataPtr) {
    this -> topElementPtr = new SimpleNode<T>(dataPtr);
    this -> numberOfElements = 1;
}

template <class T>
Stack<T>::~Stack() {
    SimpleNode<T>* tmpSimpleNode = topElementPtr;
    while(tmpSimpleNode != NULL) {
        tmpSimpleNode = topElementPtr->getNextNode();
        delete topElementPtr;
        topElementPtr = tmpSimpleNode;
    }
}

//Probalbemente hayan problemas con el destructor de single node <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template <class T>
void Stack<T>::push(T* dataPtr) {
    if(numberOfElements == 0) {
        this -> topElementPtr = new SimpleNode<T>(dataPtr);
        this -> numberOfElements = 1;
    }
    else {
        SimpleNode<T>* tmpSimpleNodePtr = new SimpleNode<T>(dataPtr);
        tmpSimpleNodePtr->setNextNode(topElementPtr);
        topElementPtr = tmpSimpleNodePtr;
        numberOfElements++;
    }
}

template <class T>
T* Stack<T>::pop() {
    T* dataPtr = NULL;
    if (numberOfElements > 0) {
        dataPtr = topElementPtr->getDataPtr();
        SimpleNode<T>* tmpSimpleNodePtr = topElementPtr;
        topElementPtr = topElementPtr->getNextNode();
        delete tmpSimpleNodePtr;
        numberOfElements--;
    }
    return dataPtr;
}

template <class T>
T* Stack<T>::peek() {
    if (numberOfElements > 0) {
        return topElementPtr;
    }
    else {
        return NULL;
    }
}

template <class T>
int Stack<T>::getNumberOfElements() {
    return numberOfElements;
}

#endif //AIRWAR_STACK_H
