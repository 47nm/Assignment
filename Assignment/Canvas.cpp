
#include "Canvas.h"
#include <cmath>
#include<typeinfo>

std::unique_ptr<Canvas> Canvas::_instance;

Canvas::Canvas()
: _width(0)
, _height(0)
{
	
	mouseClickLastState = GLUT_UP;
	mode = problem::problem1;
}

Canvas::~Canvas()
{
}

void Canvas::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas::swapBuffers()
{
    glutSwapBuffers();
}

void Canvas::drawPoint(GLint cx, GLint cy, GLubyte red, GLubyte green, GLubyte blue)
{
    cy = _height - cy;
    glColor3ub(red, green, blue);
    glBegin(GL_POINTS);
    glVertex2f(cx + 0.5f, cy + 0.5f);
    glEnd();
}

void Canvas::drawCircle(GLint cx, GLint cy, GLuint radius, GLubyte red, GLubyte green, GLubyte blue)
{
	if ((float)radius < 0.4)//point size
		return;
    static const int numSlices = 72;
    static const GLfloat deltaAngle = 2.0f * std::atan2f(0.0f, -1.0f) / numSlices;
    cy = _height - cy;
    glColor3ub(red, green, blue);
    glBegin(GL_LINE_LOOP);
    GLfloat angle = 0.0f;
    for (int i = 0; i < numSlices; ++i, angle += deltaAngle) {
        glVertex2f(cx + 0.5f + radius * std::cosf(angle), cy + 0.5f + radius * std::sinf(angle));
    }
    glEnd();
}
void Canvas::drawNearestCircles(int state) {
	actualCircle.radius = line.length();
	actualCircle.center = innerCircle.center = outerCircle.center = line.start;
	int radiusOfInnerCircle = 0.0, radiusOfOuterCircle = 0.0;
	
	if (state == GLUT_UP && (float)actualCircle.radius > 0.4) {
		markNearestGridPointsToCircle(squareGrid, Circle(Point(line.start.x, line.start.y), actualCircle.radius), radiusOfInnerCircle, radiusOfOuterCircle);
		if (radiusOfInnerCircle > 0.0 && radiusOfInnerCircle < actualCircle.radius*actualCircle.radius) {
			innerCircle.radius = radiusOfInnerCircle;
		}
		if (radiusOfOuterCircle > 0.0) {
			outerCircle.radius = radiusOfOuterCircle;
		}
	}
}
//change this 
void Canvas::drawGrid() {
	Color color;
	for (auto row : squareGrid->gridPoints) {
		for(auto cell: row){
			if (cell.state == GridPoint::STATE_OFF) {
				color = squareGrid->colorForOff;
			}
			else {
				color = squareGrid->colorForOn;
			}
			drawPoint(cell.x, cell.y, color.red, color.green, color.blue);
		}
	}

}
void Canvas::drawLine(Line & _line, GLubyte red, GLubyte green, GLubyte blue)
{
	if (_line.length() < 1.0)
		return;
	glColor3ub(red, green, blue);
	glBegin(GL_LINES);
	glVertex2i(_line.start.x, _height - _line.start.y);
	glVertex2i(_line.end.x, _height - _line.end.y);
	glEnd();

}
void Canvas::initGrid(int dots) {
	Color colorForOff(127, 127, 127);
	Color colorForOn(0, 0, 127);
	squareGrid->init(dots, GridPoint(GridPoint::STATE_OFF, 0, 0), 
		GridPoint(GridPoint::STATE_OFF, _width, _height), colorForOn, colorForOff);
	squareGrid->registerObserver(this);
	
}
void Canvas::refresh()
{
    glutPostRedisplay();
}

void Canvas::reshape(GLuint width, GLuint height)
{
    _width = width;
    _height = height;
    glViewport(0, 0, _width, _height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, _width, 0, _height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Canvas::reshapeOtherProperties(GLuint width, GLuint height) {
	
	squareGrid->reshape(GridPoint(GridPoint::STATE_OFF, 0, 0),
		GridPoint(GridPoint::STATE_OFF, width, height));
	//currently clearing other objects, draw them again after resize.
	//Instead of below code scaling can be applied for resizing.
	line.end.x = line.start.x;
	line.end.y = line.start.y;
	innerCircle.radius = outerCircle.radius = actualCircle.radius = 0;
	squareGrid->clearGrid();

	squareGrid->notifyObservers();
}
void Canvas::onMouseDrag(int x, int y)
{
	if (mouseClickLastState == GLUT_DOWN)
	{
		line.end.x = x;
		line.end.y = y;
		drawNearestCircles(GLUT_DOWN);
		refresh();
	}
}
Canvas& Canvas::GetInstance()
{
    return *_instance.get();
}

void Canvas::SetInstance(Canvas* instance)
{
    _instance.reset(instance);
}

void DisplayFunc()
{
    Canvas::GetInstance().display();
}

void ReshapeFunc(int width, int height)
{
    Canvas::GetInstance().reshape(width, height);
	Canvas::GetInstance().reshapeOtherProperties(width, height);
}

void MouseFunc(int button, int state, int x, int y)
{
    Canvas::GetInstance().onMouseButton(button, state, x, y);
}
void MouseDrag(int x, int y)
{
	Canvas::GetInstance().onMouseDrag(x, y);
}


void KeyboardFunc(unsigned char key, int x, int y)
{
    Canvas::GetInstance().onKeyboard(key, x, y);
}

void Canvas::create(GLuint width, GLuint height, const std::string& title)
{
    static const GLfloat pointSize = 4.0f;
    static const GLfloat lineWidth = 1.3f;
    static const GLfloat backColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    _width = width;
    _height = height;
    glutInitWindowSize(_width, _height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(title.c_str());
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glClearColor(backColor[0], backColor[1], backColor[2], backColor[3]);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(pointSize);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(lineWidth);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(DisplayFunc);
    glutReshapeFunc(ReshapeFunc);
    glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseDrag);
	
	this->createMenu();
    Canvas::SetInstance(this);
	
}
void Menu(int x) {
	Canvas::GetInstance().setMode(x);

}
void Canvas::createMenu() {
	
	glutCreateMenu(Menu);
	glutAddMenuEntry("Problem 1",  problem::problem1);
	glutAddMenuEntry("Problem 2",  problem::problem2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void Canvas::setMode(int x) {
	mode = static_cast<problem>(x);
	this->refresh();
}
void Canvas::update(Subject *obj)  {
	if (string(typeid(*obj).name()).compare("SquareGrid")) {
		drawGrid();
		refresh();
	}
}
