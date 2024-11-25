#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include "node.h"

template <class type>
class singlylist {
    lnode<type>* head;
    public:
    singlylist() {
        head=nullptr;
    }
    bool isempty() {
        return !(head);
    }
    ~singlylist() {
        while (!(isempty())) 
            remove(head->object);
    }
    lnode<type>* gethead() {
        return head;
    }
    void insert(type* ptr)
    {
        lnode<type>* mynode=new lnode<type>(ptr);
        if (isempty())
            head=mynode;
        else
        {
            lnode<type>* temp=head;
            while (temp->next)
                temp=temp->next;
            temp->next=mynode;
        }
    }
    void remove(type* ptr) {
        if (!(isempty())) {
            if (head->object==ptr) {
                lnode<type>* temp=head;
                head=head->next;
                delete temp->object;
                delete temp;
            }
            else {
                lnode<type>* prev=head;
                lnode<type>* temp=head->next;
                while (temp) {
                    if (temp->object==ptr) {
                        prev->next=temp->next;
                        delete temp->object;
                        delete temp; 
                        return;
                    }
                    prev=temp;
                    temp=temp->next;
                }
            }
        }
    }
};

#endif