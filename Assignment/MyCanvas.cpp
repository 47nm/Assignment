
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
	drawLine();
	drawCircle(line.start.x, line.start.y, static_cast<GLuint>(line.length()), 127, 0, 0);
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
