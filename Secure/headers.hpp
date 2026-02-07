#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <strings.h>
#include <termios.h>
#include <signal.h>
#include <openssl/evp.h> // Modern OpenSSL API
#include <sys/random.h>  // For getrandom()
#include <iomanip>
#include <cstring>
#include <sstream>

extern struct termios global_oldt;
extern bool echo_disabled;

void handle_sigint(int sig);
std::string toHex(const unsigned char* data, size_t len);
std::string hashPassword(const char* password, const std::string& saltHex);
void secureGetInput(char* buffer, size_t size, bool hideInput);
void registerUser();
bool loginUser();

#endif // HEADERS_HPP