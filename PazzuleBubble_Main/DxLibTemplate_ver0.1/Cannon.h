#pragma once
#include "Float2.h"

class Cannon
{
public:
	Cannon();

	void update();

	void draw();

	Float2 pos;
	float angle;
	int nextColor; // 装填されている玉の色
};