#include "Grid.h"
#include <algorithm>

SquareGrid ::SquareGrid(): gridPoints(NULL), start(), end(){
	dots = 0;
	pitch = 0.0;
	
}
SquareGrid::SquareGrid(int _dots, GridPoint _start, GridPoint _end, Color& _colorForOn, Color& _colorForOff) {
	init(_dots, _start, _end, _colorForOn, _colorForOff);
	
}

void SquareGrid::toggleGridPoint(Point p)
{
	float threshold = 4;//radius of point;
	int indexOfX, indexOfY;
	indexOfX = static_cast<int>(round((p.x - start.x) / pitch));
	indexOfY = static_cast<int>(round((p.y - start.y) / pitch));

	if (indexOfX < dots && indexOfY < dots && indexOfX >=0 && indexOfY >=0
			&& this->gridPoints[indexOfX][indexOfY].distance(p) < threshold) {
		this->gridPoints[indexOfX][indexOfY].toggle();
		this->notifyObservers();
	}

}

void SquareGrid::clearGrid() {
	for (auto& row: gridPoints) {
		for (auto& col: row) {
			col.setOff();
		}
	}
	this->notifyObservers();
}

void SquareGrid::init(int _dots, GridPoint _start, GridPoint _end, Color& _colorForOn, Color& _colorForOff)
{
	dots = _dots;
	start = _start;
	int dx, dy;
	dx = std::abs(_start.x - _end.x);
	dy = std::abs(_start.y - _end.y);
	colorForOn = _colorForOn;
	colorForOff = _colorForOff;

	if (_start.x > _end.x || _start.y > _end.y) {
		//throw error;
	}
	//decide on end
	if(dx < dy){
		end.x = _end.x;
		pitch = dx / dots;
		end.y = _end.y - (dy - dx);
	}
	else {
		end.y = _end.y;
		pitch = dy / dots;
		end.x = _end.x - (dy - dx);
	}
	
	

	gridPoints.resize(dots, vector<GridPoint>(dots));
	GridPoint temp = start;
	for (int i = 0; i < dots; i++) {
		temp.y = start.y;
		for (int j = 0; j < dots; j++) {
			gridPoints[i][j] = temp;
			temp.y = pitch + temp.y;
		}
		temp.x = pitch + temp.x;
	}
	
}

void SquareGrid::reshape(GridPoint newStart, GridPoint newEnd)
{
	int dx, dy;
	start = newStart;
	dx = std::abs(newStart.x - newEnd.x);
	dy = std::abs(newStart.y - newEnd.y);
	
	//decide on end
	if (dx < dy) {
		end.x = newEnd.x;
		pitch = dx / dots;
		end.y = newEnd.y - (dy - dx);
	}
	else {
		end.y = newEnd.y;
		pitch = dy / dots;
		end.x = newEnd.x - (dy - dx);
	}

	GridPoint temp = start;
	for (int i = 0; i < dots; i++) {
		temp.y = start.y;
		for (int j = 0; j < dots; j++) {
			gridPoints[i][j].x = temp.x;
			gridPoints[i][j].y = temp.y;
			temp.y = pitch + temp.y;
		}
		temp.x = pitch + temp.x;
	}
	
}

	
void SquareGrid::notifyObservers() {
	for (auto observer : observers) {
		observer->update(this);
	}
}

void SquareGrid::registerObserver(Observer* observer)
{
	for (auto _observer : observers) {
		if (_observer == observer) {
			return;
		}
	}
	observers.push_back(observer);
}

void SquareGrid::removeObserver(Observer* observer)
{
	int removeIndex = -1;
	
	for (size_t i = 0; i < observers.size(); i++) {
		if (observers.at(i) == observer) {
			removeIndex = i;
			break;
		}
	}
	if (removeIndex != -1) {
		observers.erase(observers.begin()+ removeIndex);
	}
}
