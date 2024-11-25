#ifndef ADMIN_H
#define ADMIN_H

#include "filehandling.h"

void adminlogin() {

    cout << endl;
    cout << "------------SignIn------------\n";
    cout << endl;   

    email:
    string email;
    cout << "Email acceptable-form(xxx@gmail.com): ";       // email
    cin >> email;
    if (email.length()<=10 || email.substr(email.length()-10,10)!="@gmail.com") {
        cout << "\nInvalid Input...\n";         // invalid input
        goto email;
    }

    string password;
    cout << "Password: ";           // password
    cin >> password;

    if (email!="fahad@gmail.com" && password!="1010") {
        cout << "\nEmail or Password is incorrect...\n";
        cout << "Enter Again. Thank You...\n";          // checking email and password
        goto email;
    }

    cout << "\nHi, Fahad" << endl;
    cout << "\nLogin Successfully...\n";

}

void additem(singlylist<menu>& products) {
    
    string product;
    cout << "Item name: ";          // new item for menu
    cin >> product;
    
    cost:
    string str;
    cout << "Item cost: ";          // cost of new item
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto cost;
        }
    }
    
    int cost=stoi(str); 

    products.insert(new menu(product,cost));        // inserting in menu list

    // storing new item in file
    fstream file;
    file.open("menu.csv",ios::app);
    file << product << ",";
    file << cost << endl;
    file.close();

}

void removeitem(singlylist<menu>& products,int i) {

    option:
    string str;
    cout << "Item No.: ";           // item no. to remove
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto option;
        }
    }
    
    int option=stoi(str);
    if (option>=i) {
        cout << "\nInvalid Input...\n";         // invalid input
        goto option;
    }

    i=1;
    lnode<menu>* temp=products.gethead();
    // traverse through list upto item no. user has entered
    while (i<option) {
        temp=temp->next;
        i++;
    }
    
    products.remove(temp->object);          // removing item from list
    updatemenus(products.gethead());        // updating menu

}

void updateitem(singlylist<menu>& products,int i) {

    option:
    string str;
    cout << "Item No.: ";           // item no. to update
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto option;
        }
    }
    
    int option=stoi(str);
    if (option>=i) {
        cout << "\nInvalid Input...\n";         // invalid input
        goto option;
    }

    
    cost:
    cout << "Item cost: ";          // item cost
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto cost;
        }
    }
    
    int cost=stoi(str);

    i=1;
    lnode<menu>* temp=products.gethead();
    // traverse through list upto item no. user entered
    while (i<option) {
        temp=temp->next;
        i++;
    }

    temp->object->cost=cost;            // updating cost of that item
    updatemenus(products.gethead());        // updating menu in file

}

void updatemenu() {
    
    singlylist<menu> products;          // menu list
    loadmenu(products);         // loading menu from file

    cout << endl;
    cout << "-------------Menu-------------\n";
    cout << endl; 

    menu:
    lnode<menu>* temp=products.gethead();
    int i=1;
    // displaying menu thorugh list
    while (temp) {
        cout << i << ". ";
        cout << temp->object->product << " ( Rs. " << temp->object->cost << " )" << endl;
        temp=temp->next;
        i++;
    }
    cout << endl;

    option:
    char option;
    cout << "\nSelect Options:\n";          // options
    cout << "1. Add Item\n";
    cout << "2. Remove Item\n";
    cout << "3. Update Item\n";
    cin >> option;

    switch (option) {
        case '0':
            cout << "\nMenu Updated Successfully...\n";
            return;
        case '1':
            additem(products);          // add item
            break;
        case '2':
            removeitem(products,i);         // remove item
            break;
        case '3':
            updateitem(products,i);         // update item
            break;
        default:
            cout << "\nInvalid Input...\n";         // invalid input
            goto option;
            break;
    }

    cout << "\nTo Exit Press 0:\n\n";           // 0 to exit
    goto menu;

}

void swap(lnode<sale>* temp) {

    // swaping two nodes 
    sale* temp2=temp->object;
    temp->object=temp->next->object;
    temp->next->object=temp2;
}
void sort(lnode<sale>* temp) {

    // sorting list
    lnode<sale>* last=nullptr;          // pointing to last
    while(temp!=last) {
        lnode<sale>* temp2=temp;        // starting position
        while(temp2->next!=last) {
            if (temp2->object->service.id>temp2->next->object->service.id) {        // comparing ids of two nodes
                swap(temp2);        // swap if first is greater
            }
            temp2=temp2->next;
        }
        last=temp2;         // last pointing before last position
    }
}

void sales() {

    cout << endl;
    cout << "---------Sales-Record---------\n";
    cout << endl;

    stack<sale> records;            // sales stack
    loadsales(records);         // loading records from file

    singlylist<sale> recordslist;

    // displaying sales record recent order
    cout << "ID , Bill , Order , Type\n";
    int total=0;
    while (!(records.isempty())) {
        sale* record=records.pop();
        recordslist.insert(record);         // storing in list
        cout << record->service.id << " , "; 
        cout << record->service.bill << " , ";
        cout << record->service.orders << " , ";
        cout << record->type << endl;
        total+=record->service.bill;        // total calculation
    }

    // total sales amount
    cout << "\nTotal Sales Amount: " << total << endl;

    cout << "\nSorted View...\n";
    cout << endl;
    sort(recordslist.gethead());            // sorting list

    // displaying sales record in sorted order
    cout << "ID , Bill , Order , Type\n";
    lnode<sale>* temp=recordslist.gethead();
    while (temp) {
        cout << temp->object->service.id << " , "; 
        cout << temp->object->service.bill << " , ";
        cout << temp->object->service.orders << " , ";
        cout << temp->object->type << endl;
        temp=temp->next;
    }

}

void addcity(singlylist<location>& locations,int i) {
    
    city:
    string city;
    cout << "City name: ";          // city
    cin.ignore();
    getline(cin,city);
    lnode<location>* temp=locations.gethead();
    while (temp) {
        if (temp->object->from==city) {
            cout << "\nCity Already Exited...\n";       // checking city
            goto city;
        }
        temp=temp->next;
    }

    des:
    string str;
    cout << "City No. to whom it would connect\n";          // city no. to connect
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid  input
            goto des;
        }
    }
    int choice=stoi(str);

    if (choice>=i) {
        cout << "\nInvalid Input...\n";         // invalid input
        goto des;
    }
    int index=i;

    distance:
    cout << "Distance in km : ";            // distance 
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto distance;
        }
    }
    int distance=stoi(str);

    i=1;
    temp=locations.gethead();
    // traverse through list upto city no. user entered
    temp=temp->next;
    while (i<choice) {
        temp=temp->next;
        i++;
    }

    locations.insert(new location(index,city,temp->object->from,distance));         // inserting new location

    // storing new location to file
    fstream file;
    file.open("locations.csv",ios::app);
    file << index << ",";
    file << city << ",";
    file << temp->object->from << ",";
    file << distance << endl;
    file.close();

}

void removecity(singlylist<location>& locations,int i) {

    option:
    string str;
    cout << "City No.: ";           // city no. to remove
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto option;
        }
    }
    
    int option=stoi(str);
    if (option>=i) {
        cout << "\nInvalid Input...\n";         // invalid input
        goto option;
    }

    i=1;
    lnode<location>* temp=locations.gethead();
    // traverse through list upto city no. user entered
    temp=temp->next;
    while (i<option) {
        temp=temp->next;
        i++;
    }

    string city=temp->object->from;         // city

    temp=locations.gethead();
    // removing that city containing nodes
    temp=temp->next;
    while(temp) {
        if (temp->object->from==city || temp->object->to==city) 
            locations.remove(temp->object);
        temp=temp->next;
    }
    
    updatelocations(locations.gethead());           // updating locations

}

void updatelocation() {
    
    singlylist<location> locations;         // locations list
    loadlocation(locations);            // loading location from file

    cout << endl;
    cout << "-----------Location-----------\n";
    cout << endl; 

    locations:
    lnode<location>* temp=locations.gethead();
    temp=temp->next;
    int i=1;
    // displaying locations through list
    while (temp) {
        cout << i << ". ";
        cout << temp->object->from << " ---> " << temp->object->to;
        cout << " ( " << temp->object->distance << " km )" << endl;
        temp=temp->next;
        i++;
    }
    cout << endl;

    option:
    char option;
    cout << "\nSelect Options:\n";          // options
    cout << "1. Add City\n";
    cout << "2. Remove City\n";
    cin >> option;

    switch (option) {
        case '0':
            cout << "\nLocations Updated Successfully...\n";
            return;
        case '1':
            addcity(locations,i);       // 1 to add city
            break;
        case '2':
            removecity(locations,i);        // 2 to remove city
            break;
        default:
            cout << "\nInvalid Input...\n";     // invalid input
            goto option;
            break;
    }

    cout << "\nTo Exit Press 0:\n\n";       // 0 to exit
    goto locations;

}

bool customerrecord(int id) {

    // particular customer record
    fstream file;
    file.open("customers.csv",ios::in);
    string cell;
    bool found=0;
    string name,age,email;
    getline(file,cell,'\n');
    try {
        // reading customers from file
        while (!(file.eof())) {
            getline(file,cell,',');
            if (id==stoi(cell))
                found=1;            // checking id
            getline(file,cell,',');
            if (found) 
                name=cell;
            getline(file,cell,',');
            if (found) 
                age=cell;
            getline(file,cell,',');
            if (found) 
                email=cell;
            getline(file,cell,'\n');
            if (found) 
                break;
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();
    if (!(found)) {
        cout << "No Sales Record...\n";         // if not found
        return 0;
    }

    cout << endl;
    cout << "--------CustomerRecord--------\n";
    cout << endl;

    // customer info
    cout << "ID-> " << id << endl;
    cout << "Name-> " << name << endl;
    cout << "Age-> " << age << endl;
    cout << "Email-> " << email << endl;

    cout << "\nCustomer's sales record...\n";
    cout << "\nBill , Order , Type\n";
    
    stack<sale> records;            // sales stack
    loadsales(records);         // loading sales from file

    // displaying sales record of that customer
    while (!(records.isempty())) {
        sale* record=records.pop();
        if (record->service.id==id) {
            cout << record->service.bill << " , ";
            cout << record->service.orders << " , ";
            cout << record->type << endl;
        }
        delete record;
    }
    cout << endl;
    return 1;
    
}

void _admin_() {

    adminlogin();

    cout << endl;
    cout << "------------Option------------\n";
    cout << endl; 

    option:
    char option;
    cout << "\nSelect Function:\n";         // options
    cout << "1. Update Menu\n";
    cout << "2. Update Location\n";
    cout << "3. Sales Analysis\n";
    cout << "4. Customer Record Lookup\n";
    cin >> option;

    string str;
    int id;
    switch (option) {
        case '0':
            return;
        case '1':
            updatemenu();           // 1 to update menu
            cout << "\nTo Exit Press 0:\n\n";       // 0 to exit
            goto option;
            break;
        case '2':
            updatelocation();          // 2 to update locations
            cout << "\nTo Exit Press 0:\n\n";       // 0 to exit
            goto option;
            break;
        case '3':
            sales();            // 3 for sales record
            cout << "\nTo Exit Press 0:\n\n";       // 0 to exit
            goto option;
            break;
        case '4':
            id:
            cout << "ID: ";         // id
            cin >> str;
            for (char ch:str) {
                if (!(isdigit(ch))) {
                    cout << "\nInvalid Input...\n";         // invalid input
                    goto id;
                }
            }
            id=stoi(str);

            if (!(customerrecord(id))) {            // customer record
                cout << "\nID Not Found...\n";
            }
            cout << "\nTo Exit Press 0:\n\n";       // 0 to exit
            goto option;
            break;
        default:
            cout << "\nInvalid Input...\n";         // invalid input
            goto option;
            break;
    }
}

#endif