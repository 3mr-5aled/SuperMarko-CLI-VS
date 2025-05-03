#pragma once
#include"struct.h"
#include <string>
#include <iostream>
#include <iomanip>
#include<conio.h>
using namespace std;
bool changestateExchange(string productInput, int& number)
{
    if ((productInput.length() == 1 && isdigit(productInput[0])))
    {
        number = productInput[0] - '0';
        return true;
    }
    else if (productInput == "10")
    {
        number = 10;
        return true;
    }
    else
        return false;
}
bool returning(string& type, string typeFunc, bool mask = false) {
    type = "";
    char ch;
    while ((ch = _getch()) != '\r') // Enter key
    {
        if (ch == '\b') {
        
            if (type.empty() && !mask) {
                    cout << RED << endl << "Canceled " << typeFunc << " Returning to menu.\n\n" << RESET;
                    return false;  // Cancel input
            }
            else {
                type.pop_back();
                cout << "\b \b";
            }
        }
        else {
            type += ch;
            if (mask)
                cout << '*';
            else
                cout << ch;
        }
    }
    cout << endl;
    return true;  // Successful input
}
