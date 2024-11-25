#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "node.h"
#include "object.h"

int max(int a, int b) { 
    return (a > b)? a : b; 
} 
template <class type>
int height(tnode<type>* temp) {
    if (!(temp))
        return 0;
    else 
        return temp->height;
}

template <class type>
class binarytree {
    tnode<type>* root;
    public:
    binarytree() {
        root=nullptr;
    }
    bool isempty() {
        return !(root);
    }
    tnode<type>* getroot() {
        return root;
    }
    ~binarytree() {
        while (isempty()) 
            remove(root->object);
    }

    tnode<type>* rightrotate(tnode<type>* y) { 

        tnode<type>* x=y->left; 
        tnode<type>* temp=x->right; 
    
        x->right=y; 
        y->left=temp; 
    
        x->height=max(height(x->left),height(x->right))+1; 
        y->height=max(height(y->left),height(y->right))+1; 
    
        return x; 
    } 

    tnode<type>* leftrotate(tnode<type>* y) { 

        tnode<type>* x=y->right; 
        tnode<type>* temp=x->left; 
    
        x->left=y; 
        y->right=temp; 
    
        x->height=max(height(x->left),height(x->right))+1; 
        y->height=max(height(y->left),height(y->right))+1; 
    
        return x; 
    } 

    int getbalance(tnode<type>* temp) { 
        if (!(temp)) 
            return 0; 
        return height(temp->left)-height(temp->right); 
    } 

    tnode<type>* insert(type* ptr,tnode<type>* temp,int key) {
        if (!(temp))
            return new tnode<type>(ptr,key);
        if (ptr->id<temp->object->id) 
            temp->left=insert(ptr,temp->left,key);
        else if (ptr->id>temp->object->id)
            temp->right=insert(ptr,temp->right,key);
        else
            return temp;
        temp->height=max(height(temp->left),height(temp->right))+1; 
        int balance=getbalance(temp);
        if (balance>1 && key<temp->left->key)
            return rightrotate(temp);
        if (balance<-1 && key>temp->right->key)
            return leftrotate(temp);
        if (balance>1 && key>temp->left->key) {
            temp->left=leftrotate(temp->left);
            return rightrotate(temp);
        }
        if (balance<-1 && key<temp->right->key) {
            temp->right=rightrotate(temp->right);
            return leftrotate(temp);
        }
        return temp;
    } 
    void insert(customer* ptr) {
        root=insert(ptr,root,ptr->id);
    }

    tnode<type>* min(tnode<type>* temp) {
        if (!(temp->left)) 
            return temp;
        else 
            return min(temp->left);
    }

    tnode<type>* remove(type* ptr,tnode<type>* temp) {
        if (!(temp)) 
            return nullptr;
        if (ptr->id<temp->object->id) 
            temp->left=remove(ptr,temp->left);
        else if (ptr->id>temp->object->id)
            temp->right=remove(ptr,temp->right);
        else {
            if (!(temp->left)) {
                tnode<type>* child=temp->right;
                delete temp->object;
                delete temp;
                return child;
            }
            else if (!(temp->right)) {
                tnode<type>* child=temp->left;
                delete temp->object;
                delete temp;
                return child;     
            }
            else {
                tnode<type>* child=min(temp->right);
                type* swaping=temp->object;
                temp->object=child->object;
                child->object=swaping;
                temp->right=remove(child->object,temp->right);
            }
        }
        if (temp)
            return temp;
        temp->height=max(height(temp->left),height(temp->right))+1; 
        int balance=getbalance(temp);
        if (balance>1 && getbalance(temp->left)>=0)
            return rightrotate(temp);
        if (balance<-1 && getbalance(temp->right)<=0)
            return leftrotate(temp);
        if (balance>1 && getbalance(temp->left)<0) {
            temp->left=leftrotate(temp->left);
            return rightrotate(temp);
        }
        if (balance<-1 && getbalance(temp->right)>0) {
            temp->right=rightrotate(temp->right);
            return leftrotate(temp);
        }
        return temp;
    }
    void remove(type* ptr) {
        root=remove(ptr,root);
    }
};

#endif