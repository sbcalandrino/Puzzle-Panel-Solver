#include "ProgramLogic.h"
#include "IncrementingClass.h"
#include <iostream>

// fills a vector of vectors which represents the board, with input
// puzzle panel puzzles are always square, so length is also width of the 2d vector
void ProgramLogic::fillBoard(cvec2d& vector, int length)
{
	cvec2d board;
	for (int i = 0; i < length; i++)
	{
		std::string text;
		std::getline(std::cin, text);

		ProgramLogic::convertFromString(board, text);

		if (length == INT_MAX)
			length = board[i].size();
		else if (length != board[i].size())
			throw std::exception("Error: You inputted a row that wasn't the same length.");
	}

	vector = board;
}

// just displays the vector to the console
// separates columns by spaces and rows by a new line
void ProgramLogic::displayVector(cvec2d vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		for (int j = 0; j < vector[i].size(); j++)
			std::cout << vector[i][j] << ' ';

		std::cout << std::endl;
	}
}

// actual solving part of the program
cvec2d ProgramLogic::logic(cvec2d startBoard, cvec2d endBoard, int numberOfMoves)
{
	// it doesn't matter if i use startBoard.size() or endBoard.size(), they will always be the same size if the program gets to this point
	// the .size() will always be from startBoard from here on though, just for consistency
	IncrementingClass increment = IncrementingClass(startBoard.size(), numberOfMoves);
	
	// setting default value for the moves 2d vector
	cvec2d moves;
	for (int i = 0; i < startBoard.size(); i++)
	{
		std::vector<char> pushVector;

		for (int j = 0; j < startBoard[i].size(); j++)
		{
			pushVector.push_back('0');
		}

		moves.push_back(pushVector);
	}

	while (true)
	{
		// boolean to test if the puzzle is possible to solve
		// checking for this is at the bottom of the while loop
		bool possible = false;

		// increment number, basically a 2d vector of coordinates to use on the 2d vector below
		ivec2d moveAttempts = increment.getCurrentIncrement();
		cvec2d spacesCheck = startBoard;

		// actual solving loop
		for (int i = 0; i < moveAttempts.size(); i++)
		{
			int x = moveAttempts[i][0];
			int y = moveAttempts[i][1];

			// it is equaled to a function using it so it can get checked on the same board
			spacesCheck = checkSpaces(spacesCheck, x, y);
		}

		// checking if the solution is correct
		bool done = true;
		for (int i = 0; i < spacesCheck.size(); i++)
		{
			for (int j = 0; j < spacesCheck[i].size(); j++)
			{
				if (spacesCheck[i][j] != endBoard[i][j])
				{
					done = false;
					break;
				}
			}
		}

		if (done)
		{
			// if it is the solution, put '1' in all the coords of the increment number and break the while loop
			for (int i = 0; i < moveAttempts.size(); i++)
			{
				int x = moveAttempts[i][0];
				int y = moveAttempts[i][1];

				moves[x][y] = '1';
			}
			break;
		}
		else
		{
			// checking if the numbers in the increment number aren't filled up, to check if it is still possible
			for (int i = 0; i < moveAttempts.size(); i++)
				for (int j = 0; j < moveAttempts[i].size(); j++)
					if (moveAttempts[i][j] != startBoard.size() - 1)
						possible = true;

			// if it isn't actually possible, throw an exception
			if (!possible)
				throw std::exception("Error: Board isn't possible.");

			// increments the increment number by 1
			increment.Increment();
		}
	}

	return moves;
}

// hard coded all the ways that it can switch the adjacent panels
// this is extremely ugly
cvec2d ProgramLogic::checkSpaces(cvec2d board, int x, int y)
{
	cvec2d finished = board;

	if (x == 0 && y == 0)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x + 1][y] = board[x + 1][y] == '0' ? '1' : '0';
		finished[x][y + 1] = board[x][y + 1] == '0' ? '1' : '0';
		finished[x + 1][y + 1] = board[x + 1][y + 1] == '0' ? '1' : '0';
	}
	else if (x == 0 && y > 0 && y < board.size() - 1)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x + 1][y] = board[x + 1][y] == '0' ? '1' : '0';
		finished[x][y + 1] = board[x][y + 1] == '0' ? '1' : '0';
		finished[x + 1][y + 1] = board[x + 1][y + 1] == '0' ? '1' : '0';
		finished[x][y - 1] = board[x][y - 1] == '0' ? '1' : '0';
		finished[x + 1][y - 1] = board[x + 1][y] == '0' ? '1' : '0';
	}
	else if (x == 0 && y == board.size() - 1)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x + 1][y] = board[x + 1][y] == '0' ? '1' : '0';
		finished[x][y - 1] = board[x][y - 1] == '0' ? '1' : '0';
		finished[x + 1][y - 1] = board[x + 1][y - 1] == '0' ? '1' : '0';
	}
	else if (x > 0 && x < board[0].size() - 1 && y == 0)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x + 1][y] = board[x + 1][y] == '0' ? '1' : '0';
		finished[x][y + 1] = board[x][y + 1] == '0' ? '1' : '0';
		finished[x + 1][y + 1] = board[x + 1][y + 1] == '0' ? '1' : '0';
		finished[x - 1][y] = board[x - 1][y] == '0' ? '1' : '0';
		finished[x - 1][y + 1] = board[x - 1][y + 1] == '0' ? '1' : '0';
	}
	else if (x == board[0].size() - 1 && y == 0)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x - 1][y] = board[x - 1][y] == '0' ? '1' : '0';
		finished[x][y + 1] = board[x][y + 1] == '0' ? '1' : '0';
		finished[x - 1][y + 1] = board[x - 1][y + 1] == '0' ? '1' : '0';
	}
	else if (x == board[0].size() - 1 && y == board.size() - 1)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x - 1][y] = board[x - 1][y] == '0' ? '1' : '0';
		finished[x][y - 1] = board[x][y - 1] == '0' ? '1' : '0';
		finished[x - 1][y - 1] = board[x - 1][y - 1] == '0' ? '1' : '0';
	}
	else if (x == board[0].size() - 1 && y > 0 && y < board.size() - 1)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x - 1][y] = board[x - 1][y] == '0' ? '1' : '0';
		finished[x][y - 1] = board[x][y - 1] == '0' ? '1' : '0';
		finished[x - 1][y - 1] = board[x - 1][y - 1] == '0' ? '1' : '0';
		finished[x][y + 1] = board[x][y + 1] == '0' ? '1' : '0';
		finished[x - 1][y + 1] = board[x - 1][y + 1] == '0' ? '1' : '0';
	}
	else if (x > 0 && x < board[0].size() - 1 && y == board.size() - 1)
	{
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x - 1][y] = board[x - 1][y] == '0' ? '1' : '0';
		finished[x][y - 1] = board[x][y - 1] == '0' ? '1' : '0';
		finished[x - 1][y - 1] = board[x - 1][y - 1] == '0' ? '1' : '0';
		finished[x + 1][y] = board[x + 1][y] == '0' ? '1' : '0';
		finished[x + 1][y - 1] = board[x + 1][y - 1] == '0' ? '1' : '0';
	}
	else
	{
		finished[x - 1][y - 1] = board[x - 1][y - 1] == '0' ? '1' : '0';
		finished[x - 1][y] = board[x - 1][y] == '0' ? '1' : '0';
		finished[x][y - 1] = board[x][y - 1] == '0' ? '1' : '0';
		finished[x][y] = board[x][y] == '0' ? '1' : '0';
		finished[x + 1][y] = board[x + 1][y] == '0' ? '1' : '0';
		finished[x][y + 1] = board[x][y + 1] == '0' ? '1' : '0';
		finished[x + 1][y + 1] = board[x + 1][y + 1] == '0' ? '1' : '0';
		finished[x - 1][y + 1] = board[x - 1][y + 1] == '0' ? '1' : '0';
		finished[x + 1][y - 1] = board[x + 1][y - 1] == '0' ? '1' : '0';
	}

	return finished;
}

// removes the spaces from a string and puts it into a vector, which pushes it into a vector of char vectors
void ProgramLogic::convertFromString(cvec2d& vector, std::string convertString)
{
	std::vector<char> pushVector;

	for (int i = 0; i < convertString.length(); i++)
	{
		if (convertString[i] != '0' && convertString[i] != '1' && convertString[i] != ' ')
			throw std::exception("Error: You inputted a value that is not 1 or 0");

		if (convertString[i] != ' ')
			pushVector.push_back(convertString[i]);
	}

	vector.push_back(pushVector);
}