#include <iostream>
#include <fstream>
using namespace std;

void registerUser() {
    string username, password;
    cout << "\n=== User Registration
    ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream checkFile("users.txt");
    string existingUsername,     existingPassword;
    while (checkFile >> existingUsername >> existingPassword) {
        if (existingUsername == username) {
            cout << "Username already exists. Try a different one.\n";
            return;
        }
    }
    checkFile.close();

    ofstream outFile("users.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registration successful.\n";
}

void loginUser() {
    string username, password;
    cout << "\n=== User Login ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream inFile("users.txt");
    string storedUser, storedPass;
    bool found = false;
    while (inFile >> storedUser >> storedPass) {
        if (storedUser == username && storedPass == password) {
            found = true;
            break;
        }
    }
    inFile.close();

    if (found) {
        cout << "Login successful. Welcome, " << username << "!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n=== Login & Registration System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loginUser();
        } else if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}