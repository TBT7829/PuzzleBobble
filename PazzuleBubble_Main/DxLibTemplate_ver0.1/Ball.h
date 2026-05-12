#pragma once
#include "Task.h"
#include "Float2.h"



class Ball : public Task
{
public:
	Ball(int taskId) : Task(taskId)
	{
		pos.x = pos.y = 0.0f;

		isCheck = false;
		isSelect = false;
		colorNum = 0;

	}
	Ball(int taskId, Float2 SetPos) : Task(taskId)
	{
		pos = SetPos;
		isCheck = false;
		isSelect = false;
		colorNum = 0;
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