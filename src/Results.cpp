#include "Results.h"

Results::Results(int *distance, int *previous)
{
	this->distance = distance;
	this->previous = previous;
}

int* Results::getDistances(){
	return this->distance;
}

int* Results::getPreviouses(){
	return this->previous;
}

Results::~Results()
{
	//dtor
}
