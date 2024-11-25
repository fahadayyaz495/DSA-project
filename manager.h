#ifndef MANAGER_H
#define MANAGER_H

#include "filehandling.h"

string managerlogin() {

    cout << endl;
    cout << "------------SignIn------------\n";
    cout << endl;   

    email:
    string email;
    cout << "Email acceptable-form(xxx@gmail.com): ";           //  email
    cin >> email;
    if (email.length()<=10 || email.substr(email.length()-10,10)!="@gmail.com") {
        cout << "\nInvalid Input...\n";         // invalid input
        goto email; 
    }

    string password;
    cout << "Password: ";           // password
    cin >> password;

    string name,type;

    fstream file;
    file.open("manager.csv",ios::in);
    string cell;
    bool found=0;

    getline(file,cell,'\n');
    try {
        // reading from file to check email
        while (!(file.eof())) {
            getline(file,cell,',');
            name=cell;
            getline(file,cell,',');
            if (cell==email) 
                found=1;
            getline(file,cell,',');
            if (found) {
                if (cell!=password) {
                    cout << "\nEmail or Password is incorrect...\n";
                    cout << "Enter Again. Thank You...\n";          // checking email and password
                    file.close();
                    goto email;
                }
            }
            getline(file,cell,'\n');
            if (found) {
                type=cell;
                break;
            }
        }
    }
    catch (invalid_argument const& ex) {
        ex.what();
    }
    file.close();

    if (!(found)) {
        cout << "\nEmail or Password is incorrect...\n";
        cout << "Enter Again. Thank You...\n";         // checking email and password
        goto email;
    }

    cout << "\nHi, " << name << endl;
    cout << "\nLogin Successfully...\n";
    return type;

}

int askamount(int records) {
        
    cout << "\nThere are " << records << " orders present\n";       // records amount
    
    records:
    string str;
    cout << "\nHow many do you want to place? ";           // asking number of orders
    cin >> str;
    for (char ch:str) {
        if (!(isdigit(ch))) {
            cout << "\nInvalid Input...\n";         // invalid input
            goto records;
        }
    }
    int choice=stoi(str);
    if (choice>records) {
        cout << "\nInvalid Input...\n";         // invalid input
        goto records;
    }
    
    return choice;
}

void _manager_() {

    string type=managerlogin();         // login for manager
    
    int records;
    if (type=="walkin") {
        
        priorityqueue<order> services;          // priority queue for walk-in orders
        records=loadorders(services);           // loading waik-in orders

        int choice=askamount(records);          // manager's choice
        storeorders(choice,services);           // storing completed orders to sales record
        updateorders(services);         // updating walk-in orders file
        
    }
    else if (type=="dinein") {
        queue<order> services;          // queue for dine-in orders
        records=loadorders(services);           // loading dine-in orders
    
        int choice=askamount(records);          // manager's choice
        storeorders(choice,services);        // storing completed orders to sales record
        updateorders(services);         // updating dine-in orders file        
     
    }
    else {
        cout << type << endl;
        priorityqueue<delivery> services;          // priority queue for home-delivery orders based on shorter distance
        records=loaddelorders(services);          // loading home-delivery orders

        int choice=askamount(records);          // manager's choice
        storedelorders(choice,services);        // storing completed orders to sales record
        updatedelorders(services);         // updating dine-in orders file
    }
    cout << "\nOrder Placed Successfully...\n";

}

#endif