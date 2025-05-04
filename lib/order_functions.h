#include "lib/struct.h"
#include <iostream>
#include "lib/change_exchange.h"
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

bool addProducts(ORDER order[numOfCustomers], PRODUCT product[numOfCategories][numOfProducts], int& id, int CategoryCase, bool& returnToCategoryMenu)
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
    answerofproduct = "y";
    while (answerofproduct == "y")
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

        

        if (!changestateExchange(productInput, number)) {
            cout << RED << "Invalid input. Please enter a number.\n" << RESET;
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
            cout << RED << "Invalid input. Please enter a valid number.\n"
                << RESET;
            answerofproduct = "y";
            continue;
        }

        // Store the product name for better user experience
        string productName = product[CategoryCase - 1][number - 1].Name;

        cout << YELLOW << "How many amount of " << CYAN << productName << YELLOW << " do you want? (enter 0 to cancel)\n"
            << RESET;
        cin >> amount;
        changestateExchange(amount, amounts);

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

        // Cancel add if amount is zero
        if (amounts == 0)
        {
            cout << RED << "Canceled adding product.\n"
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
            cout << "Updated quantity of " << order[id - 1].Products[existingIndex].Name << " : " << GREEN << order[id - 1].Amount[existingIndex] << RESET << endl;
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

        cout << GREEN << "Do you want to choose another product from current category? (y/n)" << RESET<<endl;
        cin >> answerofproduct;

        // Validate input
        while (answerofproduct != "y" && answerofproduct != "Y" && answerofproduct != "n" && answerofproduct != "N") {
            cout << RED << "Invalid input. Please enter 'y' or 'n'.\n" << RESET;
            cout << GREEN << "Do you want to choose another product from current category? (y/n): " << RESET;
            cin >> answerofproduct;
        }

        if (answerofproduct == "n" || answerofproduct == "N") {
            break;
        }
    }

    return true;
}

void ReviewOrder(ORDER order[numOfCustomers], int& id)
{
    if (order[id - 1].productcount == 0)
    {
        cout << RED << "You have no items in your order to review.\n" << RESET;
        return;
    }

    cout << "\n";
    cout << BOLD << CYAN << "| 🧾                               ORDER CHEQUE                                 🧾 |" << RESET << "\n";
    cout << "\n";
    cout << BOLD << YELLOW << "|  No.  |     Product Name     |  Quantity  | Unit Price |   Price   |" << RESET << "\n";
    cout << BOLD << YELLOW << "-------------------------------------------------------------------------------" << RESET << "\n";

    for (int i = 0; i < order[id - 1].productcount; i++)
    {
        cout << YELLOW << "|  " << setw(4) << i + 1 << " | " << RESET;
        cout << CYAN << setw(20) << order[id - 1].Products[i].Name << RESET << " | ";
        cout << GREEN << setw(10) << order[id - 1].Amount[i] << RESET << " | ";
        cout << TEAL << setw(10) << fixed << setprecision(2) << order[id - 1].Products[i].BasePrice << RESET << " | ";
        cout << ORANGE << setw(8) << fixed << setprecision(2) << order[id - 1].Products[i].Price << RESET << " |\n";
    }

    cout << BOLD << "-------------------------------------------------------------------------------" << RESET << "\n";
    cout << BOLD << "TOTAL: " << RESET << GREEN << fixed << setprecision(2) << order[id - 1].TotalPrice << " EGP" << RESET << "\n";
}


void ModifyOrder(ORDER order[numOfCustomers], int& id)
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

        string input;
        int choice;
        cin >> input;
        bool y = changestateExchange(input, choice);

        if (choice == 0)
            break;

        if (choice < 1 || choice > order[index].productcount || y == false)
        {
            cout << RED << "Invalid choice. Try again\n"
                << RESET;
            continue;
        }
        cout << "You have selected : " << order[index].Products[choice - 1].Name;
        cout << " | Quantity: " << order[index].Amount[choice - 1];
        cout << " | Price : " << order[index].Products[choice - 1].Price << " EGP\n";

        int ItemIndex = choice - 1;

        string optionInput;
        int option = -1;
        do
        {
            cout << CYAN << "1. Change quantity\n"
                << RESET;
            cout << CYAN << "2. Remove Item\n"
                << RESET;
            cout << CYAN << "0. Cancel\n"
                << RESET;
            cout << "Enter Your option : ";
            string optionInput;
            cin >> optionInput;

            if (!changestateExchange(optionInput, option) || option < 0 || option > 2)
            {
                cout << RED << "Invalid option. Please enter 0, 1, or 2.\n"
                    << RESET;
                option = -1; // Force loop to repeat
            }
        } while (option == -1);

        if (option == 1)
        {
            int newQuantity = -1;
            string newQuantityInput;

            do {
                cout << "Enter your new quantity : ";
                cin >> newQuantityInput;

                bool isValid = true;

                // Validate input is digits only
                for (char c : newQuantityInput)
                {
                    if (!isdigit(c))
                    {
                        isValid = false;
                        break;
                    }
                }

                if (!isValid || !changestateExchange(newQuantityInput, newQuantity))
                {
                    cout << RED << "Invalid input. Please enter a valid number.\n" << RESET;
                    continue;
                }

                newQuantity = stoi(newQuantityInput);

                if (newQuantity == 0)
                {
                    cout << RED << "Canceled updating product.\n" << RESET;
                    break;
                }

                if (newQuantity < 1 || newQuantity > 10)
                {
                    cout << RED << "Invalid quantity. Must be between 1 and 10.\n" << RESET;
                    continue;
                }

                if (newQuantity == order[index].Amount[ItemIndex])
                {
                    cout << RED << "You entered the same quantity. Please choose a different one.\n" << RESET;
                    continue;
                }

                // ✅ Passed all checks — update order
                order[index].TotalPrice -= order[index].Products[ItemIndex].Price;
                order[index].Amount[ItemIndex] = newQuantity;
                order[index].Products[ItemIndex].Price = newQuantity * order[index].Products[ItemIndex].BasePrice;
                order[index].TotalPrice += order[index].Products[ItemIndex].Price;

                cout << GREEN << "Updated: " << order[index].Products[ItemIndex].Name << " x" << newQuantity << RESET << endl;
                break;

            } while (true); // loop until valid input and quantity is changed
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
            continue;
        }
    }
    PRODUCT finalorder[10];
    int finalcount = order[index].productcount;

    for (int i = 0; i < finalcount; i++)
    {
        finalorder[i] = order[index].Products[i];
    }

    if (order[index].productcount != 0)
    {

        cout << TEAL << "Final ordered items : \n"
            << RESET;
        for (int i = 0; i < finalcount; i++)
        {
            cout << i + 1 << ". " << finalorder[i].Name;
            cout << " | Quantity : " << order[index].Amount[i];
            cout << " | Price : " << finalorder[i].Price;
            cout << " EGP\n";
        }
    }
}

void DisplayOrderWithVAT(ORDER order[numOfCustomers], int& id)
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
    cout << YELLOW << "Note:" << RESET << " The total price includes a VAT of 14%.\n"
        << RESET;
    cout << YELLOW << "Note:" << RESET << " The discount is applied for orders above 1000 EGP.\n"
        << RESET;
    cout << YELLOW << "Note:" << RESET << " The shipping cost is free for orders above 1000 EGP.\n"
        << RESET;


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