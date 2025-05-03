#include <iostream>
#include "struct.h"
#include <conio.h>
#include "lib/change_exchange.h"
using namespace std;

int loginUser(CUSTOMER customers[], const int numerofcustomers,bool & back);
bool registerUser(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id);
void menu_logging_in(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id,int& flag,bool& back);

bool registerUser(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id)
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
        cout << RED << "No empty slot to register."
             << RESET<<endl;
        return false;
    }

    while (!validName)
    {
        cout << CYAN << "Enter your username (Press Backspace to cancel): " << RESET;
		bool outfunc = returning(name,"register");
        if (!outfunc)
        {
            return false;
        }

        // Check if username is empty or contains only spaces
        if (name.empty() || name.find_first_not_of(' ') == string::npos)
        {
            cout << RED << "Username cannot be empty!" << RESET<<endl;
        }
        else if (name.length() < 3 || name.length() > 20)
        {
            cout << RED << "Username must be between 3 and 20 characters." << RESET<<endl;
        }
        else if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._") != string::npos)
        {
            cout << RED << "Username can only contain letters, numbers, dots (.), and underscores (_)." << RESET<<endl;
        }
        else if (name.front() == '.' || name.front() == '_' || name.back() == '.' || name.back() == '_')
        {
            cout << RED << "Username cannot start or end with '.' or '_'." << RESET<<endl;
        }
        else if (name.find("..") != string::npos || name.find("__") != string::npos)
        {
            cout << RED << "Username cannot contain consecutive '.' or '_'." << RESET<<endl;
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
                    cout << RED << "Username already exists! Please choose another one."
                         << RESET<<endl;
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
        cout << CYAN << "Enter your Password (Must has at least 8 characters , 1 UPPERCASE , 1 LOWERCASE , 1 SPEICAL CHARACTER) "<<endl<<"Password: " << RESET;
        cin >> password;
        
		

        // Check if password is empty
        if (password.empty())
        {
            cout << RED << "Password cannot be empty!" << RESET<<endl;
            continue;
        }

        // Check if password contains spaces
        if (password.find(' ') != string::npos)
        {
            cout << RED << "Password cannot contain spaces!" << RESET<<endl;
            continue;
        }

        // Check if password is at least 8 characters long
        if (password.size() < 8)
        {
            cout << RED << "Password must be at least 8 characters long!" << RESET<<endl;
            continue;
        }

        // Check if password contains at least one uppercase letter
        if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos)
        {
            cout << RED << "Password must contain at least one uppercase letter!" << RESET<<endl;
            continue;
        }

        // Check if password contains at least one lowercase letter
        if (password.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos)
        {
            cout << RED << "Password must contain at least one lowercase letter!" << RESET<<endl;
            continue;
        }

        // Check if password contains at least one numeric digit
        if (password.find_first_of("0123456789") == string::npos)
        {
            cout << RED << "Password must contain at least one number!" << RESET<<endl;
            continue;
        }

        // Check if password contains at least one special character
        if (password.find_first_of("!@#$%^&*()-_=+[]{}|;:'\",.<>?/") == string::npos)
        {
            cout << RED << "Password must contain at least one special character!" << RESET<<endl;
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
            cout << RED << "Phone number cannot be empty!" << RESET<<endl;
            continue;
        }

        // Check if phone number is exactly 11 digits and contains only numbers
        if (phone.length() != 11 || phone.find_first_not_of("0123456789") != string::npos)
        {
            cout << RED << "Phone number must be 11 digits long and contain only numbers." << RESET<<endl;
            continue;
        }

        // Check if phone number starts with valid Egyptian prefixes
        if (phone.substr(0, 3) != "010" && phone.substr(0, 3) != "011" && phone.substr(0, 3) != "012" && phone.substr(0, 3) != "015")
        {
            cout << RED << "Invalid phone number prefix. Egyptian phone numbers must start with 010, 011, 012, or 015." << RESET<<endl;
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
            cout << RED << "Location cannot be empty!"
                 << RESET<<endl;
        }
        else if (location.length() < 5)
        {
            cout << RED << "Location must be at least 5 characters long."
                 << RESET<<endl;
        }
        else if (location.length() > 100)
        {
            cout << RED << "Location cannot exceed 100 characters."
                 << RESET<<endl;
        }
        else if (location.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .-") != string::npos)
        {
            cout << RED << "Location contains invalid characters. Only letters, numbers, spaces, periods, and hyphens are allowed."
                 << RESET<<endl;
        }
        else
        {
            validLocation = true;
            customers[index].Location = location;
        }
    }
    id = index + 1;
    customers[index].ID = index + 1;
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
    
    return true;
}

int loginUser(CUSTOMER customers[], const int numerofcustomers,bool &back)
{
    string username, password;
    int attempts = 3, index = 0;
    back = false;

    while (attempts > 0)
    {
        cout << endl;
        cout << CYAN << "Enter your username (Press Backspace to cancel): " << RESET;
        bool outfunc = returning(username,"login");
        if (!outfunc)
        { 
			back = true;
            return false;
        }
        cout << CYAN << "Enter your password: " << RESET;
        password = "";
        char ch;
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
                cout << YELLOW << "You have " << attempts << " attempt(s) left."
                << RESET << endl;
            else
            {
                cout << RED <<endl<< "No attempts left."
                    << RESET<<endl;
                return 0;
            }
        }
    }
    return 0;
}


void menu_logging_in(CUSTOMER customers[], const int numerofcustomers, fstream &myfile, int &id, int& flag, bool &back)
{

    string input;
    int choice;
    bool upd;
    while (true)
    {
        cout << YELLOW << "Do you want to register or login?" << RESET << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Credits" << endl;
        cout << "0. Exit The Program" << endl;
        cout << CYAN << "Enter your choice: " << RESET;

        cin >> input;

		bool state = changestateExchange(input, choice);
		if (!state || choice <0 || choice > 3)
		{
			cout << RED << "Invalid input. Please enter a number (0, 1, 2 or 3)."
				<< RESET<<endl;
			continue;
		}
        if (choice == 1)
        {
            upd=registerUser(customers, numerofcustomers, myfile, id);
            if (upd)
            {
                flag = 1;
                break;
            }
            flag = 0;
            continue;
        }
        else if (choice == 2)
        {
            id = loginUser(customers, numerofcustomers,back);
			if (back)
			{
                continue;
			}
            if (id == 0)
            {
                flag = 0;
                break;
            }
            flag = 1;
            break;
        }
        else if (choice == 3) {
            cout << BOLD << CYAN << "\n===============================" << RESET << endl;
            cout << BLINK << BOLD << "👨‍💻  Team Members" << RESET << endl;
            cout << BOLD << CYAN << "===============================\n" << RESET << endl;

            cout << YELLOW << "🏅 1. Amr Khaled Hassan Morcy" << RESET << endl;
            cout << YELLOW << "🏅 2. Omar Mohammed Abdelmoaty" << RESET << endl;
            cout << YELLOW << "🏅 3. Mahmoud Mohammed AbdelSalam" << RESET << endl;
            cout << YELLOW << "🏅 4. Mohammed Gamal Abbas" << RESET << endl;
            cout << YELLOW << "🏅 5. Mohanad Refaye Hussein" << RESET << endl;
            cout << YELLOW << "🏅 6. Essam Mohammed El-Shahat" << RESET << endl;

            cout << BOLD << CYAN << "===============================\n" << RESET << endl;

        }
        else if (choice == 0)
        {
            cout << GREEN << "EXITING PROGRAM ..." << RESET << endl;
            flag = false;
            break;
        }
        else
        {
            cout << RED << "Invalid choice. Please enter 0, 1, 2 or 3."
                 << RESET<<endl;
        }
    }

    return;
}
void log_out(int& id, bool& loggedIn) {
    cout << RED <<endl <<"Logging out..."
        << RESET << endl;
    cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════"<<endl;
    cout << endl;
    id = 0;
    loggedIn = false;
}