#include <iostream>
#include <string>
#include "struct.h"
#include <conio.h>
#include "lib/change_exchange.h"
using namespace std;

// Display menu to edit user information
int displayMenu()
{
    string choice;
    int digitchoice;
    while (true)
    {
        cout << BOLD << UNDERLINE << CYAN << "What do you want to edit?" << RESET << endl;
        cout << BOLD << "1. " << RESET << "Name" << endl;
        cout << BOLD << "2. " << RESET << "Phone Number" << endl;
        cout << BOLD << "3. " << RESET << "Location" << endl;
        cout << BOLD << "4. " << RESET << "Password" << endl;
        cout << BOLD << "0. " << RED << "Cancel" << RESET << endl;
        cout << endl;
        cout << BOLD << YELLOW << "Enter your choice: " << RESET;
        cin >> choice;
		bool state = changestateExchange(choice, digitchoice);
        if (digitchoice < 0 || digitchoice > 4 || !state)
        {
            cout << RED << "Invalid choice. Please enter a number between 0 and 4.\n"
                << RESET;
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

    cin.ignore();

    while (!validName)
    {
        cout << BOLD << CYAN << "Enter the new name (Press Backspace to cancel): " << RESET;
        cin.clear();
        name = "";

        bool outfunc = returning(name,"editing");
        if (!outfunc)
        {
            return false;
        }

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
        else if (name == currentCustomer.Name)
        {
            cout << RED << "New username cannot be the same as current username.\n" << RESET;
        }
        else
        {
            // Check if username already exists in any customer record
            bool usernameExists = false;
            for (int i = 0; i < numOfCustomers; i++)
            {
                // Check against all existing users, except current user
                if (!customers[i].Name.empty() && customers[i].ID != currentCustomer.ID)
                {
                    if (customers[i].Name == name)
                    {
                        cout << RED << "Username already exists! Please choose another one.\n" << RESET;
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

    cin.ignore();

    while (!validPhone)
    {
        cout << BOLD << CYAN << "Enter the new phone number (Press Backspace to cancel):" << RESET;
        bool outfunc = returning(phone, "editing");
        if (!outfunc)
        {
            return false;
        }

        // Check if phone number is empty or contains spaces
        if (phone.empty() || phone.find(' ') != string::npos)
        {
            cout << RED << "Phone number cannot be empty or contain spaces!\n" << RESET;
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

        // Check if new phone is the same as current
        if (phone == currentCustomer.PhoneNumber)
        {
            cout << RED << "New phone number cannot be the same as current phone number.\n" << RESET;
            continue;
        }

        // If all validations pass, it's a valid phone number
        validPhone = true;
        currentCustomer.PhoneNumber = phone;
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

    cin.ignore();

    while (!validLocation)
    {
        cout << BOLD << CYAN << "Enter the new location (Press Backspace to cancel): " << RESET;
        bool outfunc = returning(location, "editing");
        if (!outfunc)
        {
            return false;
        }

        if (location.empty() || location.find_first_not_of(' ') == string::npos)
        {
            cout << RED << "Location cannot be empty!\n" << RESET;
        }
        else if (location.length() < 5)
        {
            cout << RED << "Location must be at least 5 characters long.\n" << RESET;
        }
        else if (location.length() > 100)
        {
            cout << RED << "Location cannot exceed 100 characters.\n" << RESET;
        }
        else if (location.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ,.-") != string::npos)
        {
            cout << RED << "Location contains invalid characters. Only letters, numbers, spaces, commas, periods, and hyphens are allowed.\n" << RESET;
        }
        else if (location == currentCustomer.Location)
        {
            cout << RED << "New location cannot be the same as current location.\n" << RESET;
        }
        else
        {
            validLocation = true;
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

    cin.ignore();

    while (!validPassword)
    {
        cout << BOLD << CYAN << "Enter the new password (Must has at least 8 characters , 1 UPPERCASE , 1 LOWERCASE , 1 SPEICAL CHARACTER): " << RESET;
        password = "";
        bool outfunc = returning(password, "editing",true);
        // Mask input
        if (!outfunc)
            return false;

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

        // Check if new password is the same as current
        if (password == currentCustomer.Password)
        {
            cout << RED << "New password cannot be the same as current password.\n" << RESET;
            continue;
        }

        // Confirm password
        string confirmPassword = "";
        cout << BOLD << CYAN << "Confirm your new password (Press Backspace to cancel): " << RESET;

        // Mask input for confirmation
        if (!returning(confirmPassword, "editing",true))
            return false;

        // Check if passwords match
        if (password != confirmPassword)
        {
            cout << RED << "Passwords do not match!\n" << RESET;
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
    }

    cout << endl;
}