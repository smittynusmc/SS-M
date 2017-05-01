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
	double elapsedArrivalTime;
	double interArrivalTime;
	double delayTime;
	double interServiceTime;
	double serviceTime;
	bool isTurningRight;
	
public:
	Vehicle(void);
	void getInfo(void);
	double getElapasedArrivalTime();
	void setElapasedArrivalTime(double time);
	double getInterArrivalTime();
	void setInitialDelayTime(int qSize);
	void addDelayTime(double seconds);
	double getDelayTime();
	double getInterServiceTime();
	double getServiceTime();

};

Vehicle::Vehicle(void) {
	double temp;

	temp = (double)(rand()) / RAND_MAX;
	interArrivalTime = 1.0 + temp * 4.0; // 1 <= et < 5

	temp = (double)(rand()) / RAND_MAX;
	interServiceTime = 1.0 + temp * 4.0; // 1 <= et < 5

	temp = (double)(rand()) / RAND_MAX;
	serviceTime = 1.0 + temp * 76.0; // 1 <= st < 77

	temp = (double)(rand()) / RAND_MAX;
	double rateOfRights = 78.0 / 130.0; // num right turns / total vehicles
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
		cout << "Left" << endl << endl;
}

double Vehicle::getElapasedArrivalTime() {
	return elapsedArrivalTime;
}
void Vehicle::setElapasedArrivalTime(double time) {
	elapsedArrivalTime = time;
}
double Vehicle::getInterArrivalTime() {
	return interArrivalTime;
}
void Vehicle::setInitialDelayTime(int qSize) {
	if (qSize < 8)
		delayTime = 8.0 - qSize; // adds the queue delay to drive to the back or front of the queue
	else
		delayTime = 0.0;
}
void Vehicle::addDelayTime(double seconds) {
	delayTime += seconds;
}
double Vehicle::getDelayTime() {
	return delayTime;
}
double Vehicle::getInterServiceTime() {
	return interServiceTime;
}
double Vehicle::getServiceTime() {
	return serviceTime;
}

int main() {
	srand(time(NULL));

	const int numVehicles = 2;
	double d_hat = 0;
	double q = 0;
	double q_hat = 0;
	double u_hat = 0;
	double integralB = 0;
	double totalTime = 0;
	queue<Vehicle> vehicles;

	cout << "Welcome to our North Campus Drive Intersection Simulation!" << endl << endl;

	for (int i = 0; i < numVehicles; i++) { // run simulation
		Vehicle currentVehicle;
		if (vehicles.empty()) { // no cars in queue

			currentVehicle.setInitialDelayTime(vehicles.size()); // add the delay time to drive into the queue
			vehicles.push(currentVehicle); // add vehicle to queue
			totalTime += currentVehicle.getInterArrivalTime();
		}
		else { // cars in queue
			if (currentVehicle.getInterArrivalTime() < vehicles.front().getServiceTime()) { //no car being serviced

			}
			else { // car being serviced

			}
		}

		currentVehicle.getInfo();
	}

	cout << endl;
	cout << "Total time: " << totalTime << endl;

	cin.get();
	cin.get();
	return 0;
}
