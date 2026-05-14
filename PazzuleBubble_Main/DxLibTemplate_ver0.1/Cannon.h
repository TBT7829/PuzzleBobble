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
	int curColor;  // 現在装填されている玉の色
	int nextColor; // 次に装填される玉の色
};