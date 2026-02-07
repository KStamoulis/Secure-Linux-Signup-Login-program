#include "headers.hpp"

int main() {
    int choice;
    cout << "1. Register\n2. Login\n> ";
    if (!(cin >> choice)) return 1;

    if (choice == 1) registerUser();
    else if (choice == 2) {
        if (loginUser()) cout << "Success: Logged in.\n";
        else cout << "Failure: Invalid credentials.\n";
    }
    return 0;
}