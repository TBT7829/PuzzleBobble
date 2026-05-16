#pragma once


#pragma once
#include "Task.h"
#include "Float2.h"
#include "AnimationPlayer.h"

// ‚µ‚Á‚©‚è‚Æ‹@”\•ª‚¯‚È‚Ç‚ğ‚·‚é‚È‚çDrawable‚ğŒp³‚³‚¹‚Äì‚é
class BanishBall : public Task
{
public:
	enum {
		BURST, 
		CHANGE_BANISH, 
		BANISH
	};

	BanishBall(int taskId, float x, float y, int _color);
	virtual ~BanishBall();

	virtual void update();

	virtual void render();

	virtual void eventProc(Event* pEvent)
	{

	}

	Float2 pos;
	int color;

	int state;

	AnimationPlayer animPlayer;
};