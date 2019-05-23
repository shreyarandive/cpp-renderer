#include "Scene.h"
#include "Vector3.h"
#include "Matrix3.h"

#include <stdlib.h>
#include <fstream>
#include <iostream>

Scene* scene;

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

	fb->DrawRectangle(5, 5, 105, 105, 0xFFFFFFFF);
	fb->DrawCircle(405, 405, 100, 0xFFFF00FF);

	Vector3 point(3, 1, 2);
	Vector3 point2(4, 5, 6);

	std::cerr << point[0] << point[1] << point[2] << std::endl;
	std::cerr << point + point2 << std::endl;
	std::cerr << point - point2 << std::endl;
	std::cerr << point * 2 << std::endl;
	std::cerr << point / 2 << std::endl;

	Vector3 v0(3, 2, 3);
	Vector3 v1(5, 6, 7);
	Vector3 v = v0 ^ v1;
	std::cerr << v << std::endl;

	Matrix3 m0, m1;
	m0[0] = Vector3(10.0f, 12.0f, 20.0f);
	m0[1] = Vector3(20.0f, 15.0f, 15.0f);
	m0[2] = Vector3(20.0f, 20.0f, 18.0f);
	
	m1[0] = Vector3(10.5f, 10.0f, 10.0f);
	m1[1] = Vector3(15.0f, 20.0f, 10.0f);
	m1[2] = Vector3(5.0f, 10.0f, 20.5f);

	std::cerr << m0 * m1 << std::endl;

	fb->redraw();
}