// Lab9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <list>
#include <time.h>
#include <string>
/*
Summary of the program:
As per the instruction, we are not using the double ended queue for this task.

After taking the inputs from user for no.of.rounds, percentages for push & pop - we are checking few conditions.

If at the first round, new element is not added to the queue, and pop operation is triggered based on the random percentage generated, then pop operation would give an error hence we need to pop out the element only if the queue is not empty.

Example:
number of rounds : 3
percentage for push : 50
percentage for pop : 35

random number generated for push : 75 our condition did not meet, hence no push happens
random number generated for pop : 27 hence pop should happen but the buffer is empty.


http://www.chegg.com/homework-help/questions-and-answers/requirements-c-note-deque-stl-container-allowed-queue-queue-first-first-fifo-data-structur-q25304447
*/

using namespace std;

int main()
{
	/*
	variables:
	rounds - no.of.rounds of simulation
	percentPush - number taken as input for chance of inserting into the queue
	percentPop - number taken as input for chance of popping the front element from queue
	num - random number between 1 & 1000 generated everytime to push
	percent - random percent generated between 1 & 100 to compare with percentPush or percentPop
	status_push & status_pop - these are the variables to show to console about the triggers of push/pop

	avg is the average length of the buffer after ith rounds
	avg_prev is the avg of previous round, for 0th round we take it to be zero.

	we are creating queue with list as its stl container and elements to be int, also creating a temporary queue.

	defining srand so that the random number changes with time

	*/


	int rounds, percentPush, percentPop, num, percent, status_push, status_pop;
	double avg = 0, a_prev;
	queue<int, list<int>> que, temp;
	srand(time(NULL));


	//taking input from user and validating it against any string input instead of integer.

	cout << "Enter the number of rounds for the simulation:";
	while (!(cin >> rounds))
	{
		//when the input fails, it clears the last cin and for completion of line of the given input, asking again to enter valid input.
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Please enter valid input: ";
	}

	cout << "Enter percentage chance to put a random number at the end of buffer:";
	while (!(cin >> percentPush))
	{
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "\nPlease enter valid input: ";
	}

	cout << "Enter percentage chance to take out number from the front of buffer:";
	while (!(cin >> percentPop))
	{
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Please enter valid input: ";
	}

	//iterating for the number of rounds.
	for (int i = 1; i <= rounds; i++)
	{
		status_push = 0;
		status_pop = 0;
		a_prev = avg;

		//random number in range 1 to 1000
		num = rand() % 1000 + 1;
		cout << "Random Number Chosen is: " << num << endl;

		//random number in range 1 to 100
		percent = rand() % 100 + 1;

		//comparing with user provided values and pushing if it obeys
		if (percent <= percentPush)
		{
			que.push(num);
			status_push++; //incrementing status indicating push happened
		}

		//comparing with user provided values and popping if it obeys and queue is not empty
		percent = rand() % 100 + 1;
		if (percent <= percentPop && !que.empty())
		{
			que.pop();
			status_pop++; //decrementing status indicating pop happened
		}


		//temp queue is filled with our queue
		temp = que;
		cout << "\nRound " << i << endl;
		if (status_push && status_pop)
			cout << "Both push & pop triggered.\n";
		else if (status_push)
			cout << "Only push triggered.\n";
		else if (status_pop)
			cout << "Only pop triggered.\n";
		else
			cout << "Neither push nor pop triggered.\n";

		//printing the elements of queue using temp queue
		cout << "Elements of the queue from front are: ";
		while (!temp.empty())
		{
			cout << temp.front() << ". ";
			temp.pop();
		}
		cout << endl;

		//printing length of the buffer after every round.
		cout << "Length of the buffer after round " << i << " is: " << que.size() << endl;;


		//calculating average as per the given formula and printing it.
		avg = (a_prev*(i - 1) + que.size()) / i;
		cout << "Average length of the queue afer round " << i << " is: " << avg << endl << endl;

		cout << "Press '1' and then 'Enter' to begin next round." << endl;
		string pause;

		cin >> pause;
	}
	return 0;
}