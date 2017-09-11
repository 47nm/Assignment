#pragma once
#ifndef GridUtil_h
#define GridUtil_h
#include "Grid.h"
void markNearestGridPointsToCircle(SquareGrid&,const Circle , int&, int&);

Circle equateBestFitCircle(SquareGrid&);

#endif