#ifndef AIRWAR_SIMPLENODE_H
#define AIRWAR_SIMPLENODE_H

template <class T>
class SimpleNode {
private:
    T* dataPtr;
    SimpleNode* nodePtr;
public:
    SimpleNode(T* dataPtr);
    ~SimpleNode();
    void setNextNode(SimpleNode* nodePtr);
    SimpleNode* getNextNode();
    void setDataPtr(T* dataPtr);
    T* getDataPtr();
    void setData(T data);
    T getData();
};

template <class T>
SimpleNode<T>::SimpleNode(T* dataPtr) {
    this -> dataPtr = dataPtr;
    this -> nodePtr = NULL;
}

template <class T>
SimpleNode<T>::~SimpleNode() { }

template <class T>
void SimpleNode<T>::setNextNode(SimpleNode<T>* nodePtr) {
    this -> nodePtr = nodePtr;
}

template <class T>
SimpleNode<T>* SimpleNode<T>::getNextNode() {
    return nodePtr;
}

template <class T>
void SimpleNode<T>::setDataPtr(T* dataPtr) {
    this -> dataPtr = dataPtr;
}

template <class T>
T* SimpleNode<T>::getDataPtr() {
    return this -> dataPtr;
}

template <class T>
void SimpleNode<T>::setData(T data) {
    *(this -> dataPtr) = data;
}

template <class T>
T SimpleNode<T>::getData() {
    return *(this -> dataPtr);
}

#endif //AIRWAR_SIMPLENODE_H