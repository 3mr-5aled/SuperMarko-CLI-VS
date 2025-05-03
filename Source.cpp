#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "lib/struct.h"
#include "lib/menu_functions.h"
#include "lib/registeration.h"
#include "lib/edit_functions.h"
#include "lib/addtional_features.h"
#include "lib/read_functions.h"
#include "lib/get_functions.h"
#include "lib/save_functions.h"
#include "lib/order_functions.h"
#include"lib/display_func.h"

using namespace std;

int main()
{
	// Set the console to UTF-8 encoding
	// This is important for displaying Unicode characters correctly
	system("chcp 65001 > nul");

	fstream myfile("./data/customers.txt", ios::in | ios::out);
	if (!myfile.is_open())
	{
		cout << RED << "Error opening the file." << RESET << endl;
		return 1;
	}

	read_product_from_file(product, numOfCategories, numOfProducts);
	read_customer_from_file(customers, numOfCustomers, myfile);
	read_finalorder_from_file(order);

	int id = 0;
	bool exitProgram = false;
	
	while (!exitProgram)
	{
		cout <<endl <<"═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════"<<endl;
		cout << BLINK << ORANGE << R"(

		⠀⠀⠈⠛⠻⠶⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠈⢻⣆⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⢻⡏⠉⠉⠉⠉⢹⡏⠉⠉⠉⠉⣿⠉⠉⠉⠉⠉⣹⠇⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠈⣿⣀⣀⣀⣀⣸⣧⣀⣀⣀⣀⣿⣄⣀⣀⣀⣠⡿⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠸⣧⠀⠀⠀⢸⡇⠀⠀⠀⠀⣿⠁⠀⠀⠀⣿⠃⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣧⣤⣤⣼⣧⣤⣤⣤⣤⣿⣤⣤⣤⣼⡏⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⢸⡇⠀⠀⠀⠀⣿⠀⠀⢠⡿⠀⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣷⠤⠼⠷⠤⠤⠤⠤⠿⠦⠤⠾⠃⠀⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⢾⣷⢶⣶⠶⠶⠶⠶⠶⠶⠶⣶⠶⣶⡶⠀⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣧⣠⡿⠀⠀⠀⠀⠀⠀⢷⣄⣼⠇⠀⠀⠀⠀⠀⠀⠀
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀
		)" << RESET<<ORANGE<<R"(
		Welcome to the Grocery Store Management System
		)" << RESET;
		cout << BOLD << TEAL <<
			R"(███████╗██╗   ██╗██████╗ ███████╗██████╗     ███╗   ███╗ █████╗ ██████╗ ██╗  ██╗ ██████╗ 
		██╔════╝██║   ██║██╔══██╗██╔════╝██╔══██╗    ████╗ ████║██╔══██╗██╔══██╗██║ ██╔╝██╔═══██╗   
		███████╗██║   ██║██████╔╝█████╗  ██████╔╝    ██╔████╔██║███████║██████╔╝█████╔╝ ██║   ██║
		╚════██║██║   ██║██╔═══╝ ██╔══╝  ██╔══██╗    ██║╚██╔╝██║██╔══██║██╔══██╗██╔═██╗ ██║   ██║
		███████║╚██████╔╝██║     ███████╗██║  ██║    ██║ ╚═╝ ██║██║  ██║██║  ██║██║  ██╗╚██████╔╝
		╚══════╝ ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ 
		                                                              made by: real developers🧑🏻‍💻
		)" << RESET
			<< endl;
		bool back;
		int flag = 1;
		menu_logging_in(customers, numOfCustomers, myfile, id,flag,back);

		if (!flag)
		{
			exitProgram = true;
			if(!exitProgram)
				cout << RED << "LOGIN FAILED!....." << RESET << endl;
			break;
		}


		int number;
		bool loggedIn = true;

		while (loggedIn)
		{
			number = bigmenu();
			switch (number)
			{
			case 1:
				display_edit_func(id);
				continue;
			case 2:
				display_product_func(id);
				continue;
			case 3:
				display_revieworder_func(id);
				break;
			case 4:
				display_modifyorder_func(id);
				break;
			case 5:
				display_checkout_func(id);
				break;
			case 0:
				log_out(id, loggedIn);
				break;
			default:
				display_message_Error();
				continue;
			}
			if (loggedIn)
			{
				/*loop(loggedIn, id);*/
				/*cout << YELLOW << "Press Enter to continue..." << RESET;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				char buffer[256];
				cin.getline(buffer, sizeof(buffer));
				cout << endl;*/
				cout << YELLOW << "Press Enter to continue..." << RESET;
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input
				cin.get(); // Waits for Enter


			}
		}
	}

	myfile.close(); // Close read file
	save_customers(customers);
	save_finalorder(order);
	
	return 0;
}