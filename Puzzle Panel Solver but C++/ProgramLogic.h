#pragma once

#include <string>
#include <vector>

// this probably isn't good pracice, but typing out a vector of char vectors is both ugly and time consuming
#define cvec2d std::vector<std::vector<char>>

static class ProgramLogic
{
	// public functions
public:
	// needs a default value, and it doesn't matter what it is as long as it can run atleast once, so i did INT_MAX just to make sure
	static void fillBoard(cvec2d& vector, int length = INT_MAX);
	static void displayVector(cvec2d vector);
	static cvec2d logic(cvec2d startBoard, cvec2d endBoard, int numberOfMoves);

	// private functions
private:
	static void convertFromString(cvec2d& vector, std::string convertString);
	static cvec2d checkSpaces(cvec2d board, int x, int y);
};