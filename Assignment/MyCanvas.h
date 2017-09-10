#ifndef MyCanvas_h
#define MyCanvas_h

#include "Canvas.h"




class MyCanvas : public Canvas
{
public:
    MyCanvas();
    virtual ~MyCanvas();
    void display() override;
    void onKeyboard(unsigned char key, int x, int y) override;
    void onMouseButton(int button, int state, int x, int y) override;
	
	
};

#endif // MyCanvas_h
