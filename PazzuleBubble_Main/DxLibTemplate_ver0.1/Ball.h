#pragma once
#include "Task.h"
#include "Float2.h"
#include "ImageManager.h"


class Ball : public Task
{
public:
	Ball(int taskId, int color) : Task(taskId)
	{
		pos.x = pos.y = 0.0f;

		isCheck = false;
		isSelect = false;
		colorNum = color;

	}
	Ball(int taskId, Float2 SetPos, int color) : Task(taskId)
	{
		pos = SetPos;
		isCheck = false;
		isSelect = false;
		colorNum = color;
	}
	void update()
	{

	}
	void render()
	{

	}
	void eventProc(Event* pEvent)
	{

	}


	Float2 pos;
	bool isCheck;
	bool isSelect;
	int colorNum;

};
