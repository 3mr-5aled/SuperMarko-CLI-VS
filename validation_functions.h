#pragma once
#include <iostream>
#include <string>
#include "lib/struct.h"

using namespace std;

bool validateUsername(string name) {
    bool valid = false;
    // Check if username is empty or contains only spaces
    if (name.empty() || name.find_first_not_of(' ') == string::npos)
    {
        cout << RED << "Username cannot be empty!" << RESET << endl;
        valid = false;
    }
    else if (name.length() < 3 || name.length() > 20)
    {
        cout << RED << "Username must be between 3 and 20 characters." << RESET << endl;
        valid = false;
    }
    else if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._") != string::npos)
    {
        cout << RED << "Username can only contain letters, numbers, dots (.), and underscores (_)." << RESET << endl;
        valid = false;
    }
    else if (name.front() == '.' || name.front() == '_' || name.back() == '.' || name.back() == '_')
    {
        cout << RED << "Username cannot start or end with '.' or '_'." << RESET << endl;
        valid = false;
    }
    else if (name.find("..") != string::npos || name.find("__") != string::npos)
    {
        cout << RED << "Username cannot contain consecutive '.' or '_'." << RESET << endl;
        valid = false;
    }
    else
    {
        valid = true; // Username is valid
    }

    return valid;
}

bool validatePassword(string password) {
    // Check if password is empty
    if (password.empty())
    {
        cout << RED << "Password cannot be empty!" << RESET << endl;
        return false;
    }

    // Check if password contains spaces
    if (password.find(' ') != string::npos)
    {
        cout << RED << "Password cannot contain spaces!" << RESET << endl;
        return false;
    }

    // Check if password is at least 8 characters long
    if (password.size() < 8)
    {
        cout << RED << "Password must be at least 8 characters long!" << RESET << endl;
        return false;
    }

    // Check if password contains at least one uppercase letter
    if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos)
    {
        cout << RED << "Password must contain at least one uppercase letter!" << RESET << endl;
        return false;
    }

    // Check if password contains at least one lowercase letter
    if (password.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos)
    {
        cout << RED << "Password must contain at least one lowercase letter!" << RESET << endl;
        return false;
    }

    // Check if password contains at least one numeric digit
    if (password.find_first_of("0123456789") == string::npos)
    {
        cout << RED << "Password must contain at least one number!" << RESET << endl;
        return false;
    }

    // Check if password contains at least one special character
    if (password.find_first_of("!@#$%^&*()-_=+[]{}|;:'\",.<>?/") == string::npos)
    {
        cout << RED << "Password must contain at least one special character!" << RESET << endl;
        return false;
    }

	return true; // Password is valid
}


bool validatePhone(string phone) {
    // Check if phone number is empty or contains only spaces
    if (phone.empty() || phone.find(' ') != string::npos)
    {
        cout << RED << "Phone number cannot be empty!" << RESET << endl;
        return false;
    }

    // Check if phone number is exactly 11 digits and contains only numbers
    if (phone.length() != 11 || phone.find_first_not_of("0123456789") != string::npos)
    {
        cout << RED << "Phone number must be 11 digits long and contain only numbers." << RESET << endl;
        return false;
    }

    // Check if phone number starts with valid Egyptian prefixes
    if (phone.substr(0, 3) != "010" && phone.substr(0, 3) != "011" && phone.substr(0, 3) != "012" && phone.substr(0, 3) != "015")
    {
        cout << RED << "Invalid phone number prefix. Egyptian phone numbers must start with 010, 011, 012, or 015." << RESET << endl;
        return false;
    }

	return true; // Phone number is valid
}

bool validateLocation(string location) {
	bool valid = false;
    if (location.empty() || location.find_first_not_of(' ') == string::npos)
    {
        cout << RED << "Location cannot be empty!"
            << RESET << endl;
        valid = false;
    }
    else if (location.length() < 5)
    {
        cout << RED << "Location must be at least 5 characters long."
            << RESET << endl;
        valid = false;
    }
    else if (location.length() > 100)
    {
        cout << RED << "Location cannot exceed 100 characters."
            << RESET << endl;
        valid = false;
    }
    else if (location.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .-") != string::npos)
    {
        cout << RED << "Location contains invalid characters. Only letters, numbers, spaces, periods, and hyphens are allowed."
            << RESET << endl;
        valid = false;
    }
    else {
		valid = true;
    }

    return valid;
}