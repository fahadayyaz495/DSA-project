#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class type>
class tnode {
    public:
    type* object;
    tnode<type>* left;
    tnode<type>* right;
    int height,key;
    tnode(type* ptr,int id) {
        object=ptr;
        left=right=nullptr; 
        key=id;
        height=1;       
    }
};

template <class type>
class qnode {
    public:
    type* object;
    qnode<type>* next;
    qnode(type* ptr) {
        object=ptr;
        next=nullptr;        
    }
};

template <class type>
class snode {
    public:
    type* object;
    snode<type>* next;
    snode(type* ptr) {
        object=ptr;
        next=nullptr;        
    }
};

template <class type>
class pqnode {
    public:
    type* object;
    int priority;
    pqnode<type>* next;
    pqnode(type* ptr,int n=0) {
        object=ptr;
        next=nullptr;        
        priority=n;
    }
};

template <class type>
class lnode {
    public:
    type* object;
    lnode<type>* next;
    lnode(type* ptr) {
        object=ptr;
        next=nullptr;        
    }
};

#endif  