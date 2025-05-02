#include <iostream>
#include "struct.h"
#include <conio.h>
using namespace std;

int loginUser(CUSTOMER customers[], const int numerofcustomers);
void registerUser(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id);
int menu_logging_in(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id);

void registerUser(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id)
{
    bool found = false, validPassword = false, validName = false, validPhone = false, validLocation = false;
    int index = 0;
    string name, password, phone, location;
    for (int i = 0; i < numerofcustomers; i++)
    {
        if (!customers[i].ID)
        {
            index = i;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << RED << "No empty slot to register.\n"
             << RESET;
        return;
    }

    customers[index].ID = index + 1;

    cin.ignore();

    while (!validName)
    {
        cout << CYAN << "Enter your username: " << RESET;
        cin.clear();

        getline(cin, name);

        // Check if username is empty or contains only spaces
        if (name.empty() || name.find_first_not_of(' ') == string::npos)
        {
            cout << RED << "Username cannot be empty!\n" << RESET;
        }
        else if (name.length() < 3 || name.length() > 20)
        {
            cout << RED << "Username must be between 3 and 20 characters.\n" << RESET;
        }
        else if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._") != string::npos)
        {
            cout << RED << "Username can only contain letters, numbers, dots (.), and underscores (_).\n" << RESET;
        }
        else if (name.front() == '.' || name.front() == '_' || name.back() == '.' || name.back() == '_')
        {
            cout << RED << "Username cannot start or end with '.' or '_'.\n" << RESET;
        }
        else if (name.find("..") != string::npos || name.find("__") != string::npos)
        {
            cout << RED << "Username cannot contain consecutive '.' or '_'.\n" << RESET;
        }


        // Check if username already exists in any customer record
        bool usernameExists = false;
        for (int i = 0; i < numerofcustomers; i++)
        {
            // Check against all existing users, regardless of their ID
            if (!customers[i].Name.empty() && customers[i].ID != 0)
            {
                if (customers[i].Name == name)
                {
                    cout << RED << "Username already exists! Please choose another one.\n"
                         << RESET;
                    usernameExists = true;
                    break;
                }
            }
        }

        if (!usernameExists)
        {
            validName = true;
            customers[index].Name = name;
        }
    }
    while (!validPassword)
    {
        cout << CYAN << "Enter your Password (Must has at least 8 characters , 1 UPPERCASE , 1 LOWERCASE , 1 SPEICAL CHARACTER) \nPassword: " << RESET;
        cin.clear();
        getline(cin, password);

        // Check if password is empty
        if (password.empty())
        {
            cout << RED << "Password cannot be empty!\n" << RESET;
            continue;
        }

        // Check if password contains spaces
        if (password.find(' ') != string::npos)
        {
            cout << RED << "Password cannot contain spaces!\n" << RESET;
            continue;
        }

        // Check if password is at least 8 characters long
        if (password.size() < 8)
        {
            cout << RED << "Password must be at least 8 characters long!\n" << RESET;
            continue;
        }

        // Check if password contains at least one uppercase letter
        if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos)
        {
            cout << RED << "Password must contain at least one uppercase letter!\n" << RESET;
            continue;
        }

        // Check if password contains at least one lowercase letter
        if (password.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos)
        {
            cout << RED << "Password must contain at least one lowercase letter!\n" << RESET;
            continue;
        }

        // Check if password contains at least one numeric digit
        if (password.find_first_of("0123456789") == string::npos)
        {
            cout << RED << "Password must contain at least one number!\n" << RESET;
            continue;
        }

        // Check if password contains at least one special character
        if (password.find_first_of("!@#$%^&*()-_=+[]{}|;:'\",.<>?/") == string::npos)
        {
            cout << RED << "Password must contain at least one special character!\n" << RESET;
            continue;
        }

        // If all validations pass
        validPassword = true;
        customers[index].Password = password;
    }


    while (!validPhone)
    {
        cout << CYAN << "Enter your phone number: " << RESET;
        cin.clear();
        cin >> phone;

        // Check if phone number is empty or contains only spaces
        if (phone.empty() || phone.find(' ') != string::npos)
        {
            cout << RED << "Phone number cannot be empty!\n" << RESET;
            continue;
        }

        // Check if phone number is exactly 11 digits and contains only numbers
        if (phone.length() != 11 || phone.find_first_not_of("0123456789") != string::npos)
        {
            cout << RED << "Phone number must be 11 digits long and contain only numbers.\n" << RESET;
            continue;
        }

        // Check if phone number starts with valid Egyptian prefixes
        if (phone.substr(0, 3) != "010" && phone.substr(0, 3) != "011" && phone.substr(0, 3) != "012" && phone.substr(0, 3) != "015")
        {
            cout << RED << "Invalid phone number prefix. Egyptian phone numbers must start with 010, 011, 012, or 015.\n" << RESET;
            continue;
        }

        // If all validations pass, it's a valid phone number
        validPhone = true;
        customers[index].PhoneNumber = phone;
    }

    cin.ignore();
    while (!validLocation)
    {
        cout << CYAN << "Enter your location: " << RESET;
        getline(cin, location);
        if (location.empty() || location.find_first_not_of(' ') == string::npos)
        {
            cout << RED << "Location cannot be empty!\n"
                 << RESET;
        }
        else if (location.length() < 5)
        {
            cout << RED << "Location must be at least 5 characters long.\n"
                 << RESET;
        }
        else if (location.length() > 100)
        {
            cout << RED << "Location cannot exceed 100 characters.\n"
                 << RESET;
        }
        else if (location.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ,.-") != string::npos)
        {
            cout << RED << "Location contains invalid characters. Only letters, numbers, spaces, commas, periods, and hyphens are allowed.\n"
                 << RESET;
        }
        else
        {
            validLocation = true;
            customers[index].Location = location;
        }
    }
    id = index + 1;
    cout << endl;
    cout << GREEN << "Registered: User created successfully" << RESET << endl;

    // Move to end to append
    myfile.clear();
    myfile.seekp(0, ios::end);
    myfile << customers[index].ID << '\n'
           << customers[index].Name << '\n'
           << customers[index].PhoneNumber << '\n'
           << customers[index].Location << '\n'
           << customers[index].Password << '\n';

    return;
}

int menu_logging_in(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id)
{
    int flag = 1;
    string input;
    int choice;

    while (true)
    {
        cout << YELLOW << "Do you want to register or login?" << RESET << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit The Program" << endl;
        cout << CYAN << "Enter your choice: " << RESET;

        cin >> input;

        // Check if the input is a number
        if (input.length() == 1 && isdigit(input[0]))
        {
            choice = input[0] - '0'; // convert char to int
        }
        else
        {
            cout << RED << "Invalid input. Please enter a number (0, 1, or 2).\n"
                 << RESET;
            continue;
        }

        if (choice == 1)
        {
            registerUser(customers, numerofcustomers, myfile, id);
            flag = 1;
            break;
        }
        else if (choice == 2)
        {
            id = loginUser(customers, numerofcustomers);
            if (id == 0)
            {
                cout << RED << "LOGIN FAILED!....." << RESET << endl;
                flag = 0;
                break;
            }
            flag = 1;
            break;
        }
        else if (choice == 0)
        {
            cout << GREEN << "EXITING PROGRAM ..." << RESET << endl;
            flag = 0;
            break;
        }
        else
        {
            cout << RED << "Invalid choice. Please enter 0, 1, or 2.\n"
                 << RESET;
        }
    }

    return flag;
}

int loginUser(CUSTOMER customers[], const int numerofcustomers)
{
    string username, password;
    int attempts = 3, index = 0;

    cin.ignore();
    while (attempts > 0)
    {
        cout << endl;
        cout << CYAN << "Enter your username: " << RESET;
        getline(cin, username);
        cout << CYAN << "Enter your password: " << RESET;
        password = "";
        char ch;

        // Mask input
        while ((ch = _getch()) != '\r') // Enter key
        {
            if (ch == '\b' && !password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
            else if (ch != '\b')
            {
                password += ch;
                cout << '*';
            }
        }
        cout << endl;
        cout << endl;
        bool found = false;
        for (int i = 0; i < numerofcustomers; i++)
        {
            if (!customers[i].Name.empty())
            {
                if (username == customers[i].Name && password == customers[i].Password)
                {
                    cout << GREEN << "Login: Authentication successful" << RESET << endl;
                    index = i;
                    found = true;
                    break;
                }
            }
        }

        if (found)
            return customers[index].ID;
        else
        {
            attempts--;
            cout << RED << "The username or password is incorrect. " << RESET;
            if (attempts > 0)
                cout << YELLOW << "You have " << attempts << " attempt(s) left.\n"
                     << RESET;
            else
            {
                cout << RED << "\nNo attempts left.\n"
                     << RESET;
                return 0;
            }
        }
    }
    return 0;
}
