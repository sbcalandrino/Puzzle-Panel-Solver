#include "IncrementingClass.h"

// constructor for the class
// parameters: numberToCountTo is the size of the startBoard, length is the numberOfMoves
IncrementingClass::IncrementingClass(int numberToCountTo, int length)
{
	// setting private properties to the arguments passed in
	this->numberToCountTo = numberToCountTo;
	this->length = length;

	// sets the 2d vector to its lowest number so it can count up
	const std::vector<int> zero = { 0, 0 };
	for (int i = 0; i < length; i++)
		currentIncrement.push_back(zero);
}

/*
	i say directions for the 2d vector in these comments, this is what i mean
	lets say the class had the properties numberToCountTo = 4 and length = 2

	the 2d vector would look like this
	{ 0, 0 }
	{ 0, 0 }

	and it could go up to this
	{ 3, 3 }
	{ 3, 3 }

	indexes for these values are
	{ [0, 0], [0, 1] }
	{ [1, 0], [1, 1] }

	i say directions because that is the best way to i can think to describe it
*/

/* 
	increments the 2d vector by one

	the loop increments in this order
	{ 4, 3 }
	{ 2, 1 }
*/
void IncrementingClass::Increment()
{
	// increments the farthest down and right int in the 2d vector by 1
	currentIncrement[length - 1][1]++;

	// loops through all the elements in the 2d vector, from the bottom right to top left
	for (int i = length - 1; i >= 0; i--)
	{
		for (int j = 1; j >= 0; j--)
		{
			// if an element is equal to the numberToCountTo, it has to increment the next number
			if (currentIncrement[i][j] == numberToCountTo)
			{
				// if the x coord is equal to 0, you have to go up and right to increment the next number
				if (j == 0)
				{
					// if the y coord isn't at the top, set the element to 0 and increment the next number
					if (i != 0)
					{
						currentIncrement[i][j] = 0;
						currentIncrement[i - 1][j + 1]++;
					}
					// shouldn't ever be run in this program, as ProgramLogic::logic() checks before it can become an error
					else
					{
						throw std::exception("Error: Increment system went wrong somehow.");
					}
				}
				// else just increment the next number like normal
				else
				{
					currentIncrement[i][j] = 0;
					currentIncrement[i][j - 1]++;
				}
			}
		}
	}
}

// just returns the vector to check
ivec2d IncrementingClass::getCurrentIncrement()
{
	return currentIncrement;
}