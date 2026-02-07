#include "headers.hpp"

using namespace std;

struct termios global_oldt;
bool echo_disabled = false;

void handle_sigint(int sig) {
    if (echo_disabled) tcsetattr(STDIN_FILENO, TCSANOW, &global_oldt);
    _exit(sig); 
}

// Convert binary data to hex string for file storage
string toHex(const unsigned char* data, size_t len) {
    stringstream ss;
    ss << hex << setfill('0');
    for (size_t i = 0; i < len; ++i) ss << setw(2) << (int)data[i];
    return ss.str();
}

// SHA-256 Hashing using EVP API
string hashPassword(const char* password, const string& saltHex) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen = 0;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();

    EVP_DigestInit_ex(context, md, NULL);
    // Hash the salt first, then the password (concatenation)
    EVP_DigestUpdate(context, saltHex.c_str(), saltHex.length());
    EVP_DigestUpdate(context, password, strlen(password));
    EVP_DigestFinal_ex(context, hash, &hashLen);
    EVP_MD_CTX_free(context);

    return toHex(hash, hashLen);
}

void secureGetInput(char* buffer, size_t size, bool hideInput) {
    struct termios newt;
    signal(SIGINT, handle_sigint);
    if (hideInput) {
        tcgetattr(STDIN_FILENO, &global_oldt);
        newt = global_oldt;
        newt.c_lflag &= ~ECHO;
        echo_disabled = true;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    mlock(buffer, size);
    ssize_t bytesRead = read(STDIN_FILENO, buffer, size - 1);
    if (bytesRead > 0) {
        if (buffer[bytesRead - 1] == '\n') buffer[bytesRead - 1] = '\0';
        else buffer[bytesRead] = '\0';
    } else buffer[0] = '\0';

    if (hideInput) {
        tcsetattr(STDIN_FILENO, TCSANOW, &global_oldt);
        echo_disabled = false;
        cout << endl;
    }
}

void registerUser() {
    char username[64], password[64];
    cout << "--- Registration ---\nUsername: ";
    // cout.flush();   // Fix print issue
    secureGetInput(username, sizeof(username), false);

    // Simple existence check (Plaintext username is fine)
    ifstream checkFile("database");
    string line;
    while (getline(checkFile, line)) {
        if (line.substr(0, line.find(':')) == username) {
            cerr << "[!] User exists.\n";
            return;
        }
    }

    cout << "Password: ";
    // cout.flush();
    secureGetInput(password, sizeof(password), true);

    // Generate 16 bytes of random salt
    unsigned char salt[16];
    getrandom(salt, sizeof(salt), 0);
    string saltHex = toHex(salt, sizeof(salt));

    // Hash the password with the salt
    string hashedPw = hashPassword(password, saltHex);

    ofstream file("database", ios::app);
    if (file.is_open()) {
        file << username << ":" << saltHex << ":" << hashedPw << endl;
        cout << "[+] Registered with SHA-256 + Salt.\n";
    }

    explicit_bzero(password, sizeof(password));
    munlock(password, sizeof(password));
}

bool loginUser() {
    char username[64], password[64];
    cout << "--- Login ---\nUsername: ";
    // cout.flush();
    secureGetInput(username, sizeof(username), false);
    cout << "Password: ";
    // cout.flush();
    secureGetInput(password, sizeof(password), true);

    ifstream file("database");
    string line;
    bool auth = false;

    while (getline(file, line)) {
        size_t firstColon = line.find(':');
        size_t lastColon = line.rfind(':');
        
        if (firstColon != string::npos && lastColon != firstColon) {
            string u = line.substr(0, firstColon);
            string saltHex = line.substr(firstColon + 1, lastColon - firstColon - 1);
            string storedHash = line.substr(lastColon + 1);

            if (u == username) {
                // Hash the input password with the stored salt
                if (hashPassword(password, saltHex) == storedHash) {
                    auth = true;
                }
                break;
            }
        }
    }

    explicit_bzero(password, sizeof(password));
    munlock(password, sizeof(password));
    return auth;
}