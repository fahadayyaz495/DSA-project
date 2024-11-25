#ifndef STACK_H
#define STACK_H

#include "node.h"

template <class type>
class stack {
    snode<type>* top;
    public:
    stack() {
        top=nullptr;
    }
    bool isempty() {
        return !(top);
    }
    ~stack() {
        while (!(isempty())) 
            delete pop();
    }
    type* peek() {
        return top->object;
    }
    void push(type* ptr)
    {
        snode<type>* mynode = new snode<type>(ptr);
        mynode->next=top;
        top=mynode;
    }
    type* pop()
    {
        if (isempty()) 
            return nullptr;
        else
        {
            type* obj=top->object;
            snode<type>* temp = top;
            top=top->next;
            delete temp;
            return obj;
        }
    }
};

#endif