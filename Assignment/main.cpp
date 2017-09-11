#include "MyCanvas.h"
#include "Grid.h"



int main(int argc, char** argv)
{
    // Initialize GLUT with command line arguments
    glutInit(&argc, argv);
    // Create a canvas for the coding challenge
    MyCanvas* canvas = new MyCanvas();
	//SquareGrid * squareGrid = new SquareGrid();
    canvas->create(400, 400, "C++ Coding Challenge");
	//initialize the grid for certain count of gridPoints
	canvas->initGrid(20);
	// Run the GLUT event loop
    glutMainLoop();
	
    return 0;
}
