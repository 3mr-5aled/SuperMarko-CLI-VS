#include <iostream>
#include <fstream>
#include "struct.h"

int save_customers(CUSTOMER customers[])
{
	ofstream outFile("data/customers.txt", ios::out | ios::trunc);
	if (!outFile.is_open())
	{
		cout << RED << "Error: Could not write to customers.txt" << RESET << endl;
		return 1;
	}

	for (int i = 0; i < numOfCustomers; i++)
	{
		if (customers[i].ID == 0)
			continue;
		outFile << customers[i].ID << '\n';
		outFile << customers[i].Name << '\n';
		outFile << customers[i].PhoneNumber << '\n';
		outFile << customers[i].Location << '\n';
		outFile << customers[i].Password << '\n';
	}

	outFile.close();
	return 0;
}

void save_finalorder(ORDER order[])
{
	ofstream outfile("data/finalorder.txt", ios::out | ios::trunc);
	if (!outfile)
	{
		cout << RED << "Error : Could not open finalorder.txt for writing\n"
			 << RESET;
		return;
	}

	for (int i = 0; i < numOfCustomers; i++)
	{
		if (order[i].CustomerID == 0)
			continue;

		outfile << order[i].CustomerID << '\n';
		outfile << order[i].productcount << '\n';

		for (int j = 0; j < order[i].productcount; j++)
		{
			outfile << order[i].Products[j].Name << '\n';
			outfile << order[i].Amount[j] << '\n';
			outfile << order[i].Products[j].BasePrice << '\n';
			outfile << order[i].Products[j].Price << '\n';
		}
		outfile << order[i].TotalPrice << '\n';
	}

	outfile.close();
}