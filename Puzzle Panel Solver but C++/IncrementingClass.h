#pragma once

#include <string>
#include <vector>

// this probably isn't good pracice, but typing out a vector of int vectors is both ugly and time consuming
#define ivec2d std::vector<std::vector<int>>

class IncrementingClass
{
	// public functions
public:
	IncrementingClass(int numberToCountTo, int length);

	void Increment();

	ivec2d getCurrentIncrement();

	// private functions
private:
	int numberToCountTo;
	int length;

	ivec2d currentIncrement;
};