#include <iostream>
#include <string>
#include "struct.h"
#include <conio.h>
#include "lib/change_exchange.h"
#include "validation_functions.h"

using namespace std;

// Display menu to edit user information
int displayMenu()
{
    string choice;
    int digitchoice;
    while (true)
    {
        cout << BOLD << UNDERLINE << CYAN << "🔧 What do you want to edit?" << RESET << endl;
        cout << BOLD << "1. 📝 " << RESET << "Name" << endl;
        cout << BOLD << "2. 📞 " << RESET << "Phone Number" << endl;
        cout << BOLD << "3. 📍 " << RESET << "Location" << endl;
        cout << BOLD << "4. 🔑 " << RESET << "Password" << endl;
        cout << BOLD << "0. " << RED << "Cancel" << RESET << endl;
        cout << endl;
        cout << BOLD << YELLOW << "Enter your choice: " << RESET;
        cin >> choice;
        cin.ignore();
        bool state = changestateExchange(choice, digitchoice);
        if (digitchoice < 0 || digitchoice > 4 || !state)
        {
            cout << RED << "Invalid choice. Please enter a number between 0 and 4."
                << RESET << endl;
            continue;
        }
        break;
    }
    return digitchoice;
}

// Edit name with matching registration validation
bool editName(CUSTOMER& currentCustomer, CUSTOMER customers[], int numOfCustomers)
{
    string name;
    bool validName = false;

    cout << BOLD << BLUE << "Current Name: " << RESET << currentCustomer.Name << endl;
    cout << endl;



    while (!validName)
    {
        cout << BOLD << CYAN << "Enter the new name (Press Backspace to cancel): " << RESET;
        cin.clear();
        name = "";

        bool outfunc = returning(name, "editing");
        if (!outfunc)
        {
            return false;
        }

        validName = validateUsername(name, currentCustomer.Name);

        if (validName) {
            // Check if username already exists in any customer record
            bool usernameExists = false;
            for (int i = 0; i < numOfCustomers; i++)
            {
                // Check against all existing users, except current user
                if (!customers[i].Name.empty() && customers[i].ID != currentCustomer.ID)
                {
                    if (customers[i].Name == name)
                    {
                        cout << RED << "Username already exists! Please choose another one." << RESET << endl;
                        usernameExists = true;
                        break;
                    }
                }
            }

            if (!usernameExists)
            {
                validName = true;
                currentCustomer.Name = name;
            }
        }
    }


    return true;
}

// Edit phone number with matching registration validation
bool editPhoneNumber(CUSTOMER& currentCustomer)
{
    string phone;
    bool validPhone = false;

    cout << BOLD << BLUE << "Current Phone Number: " << RESET << currentCustomer.PhoneNumber << endl;
    cout << endl;



    while (!validPhone)
    {
        cout << BOLD << CYAN << "Enter the new phone number (Press Backspace to cancel):" << RESET;
        bool outfunc = returning(phone, "editing");
        if (!outfunc)
        {
            return false;
        }

        validPhone = validatePhone(phone, currentCustomer.PhoneNumber);
        if (validPhone) {
            currentCustomer.PhoneNumber = phone;
        }
    }

    return true;
}

// Edit location with matching registration validation
bool editLocation(CUSTOMER& currentCustomer)
{
    string location;
    bool validLocation = false;

    cout << BOLD << BLUE << "Current Location: " << RESET << currentCustomer.Location << endl;
    cout << endl;


    while (!validLocation)
    {
        cout << BOLD << CYAN << "Enter the new location (Press Backspace to cancel): " << RESET;
        bool outfunc = returning(location, "editing");
        if (!outfunc)
        {
            return false;
        }
        validLocation = validateLocation(location, currentCustomer.Location);
        if (validLocation) {
            currentCustomer.Location = location;
        }
    }

    return true;
}

// Edit password with matching registration validation
bool editPassword(CUSTOMER& currentCustomer)
{
    string password;
    bool validPassword = false;


    cout << BOLD << CYAN << "Enter the new password (Must has at least 8 characters , 1 UPPERCASE , 1 LOWERCASE , 1 SPECIAL CHARACTER): " << RESET << endl;

    while (!validPassword)
    {
        cout << CYAN << "New Password: " << RESET;
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

        validPassword = validatePassword(password);
        if (!validPassword) {
            continue;
        }

        // Confirm password
        string confirmPassword = "";
        cout << YELLOW << BOLD << "Confirm your new password: " << RESET;
        ch;
        while ((ch = _getch()) != '\r') // Enter key
        {
            if (ch == '\b' && !confirmPassword.empty())
            {
                confirmPassword.pop_back();
                cout << "\b \b";
            }
            else if (ch != '\b')
            {
                confirmPassword += ch;
                cout << '*';
            }
        }
        // Mask input for confirmation


        // Check if passwords match
        if (password != confirmPassword)
        {
            cout << RED << "\nPasswords do not match!" << RESET << endl;
            continue;
        }

        // If all validations pass
        validPassword = true;
        currentCustomer.Password = password;
    }

    return true;
}

// Display updated information
void displayInformation(const CUSTOMER& currentCustomer, int state = 1)
{
    if (state == 1)
    {
        cout << BOLD << YELLOW << UNDERLINE << "Your Information:" << RESET << endl;
        cout << BOLD << "-------------------" << RESET << endl;
        cout << GREEN << "Name: " << RESET << currentCustomer.Name << endl;
        cout << GREEN << "Phone Number: " << RESET << currentCustomer.PhoneNumber << endl;
        cout << GREEN << "Location: " << RESET << currentCustomer.Location << endl;
        cout << GREEN << "Password: " << RESET << "*********" << endl;  // Hide password for security
        cout << BOLD << "-------------------" << RESET << endl;
    }
    else if (state == 2)
    {
        cout << endl;
        cout << GREEN << BOLD << "Success: " << RESET << "The information has been updated successfully!" << endl;
        cout << endl;
        cout << BOLD << YELLOW << UNDERLINE << "The Updated Information:" << RESET << endl;
        cout << BOLD << "--------------------------" << RESET << endl;
        cout << GREEN << "Name: " << RESET << currentCustomer.Name << endl;
        cout << GREEN << "Phone Number: " << RESET << currentCustomer.PhoneNumber << endl;
        cout << GREEN << "Location: " << RESET << currentCustomer.Location << endl;
        cout << GREEN << "Password: " << RESET << "*********" << endl;  // Hide password for security
        cout << BOLD << "--------------------------" << RESET << endl;
    }
    cout << endl;
}

// Main function to edit user information
void editUserInformation(CUSTOMER customers[], int id, int numOfCustomers)
{
    bool updated = false;
    bool continueEditing = true;
    int index = -1;

    for (int i = 0; i < numOfCustomers; i++)
    {
        if (customers[i].ID == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << RED << "Customer with ID " << id << " not found." << RESET << endl;
        return;
    }

    while (continueEditing)
    {
        displayInformation(customers[index], 1);
        int choice = displayMenu();

        cout << endl;

        switch (choice)
        {
        case 1:
            updated = editName(customers[index], customers, numOfCustomers);
            break;
        case 2:
            updated = editPhoneNumber(customers[index]);
            break;
        case 3:
            updated = editLocation(customers[index]);
            break;
        case 4:
            updated = editPassword(customers[index]);
            break;
        case 0:
            cout << YELLOW << BOLD << "No changes have been made." << RESET << endl;
            continueEditing = false;
            break;
        default:
            cout << RED << BOLD << "Error: " << RESET << "Invalid choice." << endl;
            break;
        }

        if (updated)
        {
            displayInformation(customers[index], 2);
            string editMore;
            do
            {
                cout << BOLD << CYAN << "Do you want to edit another data? (y/n): " << RESET;
                cin >> editMore;
                cin.ignore();
                if (editMore == "n" || editMore == "N")
                {
                    continueEditing = false;
                }
                else if (editMore == "y" || editMore == "Y")
                {
                    continueEditing = true;
                }
                else
                {
                    cout << RED << BOLD << "Error: " << RESET << "Invalid input. Please enter y or n." << endl;
                }
            } while (editMore != "y" && editMore != "Y" && editMore != "n" && editMore != "N");
		}
		else
		{
			cout << RED << BOLD << "Error: " << RESET << "No changes have been made." << endl;
    }

    cout << endl;
}
