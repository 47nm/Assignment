#ifndef Canvas_h
#define Canvas_h

#include <string>
#include <memory>
#include "glut.h"
#include "Grid.h"
#include "GridUtil.h"
#include "SubjectAndObserver.h"


//! Canvas represents a 2D window with built-in support for drawing points and circles, as well as
//! receiving and processing window refresh, window resize, mouse input, and keyboard input events.
//! The canvas coordinate system origin is located in the upper left hand corner with the X axis 
//! pointing right and the Y axis pointing down.
class Canvas : public Observer
{
public:
    //! Default destructor.
    virtual ~Canvas();
    //! Create a canvas of a specific initial size displaying the given text string in the title bar.
    //! \param width    Initial canvas width in pixels.
    //! \param height   Initial canvas height in pixels.
    //! \param title    Canvas title string.
    void create(GLuint width, GLuint height, const std::string& title);

	void createMenu();

	void setMode(int);

	void update(Subject *);

	
	
    //! Receive window resize events.
    //! \param width    New window width in pixels.
    //! \param height   New window height in pixels.
    void reshape(GLuint width, GLuint height);
    //! Receive a window refresh event and redraw the entire canvas.
    virtual void display() = 0;
    //! Receive and process keyboard input events.
    //! \param key      Keyboard character.
    //! \param x        Mouse X coordinate in pixels.
    //! \param y        Mouse Y coordinate in pixels.
    virtual void onKeyboard(unsigned char key, int x, int y) = 0;
    //! Receive and process mouse input events.
    //! \param button   Which mouse button the event is generated for,
    //!                 one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
    //! \param state    Mouse button state, one of GLUT_UP or GLUT_DOWN.
    //! \param x        Mouse X coordinate in pixels.
    //! \param y        Mouse Y coordinate in pixels.
    virtual void onMouseButton(int button, int state, int x, int y) = 0;
	//! Receive window resize events.
	//! \param width    New window width in pixels.
	//! \param height   New window height in pixels.
	void reshapeOtherProperties(GLuint width, GLuint height);
	//todo:comment
	void onMouseDrag(int x, int y);

	//! Access the singleton canvas instance.
    static Canvas& GetInstance();
	void initGrid(int dots);
	void drawGrid();
	void drawLine(Line&, GLubyte red, GLubyte green, GLubyte blue);
	
protected:
    //! Default constructor, protected for singleton object.
    Canvas();
    //! Disable copy constructor for singleton object.
    Canvas(const Canvas&) = delete;
    //! Disable assignment operator for singleton object.
    Canvas& operator=(const Canvas&) = delete;
    //! Trigger a window refresh event to redraw the canvas.
    void refresh();
    //! Clear the canvas to the background color.
    void clear();
    //! Show the canvas on the screen.
    void swapBuffers();
    //! Draw a point on the canvas at the specified location using the given RGB color.
    //! \param cx       Point center X coordinate in pixels.
    //! \param cy       Point center Y coordinate in pixels.
    //! \param red      Red component of the RGB color (0-255).
    //! \param green    Green component of the RGB color (0-255).
    //! \param blue     Blue component of the RGB color (0-255).
    void drawPoint(GLint cx, GLint cy, GLubyte red, GLubyte green, GLubyte blue);
    //! Draw a circle on the canvas at the specified location with the given radius and RGB color.
    //! \param cx       Circle center X coordinate in pixels.
    //! \param cy       Circle center Y coordinate in pixels.
    //! \param radius   Circle radius in pixels.
    //! \param red      Red component of the RGB color (0-255).
    //! \param green    Green component of the RGB color (0-255).
    //! \param blue     Blue component of the RGB color (0-255).
    void drawCircle(GLint cx, GLint cy, GLuint radius, GLubyte red, GLubyte green, GLubyte blue);

	void drawNearestCircles(int);

    //! Set the singleton canvas instance.
    static void SetInstance(Canvas* instance);

	
protected:
    GLuint _width;
    GLuint _height;
    static std::unique_ptr<Canvas> _instance;
	SquareGrid *squareGrid;
	Line line;
	Circle actualCircle, outerCircle, innerCircle;
	int mouseClickLastState;
	problem mode;
	Color colorOfline, colorOfactualCircle, colorOfOuterAndInnerCircle;

};


#endif // Canvas_h
