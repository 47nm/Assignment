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
	float pitch; //distance between two adjacent grid point

	GridPoint start, end;
	Color colorForOn, colorForOff;
	vector<Observer*> observers; //vector of observers registered
	vector<vector<GridPoint>> gridPoints; //2d gridPoints
	static SquareGrid* squareGrid;
	
	//! get singleton instance of SquareGrid
	static SquareGrid* getInstance();
	//! get singleton instance of SquareGrid with specified configuration as parameters
	//! \param _dots	number of points in grid in one dimension
	//! \param _start	starting position of grid in window.
	//! \param _end		ending position of grid in window.
	//! \param _colorForOn	color for on state
	//! \param _colorForOff	color for off state
	static SquareGrid* getInstance(int, GridPoint, GridPoint, Color&, Color&);

	//! Toggle the state of grid point. On <==> Off
	//! \param Point the grid point whose state has to be toggered
	void toggleGridPoint(Point);
	//! Make all grid point state Off
	void clearGrid();
	//! Initialize the grid
	//! \param _dots	number of points in grid in one dimension
	//! \param _start	starting position of grid in window.
	//! \param _end		ending position of grid in window.
	//! \param _colorForOn	color for on state
	//! \param _colorForOff	color for off state
	void init(int, GridPoint, GridPoint, Color&, Color&);
	//! reshape the grid
	//! \param _start	starting position of grid in window.
	//! \param _end		ending position of grid in window.
	void reshape(GridPoint, GridPoint);


	void notifyObservers() override;
	void registerObserver(Observer*) override;
	void removeObserver(Observer*) override;
	//! destruct grid Object
	~SquareGrid();
private:
	
	SquareGrid();
	SquareGrid(int, GridPoint, GridPoint, Color&, Color&);

};

#endif