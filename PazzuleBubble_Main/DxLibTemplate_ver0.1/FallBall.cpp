#include "FallBall.h"
#include "TaskManager.h"
#include "const.h"
#include "variable.h"

#include "dxlib/DxLib.h"

FallBall::FallBall(int taskId, float x, float y, float _wait, int _color) : Task(taskId)
{
	pos.x = x;
	pos.y = y;
	wait = _wait;
	moveVec.x = moveVec.y = 1.0f;
	color = _color;
}

FallBall::~FallBall()
{

}

void FallBall::update()
{
	if (0 < wait) {
		wait -= 1.0f;
	}
	else {
		pos.y += moveVec.y;
		moveVec.y += 0.8f;
		if (WINDOW_HEIGHT < pos.y) {
			TaskManager::getInstance()->kill(getTaskId());
		}
	}

}

void FallBall::render()
{
	DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[color]);
}
