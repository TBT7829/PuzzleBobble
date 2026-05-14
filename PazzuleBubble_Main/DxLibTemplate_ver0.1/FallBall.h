#pragma once
#include "Task.h"
#include "Float2.h"

// ‚µ‚Á‚©‚è‚Æ‹@”\•ª‚¯‚È‚Ç‚ğ‚·‚é‚È‚çDrawable‚ğŒp³‚³‚¹‚Äì‚é
class FallBall : public Task
{
public:
	FallBall(int taskId, float x, float y, float _wait, int _color);
	virtual ~FallBall();

	virtual void update();

	virtual void render();

	virtual void eventProc(Event* pEvent)
	{

	}

	Float2 pos;
	Float2 moveVec;
	float wait;
	int color;
};