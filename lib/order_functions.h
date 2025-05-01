#include "struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

bool addProducts(ORDER order[numOfCustomers], PRODUCT product[numOfCategories][numOfProducts], int &id, int CategoryCase, bool &returnToCategoryMenu)
{
    int number;
    string productInput;
    string answerofproduct;
    string amount;
    int amounts = 1;
    order[id - 1].CustomerID = id;
    int i = order[id - 1].productcount;

    if (i >= 10)
    {
        cout << RED << "Maximum limit of 10 products reached. Cannot add more products.\n"
             << RESET;
        return false;
    }

    do
    {
        if (i >= 10)
        {
            cout << RED << "Maximum limit of 10 products reached. Cannot add more products.\n"
                 << RESET;
            return false;
        }

        cout << YELLOW << "Please choose a product by entering a number between 1 and 10.\n"
             << RESET;
        cout << YELLOW << "Enter 0 to return to categories.\n"
             << RESET;
        cin >> productInput;

        if ((productInput.length() == 1 && isdigit(productInput[0])))
        {
            number = productInput[0] - '0';
        }
        else if (productInput == "10")
        {
            number = 10;
        }
        else
        {
            cout << RED << "Invalid input. Please enter a valid number.\n"
                 << RESET;
            answerofproduct = "y";
            continue;
        }

        if (number == 0)
        {
            cout << BLUE << "Returning to category menu...\n"
                 << RESET;
            returnToCategoryMenu = true;
            break;
        }

        if (!(number >= 1 && number <= 10))
        {
            cout << RED << "There is no choice like this.\n"
                 << RESET;
            answerofproduct = "y";
            continue;
        }

        // Store the product name for better user experience
        string productName = product[CategoryCase - 1][number - 1].Name;

        cout << YELLOW << "How many amount of " << CYAN << productName << YELLOW << " do you want? (enter 0 to cancel)\n"
             << RESET;
        cin >> amount;
        if ((amount.length() == 1 && isdigit(amount[0])))
        {
            amounts = amount[0] - '0';
        }
        else if (amount == "10")
        {
            amounts = 10;
        }
        else
        {
            // Check if the input is a valid number
            bool isValid = true;
            for (char c : amount)
            {
                if (!isdigit(c))
                {
                    isValid = false;
                    break;
                }
            }

            if (isValid)
            {
                amounts = stoi(amount);
                if (amounts > 10)
                {
                    cout << ORANGE << "Please head to Supplier\n"
                         << RESET;
                    answerofproduct = "y";
                    continue;
                }
            }
            else
            {
                cout << RED << "Invalid input. Please enter a valid number.\n"
                     << RESET;
                answerofproduct = "y";
                continue;
            }
        }
        // Cancel add if amount is zero
        if (amounts == 0)
        {
            cout << RED << "Cancelled adding product.\n"
                 << RESET;
            answerofproduct = "y";
            continue;
        }
        // Check if product already exists in order
        bool productExists = false;
        int existingIndex = -1;
        for (int j = 0; j < order[id - 1].productcount; j++)
        {
            if (order[id - 1].Products[j].Name == product[CategoryCase - 1][number - 1].Name)
            {
                productExists = true;
                existingIndex = j;
                break;
            }
        }

        if (productExists)
        {
            // Cancel if amount is zero for existing products
            if (amounts == 0)
            {
                cout << RED << "Canceled updating product.\n"
                     << RESET;
                answerofproduct = "y";
                continue;
            }

            if (amounts < 1 || amounts > 10)
            {
                cout << RED << "Invalid quantity. Please enter a number between 1 and 10.\n"
                     << RESET;
                answerofproduct = "y";
                continue;
            }
            if (order[id - 1].Amount[existingIndex] + amounts > 10)
            {
                cout << ORANGE << "Maximum amount for each customer is 10. You currently have "
                     << order[id - 1].Amount[existingIndex] << ".\n"
                     << RESET;
                answerofproduct = "y";
                continue;
            }

            // Update existing product quantity and price
            order[id - 1].TotalPrice -= order[id - 1].Products[existingIndex].Price;
            order[id - 1].Amount[existingIndex] += amounts;
            order[id - 1].Products[existingIndex].Price = order[id - 1].Amount[existingIndex] * product[CategoryCase - 1][number - 1].Price;
            order[id - 1].TotalPrice += order[id - 1].Products[existingIndex].Price;
            cout << "Updated quantity of " << order[id - 1].Products[existingIndex].Name << " : " << GREEN << order[id - 1].Amount[existingIndex] << RESET << "\n ";
        }
        else
        {
            // Add new product
            order[id - 1].Amount[i] = amounts;
            order[id - 1].Products[i] = product[CategoryCase - 1][number - 1];
            order[id - 1].Products[i].BasePrice = product[CategoryCase - 1][number - 1].Price;
            order[id - 1].Products[i].Price = (product[CategoryCase - 1][number - 1].Price) * (order[id - 1].Amount[i]);
            order[id - 1].TotalPrice += order[id - 1].Products[i].Price;
            order[id - 1].productcount++;
            cout << GREEN << "Added: " << order[id - 1].Products[i].Name << " x" << amounts << RESET << endl;
            i++;
        }

        cout << GREEN << "Do you want to choose another product from current category? (y/n)\n"
             << RESET;
        cin >> answerofproduct;
    } while (answerofproduct == "y" || answerofproduct == "Y");

    return true;
}

void ReviewOrder(ORDER order[numOfCustomers], int &id)
{
    if (order[id - 1].productcount == 0)
    {
        cout << RED << "You have no items in your order to review.\n"
             << RESET;
        return;
    }

    cout << "\n";
    cout << "|                                ORDER CHEQUE                                 |\n";
    cout << "\n";
    cout << "|  No.  |     Product Name     |  Quantity  | Unit Price |   Price   |\n";
    cout << "-------------------------------------------------------------------------------\n";

    for (int i = 0; i < order[id - 1].productcount; i++)
    {
        cout << "|  " << setw(4) << i + 1 << " | ";
        cout << setw(20) << order[id - 1].Products[i].Name << " | ";
        cout << setw(10) << order[id - 1].Amount[i] << " | ";
        cout << setw(10) << fixed << setprecision(2) << order[id - 1].Products[i].BasePrice << " | ";
        cout << setw(8) << fixed << setprecision(2) << order[id - 1].Products[i].Price << " |\n";
    }
    cout << "-------------------------------------------------------------------------------\n";
    cout << "TOTAL: " << fixed << setprecision(2) << order[id - 1].TotalPrice << " EGP\n";
}

void ModifyOrder(ORDER order[numOfCustomers], int &id)
{
    int index = id - 1;

    if (order[index].productcount == 0)
    {
        cout << RED << "You have no items in your order to modify.\n"
             << RESET;
        return;
    }

    while (true)
    {
        cout << endl;
        if (order[index].productcount == 0)
        {
            cout << RED << "You have no items in your order to modify.\n"
                 << RESET;
            return;
        }
        else
        {
            cout << TEAL << "Your current order : \n"
                 << RESET;

            for (int i = 0; i < order[index].productcount; i++)
            {
                cout << i + 1 << ". " << order[index].Products[i].Name;
                cout << " | Quantity: " << order[index].Amount[i];
                cout << " | Price : " << order[index].Products[i].Price << " EGP\n";
            }
        }

        cout << YELLOW << "Choose an item number to modify (0 to return)\n"
             << RESET;
        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        if (choice < 1 || choice > order[index].productcount)
        {
            cout << RED << "Invalid choice. Try again\n"
                 << RESET;
            continue;
        }
        cout << "You have selected : " << order[index].Products[choice - 1].Name;
        cout << " | Quantity: " << order[index].Amount[choice - 1];
        cout << " | Price : " << order[index].Products[choice - 1].Price << " EGP\n";

        int ItemIndex = choice - 1;
        cout << CYAN << "1. Change quantity\n"
             << RESET;
        cout << CYAN << "2. Remove Item\n"
             << RESET;
        cout << CYAN << "0. Cancel\n"
             << RESET;
        cout << "Enter Your option : ";
        int option;
        cin >> option;

        if (option == 1)
        {
            int newQuantity;
            cout << "Enter your new quantity : ";
            cin >> newQuantity;
            if (newQuantity < 1)
            {
                cout << RED << "Invalid quantity.\n"
                     << RESET;
                continue;
            }
            if (newQuantity == order[index].Amount[ItemIndex])
            {
                cout << RED << "Error : you entered the same quantity\n";
                cout << RED << "you must change the quantity  \n"
                     << RESET;
                continue;
            }
            if (newQuantity > 10)
            {
                cout << ORANGE << "PLease head to Supplier\n"
                     << RESET;
                continue;
            }
            order[index].TotalPrice -= order[index].Products[ItemIndex].Price;
            order[index].Amount[ItemIndex] = newQuantity;
            order[index].Products[ItemIndex].Price = newQuantity * order[index].Products[ItemIndex].BasePrice;
            order[index].TotalPrice += order[index].Products[ItemIndex].Price;

            cout << GREEN << "Updated: " << order[index].Products[ItemIndex].Name << " x" << newQuantity << RESET << endl;
        }

        else if (option == 2)
        {
            string removedItem = order[index].Products[ItemIndex].Name;
            order[index].TotalPrice -= order[index].Products[ItemIndex].Price;
            for (int i = ItemIndex; i < order[index].productcount; i++)
            {
                order[index].Products[i] = order[index].Products[i + 1];
                order[index].Amount[i] = order[index].Amount[i + 1];
            }

            order[index].productcount--;
            cout << GREEN << "\nRemoved: " << removedItem << RESET << endl;
        }

        else if (option == 0)
        {
            continue;
        }
        else
        {
            cout << RED << "Invalid option.\n"
                 << RESET;
        }
    }
    PRODUCT finalorder[10];
    int finalcount = order[index].productcount;

    for (int i = 0; i < finalcount; i++)
    {
        finalorder[i] = order[index].Products[i];
    }

    if (order[index].productcount != 0 )
    {

        cout << TEAL << "Final ordered items : \n"
             << RESET;
        for (int i = 0; i < finalcount; i++)
        {
            cout << i + 1 << ". " << finalorder[i].Name;
            cout << " | Quantity : " << order[index].productcount;
            cout << " | Price : " << finalorder[i].Price;
            cout << " EGP\n";
        }
    }
}

void DisplayOrderWithVAT(ORDER order[numOfCustomers], int &id)
{
    // Store original price before VAT
    double originalPrice = order[id - 1].TotalPrice;
    if (originalPrice == 0)
    {
        cout << RED << "NO ORDER EXISTS !!!!"
             << RESET << endl;
        return;
    }

    // Create a copy of the order to apply VAT
    ORDER orderWithVAT = order[id - 1];
    applyVAT(orderWithVAT); // Apply VAT using the existing function

    double discount = 0.0;
    double shipping = 100.0;

    if (orderWithVAT.TotalPrice > 1000)
    {
        discount = 5.0; // 5% discount
        applyDiscount(orderWithVAT, discount);
        shipping = 0.0; // Free shipping
        ShippingCost(orderWithVAT, shipping);
    }
    else
    {
        ShippingCost(orderWithVAT, shipping);
    }
    cout << "\n";
    cout << "|                           ORDER SUMMARY WITH VAT                           |\n";
    cout << " --------------------------------------------------------------------------- \n";
    cout << "| " << setw(35) << left << "Subtotal (Before VAT):"
         << setw(20) << right << fixed << setprecision(2) << originalPrice << " EGP |\n";
    cout << "| " << setw(35) << left << "Discount Applied:"
         << setw(23) << right << fixed << setprecision(2) << discount << "% |\n";
    cout << "| " << setw(35) << left << "VAT (14%):"
         << setw(20) << right << fixed << setprecision(2) << orderWithVAT.TotalPrice - (originalPrice + shipping) << " EGP |\n";
    cout << "| " << setw(35) << left << "Shipping Cost:"
         << setw(20) << right << fixed << setprecision(2) << shipping << " EGP |\n";
    cout << "| " << setw(35) << left << "Total (After VAT):"
         << GREEN << setw(20) << right << fixed << setprecision(2) << orderWithVAT.TotalPrice << " EGP " << RESET << "|\n";
    cout << " --------------------------------------------------------------------------- \n";

    if (discount > 0.0)
    {
        cout << YELLOW << "Note:" << RESET << " A discount of " << discount << "% has been applied for orders above 1000 EGP.\n"
             << RESET;
    }
    if (shipping == 0.0)
    {
        cout << YELLOW << "Note:" << RESET << " Free shipping has been applied for orders above 1000 EGP.\n"
             << RESET;
    }
}