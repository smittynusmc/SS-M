#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

void main()
{
	cout << "Welcome to the SSM External File Creator Program" << endl;
	srand(time(NULL));
	cout << "Random numbers: " << endl;
	cout << "Max value of : " << RAND_MAX << endl;
	cout << endl << endl;
	for (int i = 0; i < 10; i++)
		cout << (double)(rand()) / RAND_MAX << endl;

	cout << endl << endl;
	for (int i = 0; i < 10; i++)
		cout << 1 + rand() % 6 << endl;


	cout << "Now, write it to an external file: \n\n";
	ifstream inStream;
	ofstream outStream; // Make it outStream1

	outStream.open("outfile.dat");
	if (outStream.fail())
	{
		cout << "Error opening outfile.dat\n";
		exit(1);
	}
	outStream << "Data Elements\n";

	for (int i = 0; i < 10; i++)
		outStream << (double)(rand()) / RAND_MAX << endl;

	outStream.close();

	ifstream inStream1;
	inStream1.open("outfile.dat");

	ofstream outStream1;
	outStream1.open("outfile2.dat");
	if (outStream1.fail())
	{
		cout << "Error opening outfile2.dat\n";
		exit(1);
	}


	if (outStream1.fail())
	{
		cout << "Error opening outfile2.dat\n";
		exit(1);
	}


	string s;

	inStream1 >> s;

	cout << s << endl;


	inStream1.close();

	outStream1 << s << endl;


	outStream1.close();

	cin.get();
	cin.get();

}

