// Team09Project.cpp : Defines the entry point for the console application.
// Team 09: Adam Tucker, Asa Swan, Evan Gallo

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
};

Vehicle::Vehicle(void) {
	double temp;
	double temp2;

	delayTime = 0.0; //delay time starts at zero

	temp = (double)(rand()) / RAND_MAX;
	temp2 = 1 + temp * 129; // 1 <= x < 130
	int probabilityVehicleArrivalTime[] = { 0,2,9,15,32,42,47,54,59,68,74,77,78,83,86,92,93,94,98,99,104,106,107,109,110,112,112,112,113,114,115,115,116,118,119,122,122,124,125,125,127,128,128,128,128,128,128,128,128,128,128,131 };
	for (int i = 0; i < sizeof(probabilityVehicleArrivalTime) / sizeof(probabilityVehicleArrivalTime[0]); i++) {
		if (temp2 <= probabilityVehicleArrivalTime[i]) {
			interArrivalTime = i + temp;
			break;
		}
	}

	temp = (double)(rand()) / RAND_MAX;
	interServiceTime = 1.0 + temp * 3.0; // 1 <= x < 4

	temp = (double)(rand()) / RAND_MAX;
	double rateOfRights = 78.0 / 130.0; // num right turns / total vehicles
	if (temp <= rateOfRights)
		isTurningRight = true;
	else
		isTurningRight = false;

	if (isTurningRight) { //turning right, calculate service time
		temp = (double)(rand()) / RAND_MAX;
		temp2 = 1 + temp * 78; // 1 <= x < 79
		int probabilityRights[] = { 19, 34, 49, 56, 59, 65, 69, 71, 71, 71, 72, 73, 74, 74, 74, 74,
							74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 77, 77, 80 };
		for (int i = 0; i < sizeof(probabilityRights) / sizeof(probabilityRights[0]); i++) {
			if (temp2 <= probabilityRights[i]) {
				serviceTime = i + temp + .5;
				break;
			}
		}
	}
	else { //turning left, calculate service time
		temp = (double)(rand()) / RAND_MAX;
		temp2 = 1 + temp * 52; // 1 <= x < 53
		int probabilityLefts[] = { 4,12,18,20,20,22,23,25,27,30,32,34,35,37,38,38,38,38,40,41,41,41,
			41,42,44,44,45,45,46,48,48,48,49,49,49,49,49,49,49,50,50,50,50,50,50,50,50,50,51,51,51,51,
			51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,54 };
		for (int i = 0; i < sizeof(probabilityLefts) / sizeof(probabilityLefts[0]); i++) {
			if (temp2 <= probabilityLefts[i]) {
				serviceTime = i + temp + .25;
				break;
			}
		}
	}
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
	cout << "Elapsed Arrival Time	: " << elapsedArrivalTime << endl;
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

int main() {
	srand(time(NULL));

	const int numVehicles = 130;
	double d_hat = 0.0; // average delay in the queue
	double q_hat = 0.0; // average time in the queue
	double w_hat = 0.0; // average wait time in queue
	double integralB = 0.0; // when the queue is not being used
	double totalTime = 0.0; // total time of the entire simulation run
	double avgServiceTimeRights = 0.0; // average service time for right turns
	double avgServiceTimeLefts = 0.0; // average service time for left turns
	int numRights = 0;
	deque<Vehicle> vehiclesQ;

	cout << "Welcome to our North Campus Drive Intersection Simulation!" << endl << endl;

	for (int i = 0; i < numVehicles; i++) { // run simulation
		Vehicle currentVehicle;

		if (currentVehicle.getIsTurningRight()) { // if vehicle is making right turn
			avgServiceTimeRights += currentVehicle.getServiceTime();
			numRights++;
		}
		else { // vehicle is making left turn
			avgServiceTimeLefts += currentVehicle.getServiceTime();
		}

		if (vehiclesQ.empty()) { // no cars in queue
			integralB += currentVehicle.getInterArrivalTime(); // time not being used
			totalTime, integralB += currentVehicle.getInterArrivalTime(); // advance time
			currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
			currentVehicle.setInterServiceTime(0.0); // there is no interservice time when no cars in queue
			vehiclesQ.push_back(currentVehicle); // add vehicle to queue
		}

		else { // cars in queue
				// calculate how long the front car has been already waiting at the front of the queue
			float frontServiceTimeLeft = vehiclesQ.front().getServiceTime() - (totalTime - vehiclesQ.front().getElapasedArrivalTime() - vehiclesQ.front().getDelayTime());

			if ((currentVehicle.getInterArrivalTime()) < frontServiceTimeLeft) { // current car reaches queue before front car is serviced
				float d; //calculate current vehicle's delay time
				if (vehiclesQ.size() == 1) // if there's only one car in queue
					d = frontServiceTimeLeft + currentVehicle.getInterServiceTime();
				else // if there are 2 or more cars in queue
					d = vehiclesQ.back().getDelayTime() + vehiclesQ.back().getServiceTime() + currentVehicle.getInterServiceTime();
				currentVehicle.addDelayTime(d);

				d_hat += d;
				w_hat += d + currentVehicle.getServiceTime();

				totalTime += currentVehicle.getInterArrivalTime(); // advance time
				currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
				vehiclesQ.push_back(currentVehicle); // add vehicle to queue
			}

			else { // front car is serviced before current car reaches queue
				vehiclesQ.pop_front();
				if (vehiclesQ.empty()) { // queue is empty
					integralB += currentVehicle.getInterArrivalTime(); // time not being used
					totalTime += currentVehicle.getInterArrivalTime(); //advance time
					currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
					currentVehicle.setInterServiceTime(0.0); // there is no interservice time when no cars in queue
					vehiclesQ.push_back(currentVehicle); // add vehicle to queue
				}
				else { // queue is not empty
					// car entering queue before front car is serviced
					if (currentVehicle.getInterArrivalTime() < vehiclesQ.front().getInterServiceTime() + vehiclesQ.front().getServiceTime()) {
						float d; //calculate current vehicle's delay time
						if (vehiclesQ.size() == 1) // if there's only one car in queue
							d = vehiclesQ.front().getInterServiceTime() + vehiclesQ.front().getServiceTime() + currentVehicle.getInterServiceTime();
						else // if there are 2 or more cars in queue
							d = vehiclesQ.back().getDelayTime() + vehiclesQ.back().getServiceTime() + currentVehicle.getInterServiceTime();
						currentVehicle.addDelayTime(d);

						d_hat += d;
						w_hat += d + currentVehicle.getServiceTime();

						totalTime += currentVehicle.getInterArrivalTime(); //advance time
						currentVehicle.setElapasedArrivalTime(totalTime); // calculate time the vehicle enters the queue in the simulation
						vehiclesQ.push_back(currentVehicle); // add vehicle to queue
					}
					else { // car entering queue after front car is serviced
						float eventTimeBeforeNextArrival = frontServiceTimeLeft; // time advanced since first car was popped above
						float nextArrivalTime = currentVehicle.getInterArrivalTime();

						while (eventTimeBeforeNextArrival < nextArrivalTime) { // keep moving cars up and popping cars until next arrival time
							if (!vehiclesQ.empty()) {
								eventTimeBeforeNextArrival += vehiclesQ.front().getServiceTime();
								if (eventTimeBeforeNextArrival <= nextArrivalTime) {
									eventTimeBeforeNextArrival += vehiclesQ.front().getServiceTime();
									if (eventTimeBeforeNextArrival < nextArrivalTime) {
										vehiclesQ.pop_front();
									}
								}
							}
							else {
								eventTimeBeforeNextArrival = 99999.9; // to break out of loop
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
		cout << "Cars in queue		: " << vehiclesQ.size() << endl << endl;
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

	// calculations
	d_hat = d_hat / numVehicles;
	w_hat = w_hat / numVehicles;
	avgServiceTimeRights = avgServiceTimeRights / numRights;
	avgServiceTimeLefts = avgServiceTimeLefts / (numVehicles - numRights);

	cout << "Calculations in seconds, " << numVehicles << " cars: " << endl;
	cout << "Total time	T(n)	: " << totalTime << endl;
	cout << "Avg Delay d<hat>	: " << d_hat << endl;
	cout << "Avg Wait w<hat>		: " << w_hat << endl;
	cout << "Queue not used		: " << integralB << endl;
	cout << "Avg Service Time Rights : " << avgServiceTimeRights << endl;
	cout << "Avg Service Time Lefts	: " << avgServiceTimeLefts << endl;

	cin.get();
	cin.get();
	return 0;
}
