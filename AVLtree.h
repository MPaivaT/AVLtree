#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <utility>
#define tpt template<typename T>

tpt
class AVLtree {
    private:
    
    Node<T>* root;
    int Nel;
    
    // destroi a arvore recursivamente
    tpt
    static void AVLtree<T>::DestroyR(Node<T>* R){
        if(!R) return;
        AVLtree::DestroyR(R->left);
        AVLtree::DestroyR(R->right);
        delete R;
    }
    //auxiliares rotações etc
    tpt
    static Node<T>* AVLtree<T>::Min_N(Node<T>* N){
        if(!N->left) return N;
        AVLtree::Min_N(N->left);
    }
    tpt
    static void AVLtree<T>::RSD(Node<T>** r){
        Node<T>* a = *r;
        Node<T>* b = a ->left;
        *r = b;
        a->left = b->right;
        b->right = a;
        a->fb = b->fb = 0;
    }
    tpt
    static void AVLtree<T>::RSE(Node<T>** r){
        Node<T>* a = *r;
        Node<T>* b = a ->right;
        *r = b;
        a->right = b->left;
        b->left = a;
        a->fb = b->fb = 0;
    }
    tpt
    static void AVLtree<T>::RDD(Node<T>** r){
        Node<T>* a = *r;
        Node<T>* b = a->left;
        Node<T>* c = b->right;
        a->left = c->right;
        b->right = c->left;
        c->left = b;
        c->right = a;
        *r = c;
        if(c->fb==-1){
            b->fb = 0;
            a->fb = 1;
        }
        else{
            if(c->fb==1){
                b->fb = 1;
                a->fb = 0;
            }
            else{
                c->fb = b->fb = a->fb = 0;
            }
        }
        c->fb = 0;
    }
    tpt
    static void AVLtree<T>::RDE(Node<T>** r){
        Node<T>* a = *r;
        Node<T>* b = a->right;
        Node<T>* c = b->left;
        a->right = c->left;
        b->left = c->right;
        c->right = b;
        c->left = a;
        *r = c;
        if(c->fb==-1){
            b->fb = 1;
            a->fb = 0;
        }
        else{
            if(c->fb==1){
                b->fb = 0;
                a->fb = 1;
            }
            else{
                c->fb = b->fb = a->fb = 0;
            }
        }
        c->fb = 0;
    }
    tpt
    static bool AVLtree<T>::InsertR(Node<T>** R,int k,Node<T>* P){
        if(!*R){
            *R = P;
            return true;
        }
        if(k < (*R)->key){
            if(!AVLtree<T>::Insert(&((*R)->left),k,P)) return false;
            
            if((*R)->fb>=0){
                return --((*R)->fb);
            }
            
            if((*R)->left->fb == -1){
                AVLtree<T>::RSD(R);
                return false;
            }
            AVLtree<T>::RDD(R);
            return false;
        }
        if(!AVLtree<T>::Insert(&((*R)->right),k,P)) return false;
            
            if((*R)->fb<=0){
                return ++((*R)->fb);
            }
            
            if((*R)->right->fb == 1){
                AVLtree<T>::RSE(R);
                return false;
            }
            AVLtree<T>::RDE(R);
            return false;
    }
    tpt
    static Node<T>* AVLtree<T>::SearchR(Node<T>* R,int k){
        if(!R) return nullptr;
        if(k<r->key) return AVLtree<T>::SearchR(R->left,k);
        if(R->key == k) return R;
        return AVLtree<T>::SearchR(R->right,R,k);
    }
    
    tpt
    void AVLtree<T>::imprimir_InOrderR(Node<T>* R){
        if(!R) return;
        imprimir_InOrderR(R->left);
        cout << R->element << '\n';
        imprimir_InOrderR(R->right);
    }
    
    
    public:
    // contrutor
    tpt
    AVLtree<T>::AVLtree(){
        root = nullptr;
    }
    tpt
    bool AVLtree<T>::Insert(int k,T N){
        Node<T>* P = new Node<T>(k,N);
        AVLtree<T>::InsertR(root,k,P);
        return Search(k)==N;
    }
    tpt
    T AVLtree<T>::Search(int k){
        Node<T>* N = AVLtree<T>::SearchR(root,k);
        return N->element;
    }

    tpt
    void AVLtree<T>::imprimir_InOrder(){
        imprimir_InOrderR(root);
    }
    
    
    tpt
    void AVLtree<T>::Destroy(){ //função chama destuir recursivo
        DestroyR(root);
        root = nullptr;
    }
    // Destrutor chama Destroy arvore
    tpt
    AVLtree<T>::~AVLtree(){
        AVLtree<T>:DestroyR(root);
    }
};






#endif