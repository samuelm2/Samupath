#include "pch.h"
#include "MidpointComparer.h"


MidpointComparer::MidpointComparer(int d, double m) : dim(d), midpoint(m)
{
}

bool MidpointComparer::operator()(const BVHObjectInfo & a) const
{
	return a.center[dim] < midpoint;
}

MidpointComparer::~MidpointComparer()
{

}
