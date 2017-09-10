
#include "MyCanvas.h"
#include <iostream>
#include "GridUtil.h"

MyCanvas::MyCanvas()
{
}

MyCanvas::~MyCanvas()
{
}


void MyCanvas::display()
{
    // Clear the canvas
    clear();
    // -------------------------------------------------------------------------------------------
    // Draw a gray point in the middle of the canvas
    //drawPoint(_width / 2, _height / 2, 127, 127, 127);
    // Draw a red circle on the canvas
    //drawCircle(_width / 3, _height / 3, 50, 127, 0, 0);
	// Draw a grid on the canvas
	if (mode == problem::problem1) {
		
		drawLine();
		int radius = line.length();
		int radiusOfInnerCircle = 0.0, radiusOfOuterCircle = 0.0;
		drawCircle(line.start.x, line.start.y, static_cast<GLuint>(radius), 127, 0, 0);
		squareGrid.clearGrid();//clear last time drawn circles
		if (this->mouseClickState == GLUT_UP) {
			markNearestGridPointsToCircle(squareGrid, Circle(Point(line.start.x, line.start.y), radius), radiusOfInnerCircle, radiusOfOuterCircle);
			if (radiusOfInnerCircle > 0.0 && radiusOfInnerCircle < radius*radius) {
				drawCircle(line.start.x, line.start.y, static_cast<GLuint>(radiusOfInnerCircle), 0, 127, 0);
			}
			if (radiusOfOuterCircle > 0.0) {
				drawCircle(line.start.x, line.start.y, static_cast<GLuint>(radiusOfOuterCircle), 0, 127, 0);
			}
		}
		

	}
	else if (mode == problem::problem2) {
		//select points, create a function for selection of point in grid class 
		//if pressed g draw best fir circle 
			//bestFirCircle(grid);
		//if pressed c clear grid
	}
	
	drawGrid();

    // -------------------------------------------------------------------------------------------
    // Make changes appear on screen
    swapBuffers();
}

void MyCanvas::onMouseButton(int button, int state, int x, int y)
{

    // Process mouse button events.
    switch (button) {
    case GLUT_LEFT_BUTTON:
        std::cout << "Canvas::onMouseButton: " << state << ", " << x << ", " << y << std::endl;
		switch (mouseClickState)
		{
			case GLUT_UP:
				switch (state)
				{
					case GLUT_DOWN:
						line.start.x = x;
						line.start.y = y;
						mouseClickState = GLUT_DOWN;
						break;
					case GLUT_UP: // not possible
					default:
						break; 
				}
			case GLUT_DOWN:
				switch (state)
				{
				case GLUT_UP:
					line.end.x = x;
					line.end.y = y;
					mouseClickState = GLUT_UP;
					refresh();
					break;
				case GLUT_DOWN: // not possible
				default:
					break; 
				}
			default:
				break;
		}

    default:
        break;
    }
	
}

void MyCanvas::onKeyboard(unsigned char key, int x, int y)
{
    // Process keyboard events.
    std::cout << "Canvas::onKeyboard: '" << key << "', " << x << ", " << y << std::endl;
    switch (key) {
    case 27: // ESC
        exit(0);
        break;
    default:
        break;
    }
    refresh();
}
