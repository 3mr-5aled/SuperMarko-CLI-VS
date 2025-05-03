#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include"lib/struct.h"


void editUserInformation(CUSTOMER customers[], int id, int numOfCustomers);
void DisplayOrderWithVAT(ORDER order[numOfCustomers], int& id);
void ModifyOrder(ORDER order[numOfCustomers], int& id);
void ReviewOrder(ORDER order[numOfCustomers], int& id);
void Categories(PRODUCT product[numOfCategories][numOfProducts], int& id, const int numOfProducts, ORDER order[numOfCustomers]);

void display_edit_func(int& id) {
	cout << CYAN << "\nYou selected: Edit your information\n"
		<< RESET;
	cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n";
	cout << endl;
	editUserInformation(customers, id, numOfCustomers);
}
void display_product_func(int& id) {
	cout << CYAN << "\nYou selected: View product menu\n"
		<< RESET;
	cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n";
	cout << endl;
	Categories(product, id, NUMBEROFPRODUCT, order);
}
void display_revieworder_func(int& id) {
	cout << CYAN << "\nYou selected: Review your order\n"
		<< RESET;
	cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n";
	ReviewOrder(order, id);
	cout << endl;
}
void display_modifyorder_func(int& id) {
	cout << CYAN << "\nYou selected: Modify your order\n"
		<< RESET;
	cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n";
	ModifyOrder(order, id);
	cout << endl;
}
void display_checkout_func(int& id) {
	cout << CYAN << "\nYou selected: View total price\n"
		<< RESET;
	cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n";
	DisplayOrderWithVAT(order, id);
	cout << endl;
}
void display_message_Error() {
	cout << RED << "\nInvalid input, please enter a number between 1 and 5.\n"
		<< RESET;
	cout << "═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n";
	cout << endl;
}
void loop(bool& loggedIn, int& id) {
	while (true)
	{

		string choice;
		cout << YELLOW << "Do you want another operation from the program? (y/n): " << RESET;
		cin >> choice;
		if (choice == "y" || choice == "Y")
			break;
		else if (choice == "n" || choice == "N")
		{
			loggedIn = false;
			id = 0;
			break;
		}
		else
			cout << RED << "Invalid choice! Please enter 'y' or 'n'." << RESET << endl;
	}
}