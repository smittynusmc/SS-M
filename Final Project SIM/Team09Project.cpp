// Team09Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <time.h>
#include <deque>

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
	bool isBeingServiced;

public:
	Vehicle(void);
	void getInfo(void);
	double getElapasedArrivalTime();
	void setElapasedArrivalTime(double time);
	double getInterArrivalTime();
	void addDelayTime(double seconds);
	double getDelayTime();
	double getInterServiceTime();
	void setInterServiceTime(double time);
	double getServiceTime();
	bool getIsTurningRight();
	bool getIsBeingServiced();
	void setIsBeingServiced();
	void setServiceTime(); //////////////////////////
	void setInterArrivalTime(double seconds); /////////////////////
};

Vehicle::Vehicle(void) {
	double temp;

	delayTime = 0.0; //delay time starts at zero

	temp = (double)(rand()) / RAND_MAX;
	interArrivalTime = 1.0 + temp * 4.0; // 1 <= x < 5
	//interArrivalTime = 1.0; /////////////////////////////

	temp = (double)(rand()) / RAND_MAX;
	interServiceTime = 1.0 + temp * 2.0; // 1 <= x < 3
	//interServiceTime = 5.0; //////////////////////////////////

	temp = (double)(rand()) / RAND_MAX;
	serviceTime = 1.0 + temp * 76.0; // 1 <= x < 77
	//serviceTime = 1.0;/////////////////////////////

	temp = (double)(rand()) / RAND_MAX;
	double rateOfRights = 78.0 / 130.0; // num right turns / total vehicles
	if (temp <= rateOfRights)
		isTurningRight = true;
	else
		isTurningRight = false;

	isBeingServiced = false; // at car's inception, it is not being serviced
}

void Vehicle::getInfo(void) {
	cout << "Vehicle Info:" << endl;
	cout << "Inter-Arrival Time	: " << interArrivalTime << endl;
	cout << "Delay Time		: " << delayTime << endl;
	cout << "Inter-Service Time	: " << interServiceTime << endl;
	cout << "Service Time		: " << serviceTime << endl;
	cout << "Turn Direction		: ";
	if (isTurningRight)
		cout << "Right" << endl;
	else
		cout << "Left" << endl;
	cout << "Elapsed Arrival Time	: " << elapsedArrivalTime << endl << endl;
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
void Vehicle::addDelayTime(double seconds) {
	delayTime += seconds;
}
double Vehicle::getDelayTime() {
	return delayTime;
}
double Vehicle::getInterServiceTime() {
	return interServiceTime;
}
void Vehicle::setInterServiceTime(double time) {
	interServiceTime = time;
}
double Vehicle::getServiceTime() {
	return serviceTime;
}
bool Vehicle::getIsTurningRight() {
	return isTurningRight;
}
bool Vehicle::getIsBeingServiced() {
	return isBeingServiced;
}
void Vehicle::setIsBeingServiced() {
	isBeingServiced = true;
}
void Vehicle::setServiceTime() { /////////////////////
	serviceTime = 0.5;
}
void Vehicle::setInterArrivalTime(double seconds) { ////////////////////
	interArrivalTime = seconds;
}

int main() {
	srand(time(NULL));

	const int numVehicles = 2;
	double d_hat = 0.0;
	double q = 0.0;
	double q_hat = 0.0;
	double u_hat = 0.0;
	double integralB = 0.0;
	double totalTime = 0.0;
	deque<Vehicle> vehiclesQ;
	Vehicle vehiclesArray[numVehicles];


	cout << "Welcome to our North Campus Drive Intersection Simulation!" << endl << endl;

	for (int i = 0; i < numVehicles; i++) { // run simulation
		Vehicle currentVehicle;

		if (vehiclesQ.empty()) { // no cars in queue
			//currentVehicle.setServiceTime(); /////////////////////////////////////////////////////////////////////////////
			totalTime += currentVehicle.getInterArrivalTime(); // advance time
			currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
			currentVehicle.setIsBeingServiced();
			currentVehicle.setInterServiceTime(0.0); // there is no interservice time when no cars in queue
			vehiclesQ.push_back(currentVehicle); // add vehicle to queue
		}
		else { // cars in queue
			//currentVehicle.setInterArrivalTime(0.5); ////////////////////////////////////////////////////////////////////////////////////////////
				// calculate how long the front car has been already waiting at the front of the queue
			float frontServiceTimeLeft = vehiclesQ.front().getServiceTime() - (totalTime - vehiclesQ.front().getElapasedArrivalTime() - vehiclesQ.front().getDelayTime());
			//currentVehicle.setInterArrivalTime(.2); ////////////////////////////////////////////////////////////////////////////////////////////

			if ((currentVehicle.getInterArrivalTime()) < frontServiceTimeLeft) { // current car reaches queue before front car is serviced
				float d; //calculate current vehicle's delay time
				if (vehiclesQ.size() == 1) // if there's only one car in queue
					d = frontServiceTimeLeft + currentVehicle.getInterServiceTime() - currentVehicle.getInterArrivalTime();////////////check this
				else // if there are 2 or more cars in queue
					d = vehiclesQ.back().getDelayTime() + vehiclesQ.back().getServiceTime() + currentVehicle.getInterServiceTime() - currentVehicle.getInterArrivalTime();
				currentVehicle.addDelayTime(d);

				totalTime += currentVehicle.getInterArrivalTime(); // advance time
				currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
				vehiclesQ.push_back(currentVehicle); // add vehicle to queue
			}

			else { // front car is serviced before current car reaches queue
				vehiclesQ.pop_front();
				if (vehiclesQ.empty()) { // queue is empty
					totalTime += currentVehicle.getInterArrivalTime(); //advance time
					currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
					currentVehicle.setIsBeingServiced();
					currentVehicle.setInterServiceTime(0.0); // there is no interservice time when no cars in queue
					vehiclesQ.push_back(currentVehicle); // add vehicle to queue
				}
				else { // queue is not empty
					// car entering queue before front car is serviced ///////////////////////////////////////////////
					if (currentVehicle.getInterArrivalTime() < vehiclesQ.front().getInterServiceTime() + vehiclesQ.front().getServiceTime()) {
						float d; //calculate current vehicle's delay time
						if (vehiclesQ.size() == 1) // if there's only one car in queue
							d = vehiclesQ.front().getInterServiceTime() + vehiclesQ.front().getServiceTime() + currentVehicle.getInterServiceTime() - currentVehicle.getInterArrivalTime();
						else // if there are 2 or more cars in queue
							d = vehiclesQ.back().getDelayTime() + vehiclesQ.back().getServiceTime() + currentVehicle.getInterServiceTime() - currentVehicle.getInterArrivalTime();
						currentVehicle.addDelayTime(d);

						totalTime += currentVehicle.getInterArrivalTime(); //advance time
						currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
						vehiclesQ.push_back(currentVehicle); // add vehicle to queue
						vehiclesQ.front().setIsBeingServiced(); //////////////////////////////
					}
					else { // car entering queue after front car is serviced
						float eventTimeBeforeNextArrival = frontServiceTimeLeft; // time advanced since first car was popped above
						float nextArrivalTime = currentVehicle.getInterArrivalTime();

						while (eventTimeBeforeNextArrival < nextArrivalTime) { // keep moving cars up and popping cars until next arrival time
							if (!vehiclesQ.empty()) {
								eventTimeBeforeNextArrival += vehiclesQ.front().getServiceTime();
								if (eventTimeBeforeNextArrival <= nextArrivalTime) {
									vehiclesQ.front().setIsBeingServiced();
									eventTimeBeforeNextArrival += vehiclesQ.front().getServiceTime();
									if (eventTimeBeforeNextArrival < nextArrivalTime) {
										vehiclesQ.pop_front();
									}
								}
							}
							else {
								eventTimeBeforeNextArrival = 99999.9; //to break out of loop
							}
						}

						totalTime += currentVehicle.getInterArrivalTime(); //advance time
						currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
						vehiclesQ.push_back(currentVehicle); // add vehicle to queue
					}
				}
			}
		}

		currentVehicle.getInfo();
	}

	// going through vehicles left in queue if there are more than one
	int qSize = vehiclesQ.size();
	for (int i = 0; i < qSize; i++) {
		Vehicle frontVehicle = vehiclesQ.front();
		if (vehiclesQ.size() == 1) // when there's one car left
			totalTime += frontVehicle.getServiceTime() + frontVehicle.getInterServiceTime(); // advance time
		else {
			totalTime += frontVehicle.getServiceTime() - // advance time for the remaining service time of front car
				(totalTime - frontVehicle.getElapasedArrivalTime() - frontVehicle.getDelayTime());
		}
		vehiclesQ.pop_front();
	}

	cout << endl;
	cout << "Total time: " << totalTime << endl;

	cin.get();
	cin.get();
	return 0;
}
