#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <GL/glut.h>

#include "Vector3.h"

class FrameBuffer : public Fl_Gl_Window 
{
private:
	void Set(int u, int v, unsigned int color);

public:
	unsigned int *pix;
	int w, h;
	FrameBuffer(int u0, int v0, int _w, int _h);
	void draw();
	void KeyboardHandle();
	int handle(int guievent);
	void SetBGR(unsigned int bgr);
	void SetGuarded(int u, int v, unsigned int color);
	void LoadTiff(char* fname);
	void SaveAsTiff(char* fname);
	
	//draw shapes
	void DrawRectangle(int u0, int v0, int u1, int v1, unsigned int color);
	void DrawCircle(int u0, int v0, int radius, unsigned int color);
};