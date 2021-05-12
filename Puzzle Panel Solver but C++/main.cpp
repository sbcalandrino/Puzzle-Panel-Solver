#include <iostream>

#include "ProgramLogic.h"

int main() 
{
	// try catch because im throwing exceptions
	try
	{
		// getting the starting board positions
		std::cout << "Start Panel: Please input 1's and 0's where the panels are on and off, separated by spaces" << std::endl;
		std::vector<std::vector<char>> startBoard;
		ProgramLogic::fillBoard(startBoard);

		// getting the ending board positions
		std::cout << "End Panel: Please input 1's and 0's where the panels are on and off, separated by spaces" << std::endl;
		std::vector<std::vector<char>> endBoard;
		ProgramLogic::fillBoard(endBoard, startBoard.size());

		// extra error checking
		if (startBoard.size() != endBoard.size())
			throw std::exception("Error: End board and start board are not the same size");

		// getting the number of moves that you can make
		std::cout << "Enter the amount of moves you can do" << std::endl;
		// this was the best way i know of to get an int from a char value
		char c_numberOfMoves;
		std::cin >> c_numberOfMoves;
		int numberOfMoves = c_numberOfMoves - '0';

		// starts the brute force solving using the boards and the number of moves
		cvec2d moves = ProgramLogic::logic(startBoard, endBoard, numberOfMoves);
		// displays the final vector into the console
		ProgramLogic::displayVector(moves);
	}
	catch (std::exception e)
	{
		// if there is an error, prints it to console
		std::cout << e.what() << std::endl;
	}

	// idk if system("pause") is good practice to use, but whatever
	system("pause");
	return 0;
}