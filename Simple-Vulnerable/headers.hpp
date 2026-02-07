#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

bool usernameExists(const string& username);
void registerUser();
bool loginUser();