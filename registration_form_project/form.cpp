#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x) * 1000)
#endif

using namespace std;

class Login {
private:
    string loginID, password;

public:
    Login() : loginID(), password() {}

    void setID(const string& id) {
        loginID = id;
    }

    void setPass(const string& pass) {
        password = pass;
    }

    string getID() const {
        return loginID;
    }

    string getPass() const {
        return password;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void registration(Login& login) {
    clearScreen();
    string id, pass;
    cout << "\tEnter Login ID: ";
    cin >> id;
    login.setID(id);

    while (true) {
        cout << "\tEnter Password (at least 8 characters): ";
        cin >> pass;

        if (pass.length() >= 8) {
            login.setPass(pass);
            break;
        } else {
            cout << "\tPassword must be at least 8 characters long. Please try again." << endl;
        }
    }

    ofstream outfile("login.txt", ios::app); // Updated path for macOS compatibility
    if (!outfile) {
        cout << "\tError: File cannot be opened!" << endl;
    } else {
        outfile << login.getID() << " : " << login.getPass() << endl;
        cout << "User registered successfully!" << endl;
    }
    outfile.close();
    Sleep(3000);
}

void login() {
    clearScreen();
    string id, pass;

    cout << "\tEnter Login ID: ";
    cin >> id;
    cout << "\tEnter Password: ";
    cin >> pass;

    ifstream infile("login.txt"); // Updated path for macOS compatibility
    if (!infile) {
        cout << "\tError: File cannot be opened!" << endl;
    } else {
        string line;
        bool found = false;
        while (getline(infile, line)) {
            stringstream ss(line);
            string userID, userPASS;
            char delimiter;

            ss >> userID >> delimiter >> userPASS;

            if (id == userID && pass == userPASS) {
                found = true;
                cout << "\tPlease Wait";
                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    Sleep(800);
                }
                clearScreen();
                cout << "\tWelcome to this page!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "\tError: Incorrect Login ID or Password!" << endl;
        }
    }
    infile.close();
    Sleep(3000);
}

int main() {
    Login log;
    bool exist = false;
    int val;

    while (!exist) {
        clearScreen();
        cout << "\tWelcome to Registration & Login Form" << endl;
        cout << "\t************ MENU ************" << endl;
        cout << "\t1. Register" << endl;
        cout << "\t2. Login" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            registration(log);
        } else if (val == 2) {
            login();
        } else if (val == 3) {
            clearScreen();
            exist = true;
            cout << "\tGoodbye and Good Luck!" << endl;
            Sleep(3000);
        } else {
            cout << "\tInvalid Choice! Please try again." << endl;
            Sleep(2000);
        }
    }

    return 0;
}
