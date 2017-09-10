
#include "MyCanvas.h"
#include <iostream>


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
		
		drawLine(line);
		drawCircle(actualCircle.center.x, actualCircle.center.y, static_cast<GLuint>(actualCircle.radius), 127, 0, 0);
		drawCircle(innerCircle.center.x, innerCircle.center.y, static_cast<GLuint>(innerCircle.radius), 0, 127, 0);
		drawCircle(outerCircle.center.x, outerCircle.center.y, static_cast<GLuint>(outerCircle.radius), 0, 127, 0);

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
		switch (mode) {
		case problem::problem1:
			switch (mouseClickLastState)
			{
			case GLUT_UP:
				switch (state)
				{
				case GLUT_DOWN:
					line.start.x = x;
					line.start.y = y;
					line.end.x = x;
					line.end.y = y;
					squareGrid.clearGrid();
					actualCircle.radius = innerCircle.radius = outerCircle.radius = 0;
					mouseClickLastState = GLUT_DOWN;
					
					break;
				case GLUT_UP: // not possible
					break;
				}
			case GLUT_DOWN:
				switch (state)
				{
				case GLUT_UP:
					line.end.x = x;
					line.end.y = y;
					mouseClickLastState = GLUT_UP;
					drawNearestCircles(state);
					
					break;
				case GLUT_DOWN: // not possible
					break;
				}
			}
			break;
		case problem::problem2:
			if (state == GLUT_DOWN) {				
				squareGrid.toggleGridPoint(Point(x, y));
			}
			break;
		}

	}
	
	refresh();
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
