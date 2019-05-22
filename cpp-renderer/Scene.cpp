#include "Scene.h"
#include "Vector3.h"
#include "Matrix3.h"

#include <stdlib.h>
#include <fstream>
#include <iostream>

Scene *scene;

Scene::Scene()
{
	gui = new GUI();
	gui->show();

	int u0 = 20;
	int v0 = 20;
	int w = 640;
	int h = 480;

	fb = new FrameBuffer(u0, v0, w, h);
	fb->label("Renderer");
	fb->show();

	gui->uiw->position(u0, v0 + fb->h + 60);

	Render();
}

void Scene::Render()
{
	fb->SetBGR(0xFF00FFFF);
	fb->redraw();
}

void Scene::Debug() 
{
	std::cerr << "Debug button pressed" << std::endl;
}