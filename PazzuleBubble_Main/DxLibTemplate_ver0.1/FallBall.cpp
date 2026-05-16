#include "FallBall.h"
#include "TaskManager.h"
#include "const.h"
#include "variable.h"
#include "AnimationRepository.h"

#include "dxlib/DxLib.h"

FallBall::FallBall(int taskId, float x, float y, float _wait, int _color) : Task(taskId), animPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GRAY), 0, 0)
{
	pos.x = x;
	pos.y = y;
	wait = _wait;
	moveVec.x = moveVec.y = 1.0f;

	AnimationRepository* pAnimRepo = AnimationRepository::getInstance();

	//colorNum = color;
	switch (color) {
	case 0:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	default:
		abort();
		break;
	}
}

FallBall::~FallBall()
{

}

void FallBall::update()
{
	animPlayer.update();
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
	animPlayer.render(pos.x, pos.y);
	//DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[color]);
}
