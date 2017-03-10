#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
using namespace std;


int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
	srand (time(NULL));
	int probOne = (rand()% 900) + 100;
	int probTwo = (rand()% 201) * 5;
	double probThree = ((double)rand()/RAND_MAX)*2-1;
	double probFour = ((double)(rand()+1)/(RAND_MAX+2))*2-1;
	printf("%d\n%d\n%lf\n%lf", probOne,probTwo,probThree,probFour);
   	return 0;
}

