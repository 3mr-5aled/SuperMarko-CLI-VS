#include <iostream>
#include <fstream>
#include <string>
#include "struct.h"
using namespace std;

void read_product_from_file(PRODUCT product[CATEGORY][NUMBEROFPRODUCT], const int CATEGORY, const int NUMBEROFPRODUCT)
{
	fstream myfile;
	myfile.open("data/productmenu.txt", ios::in);
	if (!myfile)
	{
		cout << "Error: Could not open product file!\n";
		return;
	}
	for (int categoryIndex = 0; categoryIndex < CATEGORY; categoryIndex++)
	{
		for (int numberOfProductIndex = 0; numberOfProductIndex < NUMBEROFPRODUCT; numberOfProductIndex++)
		{
			myfile >> product[categoryIndex][numberOfProductIndex].Code;
			myfile >> product[categoryIndex][numberOfProductIndex].Name;
			myfile >> product[categoryIndex][numberOfProductIndex].Category;
			myfile >> product[categoryIndex][numberOfProductIndex].ProductionDate.Day;
			myfile >> product[categoryIndex][numberOfProductIndex].ProductionDate.Month;
			myfile >> product[categoryIndex][numberOfProductIndex].ProductionDate.Year;
			myfile >> product[categoryIndex][numberOfProductIndex].ExpiredDate.Day;
			myfile >> product[categoryIndex][numberOfProductIndex].ExpiredDate.Month;
			myfile >> product[categoryIndex][numberOfProductIndex].ExpiredDate.Year;
			myfile >> product[categoryIndex][numberOfProductIndex].Price;

			// to use base price in modifyorder function.
			product[categoryIndex][numberOfProductIndex].BasePrice = product[categoryIndex][numberOfProductIndex].Price;
		}
	}
	myfile.close();
}

void read_customer_from_file(CUSTOMER customers[], const int numOfCustomers, fstream &myfile)
{
	myfile.clear();	 // clear any EOF flags
	myfile.seekg(0); // rewind to beginning of file

	for (int i = 0; i < numOfCustomers; i++)
	{
		if (!(myfile >> customers[i].ID))
			break;
		myfile.ignore(); // skip newline after ID
		getline(myfile, customers[i].Name);
		myfile >> customers[i].PhoneNumber;
		myfile.ignore();
		getline(myfile, customers[i].Location);
		myfile >> customers[i].Password;
		myfile.ignore();
	}
}

void read_finalorder_from_file(ORDER order[])
{
	fstream file("data/finalorder.txt", ios::in);
	if (!file)
	{
		cout << RED << "Error : Could not open finalorder.txt for reading\n"
			 << RESET;
		return;
	}

	string line;
	while (getline(file, line)) // Read first line (CustomerID)
	{
		if (line.empty())
			continue;

		int currentIndex = stoi(line) - 1; // Convert CustomerID to index
		order[currentIndex].CustomerID = currentIndex + 1;

		// Read product count
		getline(file, line);
		int productCount = stoi(line);
		order[currentIndex].productcount = productCount;

		// Read each product's details
		for (int j = 0; j < productCount; j++)
		{
			// Read product name
			getline(file, line);
			order[currentIndex].Products[j].Name = line;

			// Read amount
			getline(file, line);
			order[currentIndex].Amount[j] = stoi(line);

			// Read base price
			getline(file, line);
			order[currentIndex].Products[j].BasePrice = stod(line);

			// Read price
			getline(file, line);
			order[currentIndex].Products[j].Price = stod(line);
		}

		// Read total price
		getline(file, line);
		order[currentIndex].TotalPrice = stod(line);
	}

	file.close();
}