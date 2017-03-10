#include <iostream>
#include <math.h>

int nextEventType, numCustsDelayed, numDelaysRequired, numEvents, numInQ, serverStatus;

float areaNumInQ, areaServerStatus, meanInterArrival, meanService, simTime,
timeLastEvent, totalOfDelays;
float timeArrival[101], timeNextEvent[3];

FILE *infile, *outfile;

// prototypes:

void initialize(void);
void timing();
void arrive();
void depart();
void report();
void updateTimeAvgStats();
float expon(float mean);

/*
#define const int Q_LIMIT 100;
#define BUSY  1;
#define IDLE  0;
*/

const int Q_LIMIT = 100;
int BUSY = 1;
int IDLE = 0;

using namespace std;
int main()
{

	infile = fopen("mm1in.txt", "r");
	outfile = fopen("mm1out.txt", "w");

	numEvents = 2;

	fscanf(infile, "%f %f %d", &meanInterArrival, &meanService, &numDelaysRequired);

	fprintf(outfile, "Single server queueing system\n\n");
	fprintf(outfile, "Mean Interarrival Time %11.3f minutes\n\n", meanInterArrival);
	fprintf(outfile, "Mean Service Time %16.3f minutes\n\n", meanService);
	fprintf(outfile, "Number of Customers%14d\n\n", numDelaysRequired);

	initialize();

	while (numCustsDelayed < numDelaysRequired)
	{
		timing();
		updateTimeAvgStats();
		switch (nextEventType)
		{
		case 1:
			arrive();
			break;
		case 2:
			depart();
			break;
		}
	}

	report();
	fclose(infile);
	fclose(outfile);

	cin.get();
	//cin.get();
	return 0;
}

void initialize(void)
{
	simTime = 0;

	serverStatus = IDLE;
	numInQ = 0;
	timeLastEvent = 0.0;

	numCustsDelayed = 0;
	totalOfDelays = 0.0;
	areaNumInQ = 0.0;
	areaServerStatus = 0.0;

	timeNextEvent[1] = simTime + expon(meanInterArrival);
	timeNextEvent[2] = 1.0e+30;

}

void timing(void)
{
	int i;
	float minTimeNextEvent = 1.0e+29;
	nextEventType = 0;

	for (i = 1; i <= numEvents; ++i)
	{
		if (timeNextEvent[i] < minTimeNextEvent)
		{
			minTimeNextEvent = timeNextEvent[i];
			nextEventType = i;
		}
	}

	if (nextEventType == 0)
	{
		fprintf(outfile, "\nEvent list empty at time %f", simTime);
		exit(1);

	}

	simTime = minTimeNextEvent;


}

float expon(float mean)
{
	return -mean * log((double)(rand()) / RAND_MAX);
	//return -mean * log(lcgrabd(1));
}

void report(void)
{
	fprintf(outfile, "\n\nAverage Delay in queue%11.3f minutes\n\n", totalOfDelays / numCustsDelayed);
	fprintf(outfile, "Average number in queue%10.3f \n\n", areaNumInQ / simTime);
	fprintf(outfile, "Server Utilitation%15.3f \n\n", areaServerStatus / simTime);
	fprintf(outfile, "Time Simulation ended%12.3f minutes\n\n", simTime);



}

void arrive(void)
{
	float delay;
	timeNextEvent[1] = simTime + expon(meanInterArrival);

	if (serverStatus == BUSY)
	{
		numInQ++;
		if (numInQ > Q_LIMIT)
		{
			fprintf(outfile, "\nOverflow of the array timeArrival  at");
			fprintf(outfile, " time %f", simTime);
			exit(2);
		}
		timeArrival[numInQ] = simTime;
	}
	else
	{
		delay = 0.0;
		totalOfDelays += delay;

		numCustsDelayed++;
		serverStatus = BUSY;
		timeNextEvent[2] = simTime + expon(meanService);

	}
}

void depart(void)
{
	int i;
	float delay;
	if (numInQ == 0)
	{
		serverStatus = IDLE;
		timeNextEvent[2] = 1.0e+30;
	}
	else
	{
		numInQ--;
		delay = simTime - timeArrival[1];
		totalOfDelays += delay;

		numCustsDelayed++;
		timeNextEvent[2] = simTime + expon(meanService);

		for (i = 1; i <= numInQ; i++)
			timeArrival[1] = timeArrival[i + 1];

	}
}

void updateTimeAvgStats(void)
{
	float timeSinceLastEvent;
	timeSinceLastEvent = simTime - timeLastEvent;
	timeLastEvent = simTime;
	areaNumInQ += numInQ* timeSinceLastEvent;
	areaServerStatus += serverStatus * timeSinceLastEvent;

}
