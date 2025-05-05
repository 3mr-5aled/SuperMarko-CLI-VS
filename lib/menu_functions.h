#include "struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "lib/change_exchange.h"
using namespace std;

const int NUMBEROFPRODUCT = 10;
bool addProducts(ORDER order[numOfCustomers], PRODUCT product[numOfCategories][numOfProducts], int &id, int CategoryCase, bool &returnToCategoryMenu);
int bigmenu()
{
	string input;
	int number;
	while (true)
	{
		cout << "\n";
		cout << BOLD<<BLINK;
		cout << "            =============================================\n";
		cout << "                        # WELCOME TO OUR SYSTEM #        \n";
		cout << "            =============================================\n";
		cout << RESET << endl;

		cout << "\n";
		cout << "\n";
		cout << CYAN << "*  👤 Press (1) to edit your information.                                   *\n";
		cout << "*  🛍️ Press (2) to view your product menu.                                  *\n";
		cout << "*  🧾 Press (3) to review your order.                                       *\n";
		cout << "*  🛠️ Press (4) to modify your order.                                       *\n";
		cout << "*  💰 Press (5) to view your total price.                                   *\n";
		cout << "*  🚪 Press (0) to log out.                                                 *\n";
		cout << RESET << "\n";
		cout << "\n";
		cout << YELLOW << "Please enter the number you want to choose from the above list (1-5): " << RESET;

		cin >> input;
		bool state = changestateExchange(input, number);
		if (!state)
		{
			cout << RED << "\nINVALID CHOICE. Please enter a valid number.\n"
				<< RESET;
		}
		else if (number < 0 || number > 5)
		{
			cout << RED << "\nInvalid input, number must be between 0 and 5.\n"
				<< RESET;
		}
		else
			break;
	}

	return number;
}

void Categories(PRODUCT product[numOfCategories][numOfProducts], int &id, const int numOfProducts, ORDER order[numOfCustomers])
{
	int numberofcategory;
	string choice;
	string input;
	int CategoryCases;
	while (true)
	{
		bool returnToCategoryMenu = false;
		cout << endl;
		cout << BOLD << BLUE << "\n========= 🛒 SUPERMARKET CATEGORIES =========\n"
			<< RESET;
		cout << GREEN << "1.  🍎 Fresh Produce (fruits)\n";
		cout << "2.  🥦 Fresh Produce (vegetable)\n";
		cout << "3.  🥚 Dairy & Eggs\n";
		cout << "4.  🥩 Butcher Shop\n";
		cout << "5.  🐟 Seafood\n";
		cout << "6.  🍗 Poultry\n";
		cout << "7.  🍞 Bakery & Bread\n";
		cout << "8.  🍬 Snacks & Sweets\n";
		cout << "9.  🧹 Household & Cleaning Supplies\n";
		cout << "10. 🐾 Pet Supplies\n";
		cout << "0. Return to big menu.\n"
			<< RESET;
		cout << BOLD << BLUE << "===========================================\n"
			<< RESET;
		cout << YELLOW << "Please enter the category number: " << RESET;
		cin.clear();
		cin >> input;
		
		bool state = changestateExchange(input, numberofcategory);

		if (numberofcategory < 0 || numberofcategory > 10 || !state)
		{
			cout << RED << "\nInvalid input, please enter a number between 0 and 10.\n"
				<< RESET;
			continue;
		}
		else
			CategoryCases = numberofcategory;
		
		
		if (numberofcategory > 0 && numberofcategory < 11)
		{
			cout << PURPLE << "\n\t\t\t    You selected: " << product[numberofcategory - 1][0].Category << " of category.\n"
				 << RESET;

			cout << "******************************************************************************************\n";
			cout << "|                                      PRODUCT LIST                                     |\n";
			cout << "******************************************************************************************\n";
			cout << "|  No.  |        Name        |   Code    | Production Date | Expired Date  |   Price    |\n";
			cout << "------------------------------------------------------------------------------------------\n";

			for (int numberOfProductIndex = 0; numberOfProductIndex < NUMBEROFPRODUCT; numberOfProductIndex++)
			{
				if (!product[numberofcategory - 1][numberOfProductIndex].Code.empty())
				{
					cout << CYAN;
					cout << "|  " << setw(2) << numberOfProductIndex + 1 << "   | ";
					cout << left << setw(18) << product[numberofcategory - 1][numberOfProductIndex].Name << " | ";
					cout << setw(9) << product[numberofcategory - 1][numberOfProductIndex].Code << " |   ";
					cout << right << setw(2) << setfill('0') << product[numberofcategory - 1][numberOfProductIndex].ProductionDate.Day << "-"
						 << setw(2) << setfill('0') << product[numberofcategory - 1][numberOfProductIndex].ProductionDate.Month << "-"
						 << setw(4) << setfill(' ') << product[numberofcategory - 1][numberOfProductIndex].ProductionDate.Year << "    |  ";
					cout << setw(2) << setfill('0') << product[numberofcategory - 1][numberOfProductIndex].ExpiredDate.Day << "-"
						 << setw(2) << setfill('0') << product[numberofcategory - 1][numberOfProductIndex].ExpiredDate.Month << "-"
						 << setw(4) << setfill(' ') << product[numberofcategory - 1][numberOfProductIndex].ExpiredDate.Year << "   | ";
					cout << right << setw(6) << product[numberofcategory - 1][numberOfProductIndex].Price << " EGP |\n";
					cout << RESET;
					cout << "------------------------------------------------------------------------------------------\n";
				}
			}
			if (!addProducts(order, product, id, CategoryCases, returnToCategoryMenu))
			{
				break;
			}
		}
		else if (numberofcategory == 0)
		{
			return;
		}
		else
		{
			cout << RED << "\nInvalid input, please enter a number between 1 and 10.\n"
				 << RESET;
			continue;
		}

		if (returnToCategoryMenu)
			continue;

		while (true) {
			cout << GREEN << "Do you want to return back to categories? (y/n): " << RESET;
			cin >> choice;

			if (choice == "y" || choice == "Y") {
				// User wants to return � restart loop
				break; // or use 'continue;' if inside a larger loop
			}
			else if (choice == "n" || choice == "N") {
				// User wants to exit
				return;
			}
			else {
				cout << RED << "Invalid input. Please enter 'y' or 'n'.\n" << RESET;
			}
		}

	}
}
