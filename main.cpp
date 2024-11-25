#include "admin.h"
#include "manager.h"
#include "customer.h"

int main() {

    start:

    cout << endl;
    cout << "------------------------------\n";
    cout << "----------Pizza Shop----------\n";
    cout << "------------------------------\n";
    cout << endl;

    option:
    char option;
    cout << "\nSelect Your Category:\n";          // category
    cout << "1. Admin\n";
    cout << "2. Manager\n";
    cout << "3. Customer\n";
    cin >> option;

    switch (option) {
        case '0':
            return 0;       // 0 to exit
            break;
        case '1':
            _admin_();      // 1 to admin proceed
            break;
        case '2':
            _manager_();        // 2 to manager proceed
            break;
        case '3':
            _customer_();       // 3 to customer proceed
            break;
        default:
            cout << "\nInvalid Input...\n";        // invalid input
            goto option;
            break;
    }

    cout << "\nTo Exit Press 0:\n\n";
    goto option;

    return 0;
}