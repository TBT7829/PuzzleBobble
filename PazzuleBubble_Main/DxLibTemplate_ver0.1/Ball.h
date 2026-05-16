#pragma once
#include "Task.h"
#include "Float2.h"
#include "AnimationPlayer.h"


class Ball : public Task
{
public:
	Ball(int taskId, int color);
	Ball(int taskId, Float2 SetPos, int color);
	void update();
	void render();
	void eventProc(Event* pEvent);


	Float2 pos;
	bool isCheck;
	bool isSelect;
	int colorNum;
	AnimationPlayer animPlayer;

};
