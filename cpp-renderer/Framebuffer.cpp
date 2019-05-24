#include <iostream>
#include <iostream>
#include "math.h"
#include "tiffio.h"

#include "Framebuffer.h"
#include "Scene.h"
#include "Vector3.h"

Framebuffer::Framebuffer(int u0, int v0, int _w, int _h) : Fl_Gl_Window(u0, v0, _w, _h, nullptr) 
{
	w = _w;
	h = _h;
	pix = new unsigned int[w * h];
}

void Framebuffer::draw()
{
	glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, pix);
}

int Framebuffer::handle(int event)
{
	switch (event)
	{
		case FL_KEYBOARD:
		{
			KeyboardHandle();
			return 0;
		}
		default:
			break;
	}
	return 0;
}

void Framebuffer::KeyboardHandle() 
{
	int key = Fl::event_key();

	switch (key)
	{
		case ',': 
		{
			std::cerr << "INFO: pressed ," << std::endl;
			break;
		}
		default:
			std::cerr << "INFO: do not understand keypress" << std::endl;
	}
}


void Framebuffer::SetBGR(unsigned int bgr) 
{
	for (int uv = 0; uv < w * h; uv++)
		pix[uv] = bgr;
}

void Framebuffer::Set(int u, int v, unsigned int color)
{
	//pix[u * w + v] = color; //starts from bottom left corner of the screen
	pix[(h - 1 - u) * w + v] = color;
}

void Framebuffer::Set(Vector3 uv, unsigned int color)
{
	SetGuarded((int)uv[0], (int)uv[1], color);
}

void Framebuffer::SetGuarded(int u, int v, unsigned int color)
{
	if (u < 0 || v < 0 || u > h - 1 || v > w - 1)
		return;

	Set(u, v, color);
}

void Framebuffer::SetZB(Vector3 uvz, unsigned int color)
{
	int u = (int)uvz[0];
	int v = (int)uvz[1];
	if (u < 0 || v < 0 || u > w - 1 || v > h - 1)
		return;

	int uv = (h - 1 - v)*w + u;
	if (zb[uv] > uvz[2])
		return;
	zb[uv] = uvz[2];

	Set(uvz, color);
}

// load a tiff image to pixel buffer
void Framebuffer::LoadTiff(char* fname)
{
	TIFF* in = TIFFOpen(fname, "r");
	if (in == nullptr) 
	{
		std::cerr << fname << " could not be opened" << std::endl;
		return;
	}

	int width, height;
	TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(in, TIFFTAG_IMAGELENGTH, &height);
	if (w != width || h != height)
	{
		w = width;
		h = height;
		delete[] pix;
		pix = new unsigned int[w * h];
		size(w, h);
		glFlush();
		glFlush();
	}

	if (TIFFReadRGBAImage(in, w, h, pix, 0) == 0) 
	{
		std::cerr << "failed to load " << fname << std::endl;
	}

	TIFFClose(in);
}

// save as tiff image
void Framebuffer::SaveAsTiff(char *fname) 
{

	TIFF* out = TIFFOpen(fname, "w");

	if (out == nullptr) 
	{
		std::cerr << fname << " could not be opened" << std::endl;
		return;
	}

	TIFFSetField(out, TIFFTAG_IMAGEWIDTH, w);
	TIFFSetField(out, TIFFTAG_IMAGELENGTH, h);
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 4);
	TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

	for (uint32 row = 0; row < (unsigned int)h; row++)
	{
		TIFFWriteScanline(out, &pix[(h - row - 1) * w], row);
	}

	TIFFClose(out);
}

void Framebuffer::DrawRectangle(int u0, int v0, int u1, int v1, unsigned int color)
{
	for(int i = u0 ; i <= u1 ; i++)
		for (int j = v0; j <= v1; j++)
			SetGuarded(i, j, color);
}

void Framebuffer::DrawCircle(int u0, int v0, int radius, unsigned int color)
{
	int u1 = u0 - radius;
	int u2 = u0 + radius;
	int v1 = v0 - radius;
	int v2 = v0 + radius;

	for(int i = u1 ; i <= u2 ; i++)
		for(int j = v1 ; j <= v2 ; j++)
			if(((i - u0) * (i - u0) + (j - v0) * (j - v0)) <= radius * radius)
				SetGuarded(i, j, color);
}

void Framebuffer::DrawLineSegment(Vector3 p0, Vector3 p1, Vector3 c0, Vector3 c1) 
{
	float du = fabsf(p0[0] - p1[0]);
	float dv = fabsf(p0[1] - p1[1]);
	int stepsN;
	
	if (du > dv) 
		stepsN = static_cast<int>(du + 2);
	else 
		stepsN = static_cast<int>(dv + 2);

	Vector3 duv = (p1 - p0) / (float)(stepsN - 1);
	Vector3 dc = (c1 - c0) / (float)(stepsN - 1);
	for (int stepi = 0; stepi < stepsN; stepi++) 
	{
		Vector3 currp = p0 + duv * (float)stepi;
		Vector3 currc = c0 + dc * (float)stepi;
		SetZB(currp, currc.GetColor());
	}
}

