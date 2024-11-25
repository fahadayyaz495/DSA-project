#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "filehandling.h"

int getid(tnode<customer>* temp) {

    // getting new id (one increment by greatest id) from AVL tree of customers 
    if (!(temp)) 
        return 1;       // base case 
    if (!(temp->right)) 
        return temp->object->id+1;         // greater id lies on right side
    else 
        return getid(temp->right);         // recursive case

}

bool checklogin(tnode<customer>* temp,int id,string password) {

    // checking login wether id or password is correct or not
    if (!(temp)) 
        return 0;       // base case
    else {
        if (id<temp->object->id)
            return checklogin(temp->left,id,password);      // left recursive case if id is less
        else if (id>temp->object->id)
            return checklogin(temp->right,id,password);     // right recursive case if id is greater
        else {
            if (temp->object->password==password) {         // checking password
                cout << "\nHi, " << temp->object->name << endl;
                return 1;
            }
            else 
                return 0;
        }
    }
}

int login(tnode<customer>* temp) {

    cout << endl;
    cout << "------------SignIn------------\n";
    cout << endl;   

    id:
    string str;
    cout << "ID: ";         // id
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto id;
        }
    }
    int id=stoi(str);

    string password;
    cout << "Password: ";           // password
    cin >> password;
    
    if (!(checklogin(temp,id,password))) {
        cout << "\nID or Password is incorrect...\n";       // invalid id or password
        cout << "Enter Again. Thank You...\n";
        goto id;
    }

    cout << "\nLogin Successfully...\n";
    return id;

}

void signup(binarytree<customer>& customers) {

    cout << endl;
    cout << "------------SignUp------------\n";
    cout << endl;

    string name;
    cout << "Name: ";           // name
    cin.ignore();
    getline(cin,name);

    age:
    string str;
    cout << "Age: ";        // age
    cin >> str;
    if (str.length()>=4) {
        cout << "\nInvalid Input...\n";         // invalid input
        goto age;
    }
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto age;
        }
    }
    int age=stoi(str);

    email:
    string email;
    cout << "Email acceptable-form(xxx@gmail.com): ";           // email
    cin >> email;
    if (email.length()<=10 || email.substr(email.length()-10,10)!="@gmail.com") {
        cout << "\nInvalid Input...\n";         //  invalid input
        goto email;
    }

    string password;
    cout << "Password: ";           // password
    cin >> password;

    int id=getid(customers.getroot());
    cout << "\nYour ID is " << id << endl;          // getting id 
    cout << "Remember this...\n";

    cout << "\nRegister Successfully...\n";

    customers.insert(new customer(id,name,age,email,password));         // updating customters tree

    // storing new customer in file
    fstream file;
    file.open("customers.csv",ios::app);
    file << id << ",";
    file << name << ",";
    file << age << ",";
    file << email << ",";
    file << password << endl;
    file.close();
}

order* takeorder(int id) {

    int bill=0;
    string orders="";
    
    singlylist<menu> products;          // menu list
    loadmenu(products);         // loading menu from file

    cout << endl;
    cout << "-------------Menu-------------\n";
    cout << endl; 

    menu:
    lnode<menu>* temp=products.gethead();
    int i=1;
    // displaying menu through list
    while (temp) {
        cout << i << ". ";
        cout << temp->object->product << " ( Rs. " << temp->object->cost << " )" << endl;
        temp=temp->next;
        i++;
    }
    cout << endl;
    
    option:
    string str;
    cout << "Choice: ";         // choice
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
    if (option==0) {
        if (bill==0) {
            cout << "\nInvalid Input...\n";         // invalid input 
            goto option;
        }
        cout << "\nOrder Sent Successfully...\n";
        return new order(id,bill,orders);           // new order sent if choice is 0
    }

    temp=products.gethead();
    i=1;
    // traverse through list upto item no. user has entered
    while (i<option) {
        temp=temp->next;
        i++;
    }

    amount:
    cout << "\nHow many do you want? ";         // quantity
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto amount;
        }
    }
    int amount=stoi(str);

    bill+=(temp->object->cost*amount);          // bill calculation
    orders+=temp->object->product;
    orders+=("("+to_string(amount)+").");       // order concatenation

    cout << "\nTo Exit Press 0:\n\n";       // 0 to exit
    goto menu;

}

string takelocation(int& distance) {


    singlylist<location>* locations=new singlylist<location>();         // locations list
    int total=loadlocations(locations);         // loading locations from file

    // graph for each location dynamically
    graph<singlylist<location>>* map=new graph<singlylist<location>>(total,locations);

    lnode<location>* temp=locations->gethead();
    // finding source and destination from list to insert in graph
    while (temp) {
        int source=temp->object->index;         // source
        lnode<location>* check=locations->gethead();
        int destination;
        while (check) {
            if (temp->object->to==check->object->from) {            // finding index of destination
                destination=check->object->index;           // destination
                break;
            }
            check=check->next;
        }

        // inserting in graph
        map->insert(source,destination,temp->object->distance);
        temp=temp->next;
    }

    cout << endl;
    cout << "-----------Location-----------\n";
    cout << endl;

    locations:
    temp=locations->gethead();
    temp=temp->next;
    int i=1;
    // displaying locations through list
    while (temp) {
        cout << i << ". ";
        cout << temp->object->from << endl;
        temp=temp->next;
        i++;
    }
    cout << endl;

    option:
    string str;
    cout << "Choice: ";         // choice
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

    temp=locations->gethead();
    temp=temp->next;
    i=1;
    // traverse through list upto location no. user has entered
    while (i<option) {
        temp=temp->next;
        i++;
    }

    // shortest path distance
    distance=map->shortest(locations->gethead()->object->index,temp->object->distance);
    string city=temp->object->from;
    delete map;

    return city;

}

void _customer_() {

    binarytree<customer> customers;         // customers tree
    loadcustomers(customers);           // loading customers from file

    account:
    char account;
    cout << "\nDo you have login ID (y/n)?";        // have account or not 
    cin >> account;

    int id;
    switch (account) {
        case 'y':
            id=login(customers.getroot());          // login if account exist
            break;
        case 'n':
            signup(customers);          // signup for new account
            id=login(customers.getroot());          // login
            break;
        default:
            cout << "\nInvalid Input...\n";         // invalid input
            goto account;
            break;
    }

    cout << endl;
    cout << "------------Method------------\n";
    cout << endl; 

    option:
    char option;
    cout << "\nSelect Your Order Method:\n";            // method of order placement
    cout << "1. Walk-In\n";
    cout << "2. Dine-In\n";
    cout << "3. Home-Delivery\n";
    cin >> option;

    string orderfile;
    switch (option) {
        case '1':
            orderfile="walkin.csv";         // 1 for walk-in
            break;
        case '2':
            orderfile="dinein.csv";         // 2 for dine-in
            break;
        case '3':
            orderfile="homedel.csv";        // 3 for home delivery
            break;
        default:
            cout << "\nInvalid Input...\n";         // invalid input
            goto option;
            break;
    }

    if (option=='3') {
        int distance=0;
        string city=takelocation(distance);         // if 3 is entered ask location

        order* service=takeorder(id);       // taking order

        // storing new order in file
        fstream file;
        file.open(orderfile,ios::app);
        file << service->id << ",";
        file << (service->bill)+(distance*30) << ",";
        file << service->orders << ",";
        file << distance << ",";
        file << city << endl;
        file.close();

        delete service;
    }
    else {

        order* service=takeorder(id);       // taking order

        // storing new order in file
        fstream file;
        file.open(orderfile,ios::app);
        file << service->id << ",";
        file << service->bill << ",";
        file << service->orders << endl;
        file.close();

        delete service;
    }

}

#endif