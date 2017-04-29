// Team09Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <time.h>
#include <queue>

using namespace std;

// Vehicle class
class Vehicle {
private:
	double interArrivalTime;
	double interServiceTime;
	double serviceTime;
	bool isTurningRight;

public:
	Vehicle(void);
	void getInfo(void);
	double getInterArrivalTime();
	double getInterServiceTime();
	double getServiceTime();

};

Vehicle::Vehicle(void) {
	double temp;

	temp = (double)(rand()) / RAND_MAX;
	interArrivalTime = 1 + temp * 4; // 1 <= et < 5

	temp = (double)(rand()) / RAND_MAX;
	interServiceTime = 1 + temp * 4; // 1 <= et < 5

	temp = (double)(rand()) / RAND_MAX;
	serviceTime = 1 + temp * 76; // 1 <= st < 77

	temp = (double)(rand()) / RAND_MAX;
	double rateOfRights = 78.0 / 130.0; // num right turns / total vehicles
	cout << "Current car: " << rateOfRights << " vs. " << temp << endl;
	if (temp <= rateOfRights)
		isTurningRight = true;
	else
		isTurningRight = false;
}

void Vehicle::getInfo(void) {
	cout << "Vehicle Info:" << endl;
	cout << "Inter-Arrival Time	: " << interArrivalTime << endl;
	cout << "Inter-Service Time	: " << interServiceTime << endl;
	cout << "Service Time		: " << serviceTime << endl;
	cout << "Turn Direction		: ";
	if (isTurningRight)
		cout << "Right" << endl;
	else
		cout << "Left" << endl;
}

double Vehicle::getInterArrivalTime() {
	return interArrivalTime;
}
double Vehicle::getInterServiceTime() {
	return interServiceTime;
}
double Vehicle::getServiceTime() {
	return serviceTime;
}

int main() {
	srand(time(NULL));

	const int numVehicles = 5;
	double d_hat = 0;
	double q = 0;
	double q_hat = 0;
	double u_hat = 0;
	double integralB = 0;
	double totalTime = 0;

	cout << "Welcome to our North Campus Drive Intersection Simulation!" << endl << endl;

	Vehicle vehicles[numVehicles];
	for (int i = 0; i < numVehicles; i++) { // populate vehicles
		Vehicle temp;
		vehicles[i] = temp;
	}

	for (int i = 0; i < numVehicles; i++) { // run simulation

		totalTime++;
	}

	cin.get();
	cin.get();
	return 0;
}