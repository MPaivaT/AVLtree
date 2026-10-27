#ifndef NODE_H
#define NODE_H


template <typename T> 
class Node {
    public:
    T element;
    int key;
    int fb;
    Node* left;
    Node* right;    
    Node<T>();
    ~Node<T>();
};

template<typename T>
Node<T>::Node(){
    left = right = nullptr;
    fb = 0;
}
template<typename T>
Node<T>::~Node(){}

#endif