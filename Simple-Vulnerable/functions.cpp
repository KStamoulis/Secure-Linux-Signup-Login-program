#include "headers.hpp"

// // Function to toggle terminal echo
// void setEcho(bool enable) {
//     struct termios tty;
//     tcgetattr(STDIN_FILENO, &tty);
//     if (!enable) {
//         tty.c_lflag &= ~ECHO; // Disable echo
//     } else {
//         tty.c_lflag |= ECHO;  // Enable echo
//     }
//     (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
// }

// string getHiddenInput() {
//     string input;
//     setEcho(false);
//     cin >> input;
//     setEcho(true);
//     cout << endl; // Manual newline since Enter wasn't echoed
//     return input;
// }

bool usernameExists(const string& username) {
    ifstream file("database.txt");
    string line;
    while (getline(file, line)) {
        if (line.substr(0, line.find(':')) == username) return true;
    }
    return false;
}

void registerUser() {
    string username, password;
    cout << "Registration\nUsername: ";
    cin >> username;

    if (usernameExists(username)) {
        cerr << "Error: User already exists. Terminating.\n";
        return;
    }

    cout << "Password: ";
    cin >> password;

    ofstream file("database.txt", ios::app);
    if (file.is_open()) {
        file << username << ":" << password << endl;
        cout << "Account created.\n";
    }
}

bool loginUser() {
    string username, password, line;
    cout << "Login\nUsername: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("database.txt");
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (line.substr(0, pos) == username && line.substr(pos + 1) == password) {
            return true;
        }
    }
    return false;
}
