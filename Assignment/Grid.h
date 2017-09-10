#ifndef Grid_h
#define Grid_h
#include <iostream>
#include <vector>
#include "Util.h"
#include "SubjectAndObserver.h"
using namespace std;

class SquareGrid: public Subject{

public:
	int dots; // number of points
	float pitch;
	GridPoint start, end;
	Color colorForOn, colorForOff;
	vector<Observer*> observers;
	vector<vector<GridPoint>> gridPoints;

	SquareGrid();
	SquareGrid(int, GridPoint, GridPoint,  Color&, Color&);
	void toggleGridPoint(Point);
	void clearGrid();
	void init(int, GridPoint, GridPoint, Color&, Color&);
	void reshape(GridPoint, GridPoint);
	void notifyObservers();
	void registerObserver(Observer*);
	void removeObserver(Observer*);
};

#endif