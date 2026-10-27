#ifndef AVLTREE_H
#define AVLTREE_H

/*
    Implementation of AVL tree made of Murilo Paiva Tavares,
    student of Computer Science in Pontifícia Universidade Católica de Goiás
*/



#include "Node.h"
#include <utility>
#include <iostream>
using namespace std;

template<typename T>
class AVLtree {
    private:
    
    Node<T>* root;
    int Nel;
    
    static void DestroyR(Node<T>* R);

    //auxiliares rotações etc

    static Node<T>* Min_N(Node<T>* N);

    static void RSD(Node<T>** r);

    static void RSE(Node<T>** r);

    static void RDD(Node<T>** r);

    static void RDE(Node<T>** r);

    static bool InsertR(Node<T>** R,int k,Node<T>* P);

    static bool direx(Node<T>** R,int k);

    static bool popR(Node<T>** R,int k);

    static Node<T>* SearchR(Node<T>* R,int k);
    
    template<typename Func>
    static void InOrderR(Node<T>* R,Func act);
    
    template<typename Func>
    static void PreOrderR(Node<T>* R,Func act);

    template<typename Func>
    static void PosOrderR(Node<T>* R,Func act);
    
    public:

    AVLtree();

    bool Insert(int k,T N);

    bool pop(int k);

    T Search(int k);

    void print_Order(int ord);
    
    
    void Destroy();

    ~AVLtree();
};


// Implementação


template<typename T>
    void AVLtree<T>::DestroyR(Node<T>* R){
        if(!R) return;
        AVLtree::DestroyR(R->left);
        AVLtree::DestroyR(R->right);
        delete R;
    }
    //auxiliares rotações etc
    template<typename T>
    Node<T>* AVLtree<T>::Min_N(Node<T>* N){
        if(!N->left) return N;
        return AVLtree::Min_N(N->left);
    }

    template<typename T>
    void AVLtree<T>::RSD(Node<T>** r){
        Node<T>* a = *r;
        Node<T>* b = a ->left;
        *r = b;
        a->left = b->right;
        b->right = a;
        if(b->fb==-1){
            a->fb = b->fb = 0;
        }
        else{
            a->fb = -1;
            b->fb = 1;
        }
    }

    template<typename T>
    void AVLtree<T>::RSE(Node<T>** r){
        Node<T>* a = *r;
        Node<T>* b = a ->right;
        *r = b;
        a->right = b->left;
        b->left = a;
        if(b->fb==1){
            a->fb = b->fb = 0;
        }
        else{
            a->fb = 1;
            b->fb = -1;
        }
    }

    template<typename T>
    void AVLtree<T>::RDD(Node<T>** r){
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
                b->fb = -1;
                a->fb = 0;
            }
            else{
                c->fb = b->fb = a->fb = 0;
            }
        }
        c->fb = 0;
    }

    template<typename T>
    void AVLtree<T>::RDE(Node<T>** r){
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
                a->fb = -1;
            }
            else{
                b->fb = a->fb = 0;
            }
        }
        c->fb = 0;
    }

    template<typename T>
    bool AVLtree<T>::InsertR(Node<T>** R,int k,Node<T>* P){
        if(!*R){
            *R = P;
            return true;
        }
        if(k < (*R)->key){
            if(!AVLtree<T>::InsertR(&((*R)->left),k,P)) return false;
            
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
        if(!AVLtree<T>::InsertR(&((*R)->right),k,P)) return false;
            
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

    template<typename T>
    bool AVLtree<T>::direx(Node<T>** R,int k){
        if(!AVLtree<T>::popR(&((*R)->right),k)){return false;}
            //diminiu na direita
            if((*R)->fb>=0){
                (*R)->fb--;
                return !((*R)->fb);
            }
            //tem de rotacionar pra direita
            if((*R)->left->fb==-1){
                AVLtree<T>::RSD(R);
                return true;
            }
            if((*R)->left->fb==0){
                AVLtree<T>::RSD(R);
                return false;
            }
            //n é simples é dupla
            RDD(R);
            return true;
    }

    template<typename T>
    bool AVLtree<T>::popR(Node<T>** R,int k){
        if(!*R){
            return false;
        }
        if(k<(*R)->key){
            if(!AVLtree<T>::popR(&((*R)->left),k)){return false;}
            //diminiu na esquerda
            if((*R)->fb<1){
                (*R)->fb--;
                return !((*R)->fb);
            }
            //tem de rotacionar pra esquerda
            if((*R)->right->fb==1){
                AVLtree<T>::RSE(R);
                return true;
            }
            if((*R)->right->fb==0){
                AVLtree<T>::RSE(R);
                return false;
            }
            //n é simpes então é dupla
            RDE(R);
            return true;
        }
        if(k == (*R)->key){
            if(!(*R)->left){
                Node<T>* temp = *R;
                *R = temp->right;
                delete temp;
                return true;
            }
            //tem filho na esquerda
            if(!(*R)->right){
                Node<T>* temp = *R;
                *R = temp->left;
                delete temp;
                return true;
            }
            Node<T>* mini = AVLtree<T>::Min_N((*R)->right);
            swap(mini->key,(*R)->key);
            swap(mini->element,(*R)->element);
            return AVLtree<T>::direx(R,k);
        }
        return direx(R,k);

    }

    template<typename T>
    Node<T>* AVLtree<T>::SearchR(Node<T>* R,int k){
        if(!R) return nullptr;
        if(k<R->key) return AVLtree<T>::SearchR(R->left,k);
        if(R->key == k) return R;
        return AVLtree<T>::SearchR(R->right,k);
    }
    
    template<typename T>
    template<typename Func>
    void AVLtree<T>::InOrderR(Node<T>* R,Func act){
        if(!R) return;
        InOrderR(R->left,act);
//        cout << R->element << '\n';
        act(R->element);
        InOrderR(R->right,act);
    }

    template<typename T>
    template<typename Func>
    void AVLtree<T>::PosOrderR(Node<T>* R,Func act){
        if(!R) return;
        PosOrderR(R->left,act);
        PosOrderR(R->right,act);
        act(R->element);
    }

    template<typename T>
    template<typename Func>
    void AVLtree<T>::PreOrderR(Node<T>* R,Func act){
        if(!R) return;
        act(R->element);
        PreOrderR(R->left,act);
        PreOrderR(R->right,act);
    }
    
    //Publicas


    // contrutor
    template<typename T>
    AVLtree<T>::AVLtree(){
        root = nullptr;
    }
    
    template<typename T>
    bool AVLtree<T>::Insert(int k,T N){
        Node<T>* P = new Node<T>;
        P->element = N;
        P->key = k;
        AVLtree<T>::InsertR(&root,k,P);
        return Search(k)==N;
    }

    template<typename T>
    bool AVLtree<T>::pop(int k){
        AVLtree<T>::popR(&root,k);
        return !AVLtree<T>::Search(k);
    }

    template<typename T>
    T AVLtree<T>::Search(int k){
        Node<T>* N = AVLtree<T>::SearchR(root,k);
        if(!N) return 0;
        return N->element;
    }

    template<typename T>
    void AVLtree<T>::print_Order(int ord){
        auto f = [](T el){cout << el << '\n';};
        if(ord<0) return PreOrderR(root,f);
        if(ord>0) return PosOrderR(root,f);
        InOrderR(root,f);
    }
    
    
    template<typename T>
    void AVLtree<T>::Destroy(){ //função chama destuir recursivo
        DestroyR(root);
        root = nullptr;
    }
    // Destrutor chama Destroy arvore
    template<typename T>
    AVLtree<T>::~AVLtree(){
        AVLtree<T>::DestroyR(root);
    }



#endif