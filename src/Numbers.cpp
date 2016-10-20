#include "Numbers.h"

#include "limits.h"
Numbers::Numbers()
{
	//ctor
}

Numbers::~Numbers()
{
	//dtor
}

bool Numbers::isAdditionisSafe(int a, int x) {
    if ((x > 0) && (a > INT_MAX - x)) return false;
    return true;
}
