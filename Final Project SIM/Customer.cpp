#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <queue>
#include <deque>
#include <math.h>
//#include "Customer.h"
//#include "Customer.cpp"

using namespace std;

// Customer class
// Testing github
class Customer
{
private:
	double entryTime; // x < rand(t) < y
	double serviceTime;
	double processTime;
	int p;
	double exitTime;
	double minServiceTime = 12;
	double maxServiceTime = 90;
	int custmer = 0;

public:
	Customer(void);
	Customer(double et);
	void getInfo(void);
	double getProcessTime();
	double getServiceTime();
	void addServiceTime(double additionalTime);
	double getEntryTime();
	double getExitTime();

	int getP();
	~Customer(void);
};



Customer::Customer(void)
{
	double temp;
	//srand(time(NULL));
	temp = (double)(rand()) / RAND_MAX;
	entryTime = .5 + temp * 4; // 0.5 <= et < 4.5

	temp = (double)(rand()) / RAND_MAX;
	serviceTime = minServiceTime + temp * (maxServiceTime - minServiceTime); //12 <= st < 90

	temp = (double)(rand()) / RAND_MAX;
	processTime = .1 + temp * 9.9; //.1 <= pt < 10

	temp = (double)(rand()) / RAND_MAX;
	exitTime = 1 + temp * 4; //1 <= ext < 5

	p = rand() % 5;
	
		
}

Customer::Customer(double et)
{
	//srand(time(NULL));
	double temp = (double)(rand()) / RAND_MAX;
	entryTime = .5 + temp * 4; // 0.5 <= et < 4.5
}

Customer::~Customer(void)
{
}

void Customer::getInfo(void)
{
	cout << "Customer Info:" << endl;
	cout << "Entry Time   : " << entryTime << endl;
	cout << "Service Time : " << serviceTime << endl;
	cout << "Process Time : " << processTime << endl;
	cout << "Exit Time    : " << exitTime << endl;
}

double Customer::getProcessTime()
{
	return processTime;
}

double Customer::getServiceTime()
{
	return serviceTime;
}

void Customer::addServiceTime(double additionalTime)
{
	serviceTime += additionalTime;
}

double Customer::getEntryTime()
{
	return entryTime;
}

double Customer::getExitTime()
{
	return exitTime;
}
int Customer::getP()
{
	return p;
}


int run()
{
	srand(time(NULL));
	double d_hat = 0;
	double q = 0;
	double q_hat = 0;
	double u_hat = 0;
	double integralB = 0;
	double Tn = 0;

	const int ASIZE = 10;
	
	//04-04-14
	cout << "\n\nGoing through the array for the estimators: " << endl;

	for (int i = 0; i < ASIZE; i++)
	{
		printf("Customer # %d\n", (i+1));
		cust[i].getInfo();
		cout << endl;
	}

	// for d_hat
	// estimator of the average delay
	// in the queue
	double temp = 0;
	for (int i = 0; i < ASIZE; i++)
	{
		temp += cust[i].getProcessTime()
			+ cust[i].getServiceTime();

	}
	d_hat = temp / ASIZE;
	cout << "\n\nD<hat> = " << d_hat << endl;

	// q is the average time in the q
	// for each of it's weighted
	// delay lengths
	temp = 0;
	for (int i = 0; i < ASIZE; i++)
	{
		temp += cust[i].getProcessTime()
			* cust[i].getP();

	}
	q_hat = temp;
	cout << "\n\nq<hat> = " << q_hat << endl;

	// Find T(n) for the entire run
	Tn = 0;
	for (int i = 0; i < ASIZE; i++)
	{
		Tn += (cust[i].getExitTime()
			+ cust[i].getProcessTime()
			+ cust[i].getServiceTime()
			- cust[i].getEntryTime());

	}
	cout << "\n\nT(n) = " << Tn << endl;

	// Find IntegralB (when the queue is not being used)

	integralB = 0;
	temp = 0;
	for (int i = 1; i < ASIZE; i++)
	{
		integralB += cust[i - 1].getExitTime();
	}
	cout << "\n\nIntegral B = " << integralB << endl;

	// and finally, q_hat
	u_hat = (Tn - integralB) / Tn;
	cout << "\n\nu<hat> = " << u_hat << endl;

	cin.get();
	cin.get();
	return 0;

}


