#include "headers.hpp"

using namespace std;

int main() {
    std::cout << std::unitbuf; // Disable buffering for immediate output to fix output and replace cout.flush() calls
    char choice[2];
    cout << "1. Register\n2. Login\n> ";
    if (read(STDIN_FILENO, choice, 1) <= 0) return 1;
    tcflush(STDIN_FILENO, TCIFLUSH);

    if (choice[0] == '1') registerUser();
    else if (choice[0] == '2') {
        if (loginUser()) cout << "Welcome.\n";
        else cout << "Access Denied.\n";
    }
    return 0;
}