#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <string>
using namespace std;

// Define the constants
const int numOfProducts = 10;
const int numOfCategories = 10;
const int numOfOrders = 20;
const int numOfCustomers = 10;

// date structure
struct DATE
{
    int Day = 0;
    int Month = 0;
    int Year = 0;
};

// customer structure
struct CUSTOMER
{
    int ID = 0;
    string Name = "";
    string PhoneNumber = "";
    string Location = "";
    string Password = "";
} customers[numOfCustomers];

// product structure
struct PRODUCT
{
    string Code = "";
    string Name = "";
    string Category = "";
    DATE ProductionDate = {};
    DATE ExpiredDate = {};
    double Price = 0.0;
    double BasePrice = 0.0;
} product[numOfCategories][numOfProducts];

// order structure
struct ORDER
{
    int CustomerID = 0;
    PRODUCT Products[numOfProducts] = {};
    double TotalPrice = 0.0;
    double Amount[numOfProducts] = {};
    int productcount = 0;
} order[numOfCustomers];

// ANSI escape codes for styling terminal output
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";
const string RED = "\033[91m";
const string GREEN = "\033[92m";
const string YELLOW = "\033[93m";
const string BLUE = "\033[94m";
const string CYAN = "\033[96m";
const string PURPLE = "\033[95m";
const string WHITE_BG = "\033[107m";
const string BLACK_TEXT = "\033[90m";
const string ORANGE = "\033[38;5;214m";
const string TEAL = "\033[36m";
const string BLINK = "\033[5m";

#endif // STRUCT_H
