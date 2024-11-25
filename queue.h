#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

template <class type>
class queue {
    qnode<type>* front;
    qnode<type>* rear;
    public:
    queue() {
        front=rear=nullptr;
    }
    bool isempty() {
        return !(front);
    }
    ~queue() {
        while (!(isempty())) 
            delete dequeue();
    }
    type* peek() {
        return front->object;
    }
    void enqueue(type* ptr) {
        qnode<type>* mynode=new qnode<type>(ptr);
        if (isempty()) 
            front=rear=mynode;
        else {
            rear->next=mynode;
            rear=mynode;
        }
    }
    type* dequeue() {
        if (isempty()) 
            return nullptr;
        else {
            type* obj=front->object;
            qnode<type>* temp=front;
            front=front->next;
            if (!(front))
                rear=nullptr;
            delete temp;
            return obj;
        }
    }
};

#endif