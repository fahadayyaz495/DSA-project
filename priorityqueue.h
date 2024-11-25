#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "node.h"

template <class type>
class priorityqueue {
    pqnode<type>* front;
    pqnode<type>* rear;
    public:
    priorityqueue() {
        front=rear=nullptr;
    }
    bool isempty() {
        return !(front);
    }
    ~priorityqueue() {
        while (!(isempty())) 
            delete dequeue();
    }
    type* peek() {
        return front->object;
    }
    void enqueue(type* ptr,int key) {
        pqnode<type>* mynode=new pqnode<type>(ptr,key);
        if (isempty()) 
            front=rear=mynode;
        else {
            if (front->priority<mynode->priority) {
                mynode->next=front;
                front=mynode;
            }
            else {
                pqnode<type>* prev=front;
                pqnode<type>* temp=front->next;
                while (temp) {
                    if (temp->priority<mynode->priority) {
                        mynode->next=temp;
                        prev->next=mynode;
                        return;
                    }
                    prev=temp;
                    temp=temp->next;
                }
                prev->next=mynode;
                rear=mynode;
            }
        }
    }
    type* dequeue() {
        if (isempty()) 
            return nullptr;
        else {
            type* obj=front->object;
            pqnode<type>* temp=front;
            front=front->next;
            if (!(front))
                rear=nullptr;
            delete temp;
            return obj;
        }
    }
};

#endif