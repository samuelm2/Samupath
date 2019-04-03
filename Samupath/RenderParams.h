#pragma once
#include "World.h"
class PerspectivePinhole;
#include "PerspectivePinhole.h"
struct RenderParams {
	const World* world;
	const PerspectivePinhole* camera;
	RawImage* raw_image;
	int vstart;
	int hstart;
	int vlength;
	int hlength;
};