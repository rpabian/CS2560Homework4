#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Die
{
private:
	int m_sides;
	int value;
public:
	Die(int sides = 6)
	{
		unsigned seed = time(0);
		srand(seed);
		m_sides = sides;
	}
	void roll()
	{
		const int MIN_VALUE = 1;
		value = (rand() % (m_sides - MIN_VALUE + 1)) + MIN_VALUE;
	}
	int getSides() { return m_sides; }
	int getValue() { return value; }
};

int main()
{
	cout << "Game of 21!" << endl;
	int plyrInput = 1;
	int plyrValue = 0;
	int compValue = 0;
	Die plyrDie;
	Die compDie;

	while (plyrInput == 1 && plyrValue <= 21)
	{
		cout << "Do you want to roll the die?\n"
			<< "1 for Yes, 0 for No: ";
		cin >> plyrInput;
		if (plyrInput != 1)
			break;
		cout << "Rolling your opponents Die: ";
		compDie.roll();
		compValue += compDie.getValue();
		cout << "Rolling your Die: \n";
		plyrDie.roll();
		plyrValue += plyrDie.getValue();
		cout << "Die lands on: " << plyrDie.getValue() << "\n";
		cout << "Your total so far: " << plyrValue << endl;
	}

	if (plyrValue <= 21 && compValue <= 21)
	{
		if (plyrValue == compValue)
			cout << "Game is tied!";
		else if (plyrValue > compValue)
			cout << "You win!";
		else
			cout << "You lose!";
	}
	else if (plyrValue > 21 && compValue > 21)
		cout << "Game tied?";
	else if (plyrValue > 21)
		cout << "You lose!";
	else
		cout << "You win!";
	cout << "\nPlayer total: " << plyrValue << "\n"
		<< "Opponent total:" << compValue << endl;
}
