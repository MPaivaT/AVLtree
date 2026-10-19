#ifndef NODE_H
#define NODE_H


template <typename T> 
class Node {
    private:
    T element;
    int key;
    int fb;
    Node* left;
    Node* right;
    public:
    template<typename T>
    Node<T>(){
        left = right = nullptr;
        fb = 0;
    }
    template<typenameT>
    Node<T>(int k,T el){
        element = el;
        key = k;
        left = right = nullptr;
        fb = 0;
    }
    template<typename T>
    ~Node<T>(){}
};



#endif