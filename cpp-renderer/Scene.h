#pragma once

#include "GUI.h"
#include "Framebuffer.h"

class Scene
{
public:
	GUI* gui;
	FrameBuffer* fb;

	Scene();
	void Debug();
	void Render();

};

extern Scene* scene;