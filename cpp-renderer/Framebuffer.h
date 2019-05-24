#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <GL/glut.h>

#include "Vector3.h"

class Framebuffer : public Fl_Gl_Window 
{
private:
	void Set(int u, int v, unsigned int color);

public:
	unsigned int *pix;
	int w, h;
	float *zb;

	Framebuffer(int u0, int v0, int _w, int _h);

	int handle(int guievent);

	void draw();
	void KeyboardHandle();
	void SetBGR(unsigned int bgr);
	void Set(Vector3 v, unsigned int color);
	void SetGuarded(int u, int v, unsigned int color);
	void SetZB(Vector3 uvz, unsigned int color);
	void LoadTiff(char* fname);
	void SaveAsTiff(char* fname);
	
	//draw shapes
	void DrawRectangle(int u0, int v0, int u1, int v1, unsigned int color);
	void DrawCircle(int u0, int v0, int radius, unsigned int color);
	void DrawLineSegment(Vector3 p0, Vector3 p1, Vector3 c0, Vector3 c1);
};