#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "object.h"
#include "singlylist.h"
#include "binarytree.h"
#include "priorityqueue.h"
#include "queue.h"
#include "stack.h"
#include "graph.h"

void loadcustomers(binarytree<customer>& customers) {
    fstream file;
    file.open("customers.csv",ios::in);
    string cell;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int id=stoi(cell);
            getline(file,cell,',');
            string name=cell;
            getline(file,cell,',');
            int age=stoi(cell);
            getline(file,cell,',');
            string email=cell;
            getline(file,cell,'\n');
            string password=cell;
            customers.insert(new customer(id,name,age,email,password));
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
}

void loadmenu(singlylist<menu>& products) {
    fstream file;
    file.open("menu.csv",ios::in);
    string cell;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            string product=cell;
            getline(file,cell,'\n');
            int cost=stoi(cell);
            products.insert(new menu(product,cost));
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
}

void loadlocation(singlylist<location>& locations) {
    fstream file;
    file.open("locations.csv",ios::in);
    string cell;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int index=stoi(cell);
            getline(file,cell,',');
            string from=cell;
            getline(file,cell,',');
            string to=cell;
            getline(file,cell,'\n');
            int distance=stoi(cell);
            locations.insert(new location(index,from,to,distance));
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
}

int loadlocations(singlylist<location>* locations) {
    fstream file;
    file.open("locations.csv",ios::in);
    string cell;
    getline(file,cell,'\n');
    int i=0;
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int index=stoi(cell);
            getline(file,cell,',');
            string from=cell;
            getline(file,cell,',');
            string to=cell;
            getline(file,cell,'\n');
            int distance=stoi(cell);
            locations->insert(new location(index,from,to,distance));
            i++;
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
    return i;
}

int getage(tnode<customer>* temp,int id) {
    if (!(temp)) 
        return 0;
    else {
        if (id<temp->object->id)
            return getage(temp->left,id);
        else if (id>temp->object->id)
            return getage(temp->right,id);
        else 
            return temp->object->age;
    }
}
int loadorders(priorityqueue<order>& services) {

    binarytree<customer> customers;
    loadcustomers(customers);

    fstream file;
    file.open("walkin.csv",ios::in);
    string cell;
    int i=0;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int id=stoi(cell);
            getline(file,cell,',');
            int bill=stoi(cell);
            getline(file,cell,'\n');
            string orders=cell;
            int age=getage(customers.getroot(),id);
            services.enqueue(new order(id,bill,orders),age);
            i++;
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
    return i;
}

int loadorders(queue<order>& services) {
    fstream file;
    file.open("dinein.csv",ios::in);
    string cell;
    int i=0;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int id=stoi(cell);
            getline(file,cell,',');
            int bill=stoi(cell);
            getline(file,cell,'\n');
            string orders=cell;
            services.enqueue(new order(id,bill,orders));
            i++;
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
    return i;
}

int loaddelorders(priorityqueue<delivery>& services) {

    fstream file;
    file.open("homedel.csv",ios::in);
    string cell;
    int i=0;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int id=stoi(cell);
            getline(file,cell,',');
            int bill=stoi(cell);
            getline(file,cell,',');
            string orders=cell;
            getline(file,cell,',');
            int distance=stoi(cell);
            getline(file,cell,'\n');
            string location=cell;
            services.enqueue(new delivery(id,bill,orders,distance,location),distance);
            i++;
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
    return i;
}

void loadsales(stack<sale>& records) {
    fstream file;
    file.open("sales.csv",ios::in);
    string cell;
    getline(file,cell,'\n');
    try {
        while (!(file.eof())) {
            getline(file,cell,',');
            int id=stoi(cell);
            getline(file,cell,',');
            int bill=stoi(cell);
            getline(file,cell,',');
            string orders=cell;
            getline(file,cell,'\n');
            string type=cell;
            records.push(new sale(id,bill,orders,type));
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
}

void storeorders(int n,priorityqueue<order>& services) {
    fstream file;
    file.open("sales.csv",ios::app);
    for (int i=0; i<n; i++) {
        order* service=services.dequeue();
        file << service->id << ",";
        file << service->bill << ",";    
        file << service->orders << ",";
        file << "walkin" << endl;
        delete service;
    }
    file.close();
}

void storeorders(int n,queue<order>& services) {
    fstream file;
    file.open("sales.csv",ios::app);
    for (int i=0; i<n; i++) {
        order* service=services.dequeue();
        file << service->id << ",";
        file << service->bill << ",";    
        file << service->orders << ",";
        file << "dinein" << endl;
        delete service;
    }
    file.close();
}

void storedelorders(int n,priorityqueue<delivery>& services) {
    fstream file;
    file.open("sales.csv",ios::app);
    for (int i=0; i<n; i++) {
        delivery* service=services.dequeue();
        file << service->service.id << ",";
        file << service->service.bill << ",";    
        file << service->service.orders << ",";
        file << "homedel" << endl;
        delete service;
    }
    file.close();
}

void updateorders(priorityqueue<order>& services) {
    fstream file;
    file.open("walkin.csv",ios::out);
    file << "ID,Bill,Order" << endl;
    while (!(services.isempty())) {
        order* service=services.dequeue();
        file << service->id << ",";
        file << service->bill << ",";    
        file << service->orders << endl;
        delete service;
    }
    file.close();
}

void updateorders(queue<order>& services) {
    fstream file;
    file.open("dinein.csv",ios::out);
    file << "ID,Bill,Order" << endl;
    while (!(services.isempty())) {
        order* service=services.dequeue();
        file << service->id << ",";
        file << service->bill << ",";    
        file << service->orders << endl;
        delete service;
    }
    file.close();
}

void updatedelorders(priorityqueue<delivery>& services) {
    fstream file;
    file.open("homedel.csv",ios::out);
    file << "ID,Bill,Order,Distance,Location" << endl;
    while (!(services.isempty())) {
        delivery* service=services.dequeue();
        file << service->service.id << ",";
        file << service->service.bill << ",";    
        file << service->service.orders << ",";
        file << service->distance << ",";
        file << service->location << endl;
        delete service;
    }
    file.close();
}

void updatemenus(lnode<menu>* temp) {
    fstream file;
    file.open("menu.csv",ios::out);
    file << "Item,Cost" << endl;
    while (temp) {
        file << temp->object->product << ",";
        file << temp->object->cost << endl;
        temp=temp->next;
    }
    file.close();
}

void updatelocations(lnode<location>* temp) {
    fstream file;
    file.open("locations.csv",ios::out);
    file << "Index,From,To,Distance" << endl;
    int i=0;
    while (temp) {
        file << i << ",";
        file << temp->object->from << ",";
        file << temp->object->to << ",";
        file << temp->object->distance << endl;
        temp=temp->next;
        i++;
    }
    file.close();
}

#endif