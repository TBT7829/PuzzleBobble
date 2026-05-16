#pragma once

#include "Task.h"
#include "Float2.h"
#include "AnimationPlayer.h"

class ShotBall : public Task
{
public:
	ShotBall(int taskId, Float2 startPos, float angle, int color);

	void update();

	void render();

	void eventProc(Event* pEvent)
	{

	}

	Float2 pos;
	Float2 moveVec;
	int colorNum;
	AnimationPlayer animPlayer;
};