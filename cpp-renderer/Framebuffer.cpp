#include <iostream>
#include <iostream>
#include "math.h"
#include "tiffio.h"

#include "Framebuffer.h"
#include "Scene.h"
#include "Vector3.h"

FrameBuffer::FrameBuffer(int u0, int v0, int _w, int _h) : Fl_Gl_Window(u0, v0, _w, _h, 0) 
{
	w = _w;
	h = _h;
	pix = new unsigned int[w*h];
}

void FrameBuffer::draw()
{
	glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, pix);
}

int FrameBuffer::handle(int event)
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

void FrameBuffer::KeyboardHandle() {

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


void FrameBuffer::SetBGR(unsigned int bgr) 
{
	for (int uv = 0; uv < w*h; uv++)
		pix[uv] = bgr;
}

void FrameBuffer::Set(int u, int v, int color)
{
	pix[u*w + v] = color;
}

void FrameBuffer::SetGuarded(int u, int v, int color)
{
	if (u < 0 || v < 0 || u > h - 1 || v > w - 1)
		return;

	Set(u, v, color);
}

// load a tiff image to pixel buffer
void FrameBuffer::LoadTiff(char* fname) {
	TIFF* in = TIFFOpen(fname, "r");
	if (in == NULL) {
		std::cerr << fname << " could not be opened" << std::endl;
		return;
	}

	int width, height;
	TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(in, TIFFTAG_IMAGELENGTH, &height);
	if (w != width || h != height) {
		w = width;
		h = height;
		delete[] pix;
		pix = new unsigned int[w*h];
		size(w, h);
		glFlush();
		glFlush();
	}

	if (TIFFReadRGBAImage(in, w, h, pix, 0) == 0) {
		std::cerr << "failed to load " << fname << std::endl;
	}

	TIFFClose(in);
}

// save as tiff image
void FrameBuffer::SaveAsTiff(char *fname) {

	TIFF* out = TIFFOpen(fname, "w");

	if (out == NULL) {
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

	for (uint32 row = 0; row < (unsigned int)h; row++) {
		TIFFWriteScanline(out, &pix[(h - row - 1) * w], row);
	}

	TIFFClose(out);
}