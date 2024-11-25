#ifndef OBJECT_H
#define OBJECT_H

#include "node.h"

class customer {
    public:
    int id,age;
    string name,password,email;
    customer(int id=0,string name="",int age=0,string email="",string password="") {
        this->id=id;
        this->name=name;
        this->age=age;
        this->email=email;
        this->password=password;
    }
};

class menu {
    public:
    string product;
    int cost;
    menu(string product="",int cost=0) {
        this->product=product;
        this->cost=cost;
    }
};

class order {
    public:
    int id,bill;
    string orders;
    order(int id=0,int bill=0,string orders="") {
        this->id=id;
        this->bill=bill;
        this->orders=orders;
    }
};

class sale {
    public:
    order service;
    string type;
    sale(int id=0,int bill=0,string orders="",string type="") {
        service.id=id;
        service.bill=bill;
        service.orders=orders;
        this->type=type;
    }
};

class delivery {
    public:
    order service;
    string location;
    int distance;
    delivery(int id=0,int bill=0,string orders="",int distance=0,string location="") {
        service.id=id;
        service.bill=bill;
        service.orders=orders;
        this->distance=distance;
        this->location=location;
    }
};

class location {
    public:
    int index,distance;
    string from,to;
    location(int index,string from,string to,int distance) {
        this->index=index;
        this->from=from;
        this->to=to;
        this->distance=distance;
    }
};

#endif