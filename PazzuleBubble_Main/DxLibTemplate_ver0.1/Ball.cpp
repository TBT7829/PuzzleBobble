#include "Ball.h"
#include "ImageManager.h"
#include "variable.h"
#include "AnimationRepository.h"

#include "dxlib/DxLib.h"

Ball::Ball(int taskId, int color) : Task(taskId), animPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GRAY), 0, 0)
{
	pos.x = pos.y = 0.0f;

	isCheck = false;
	isSelect = false;

	//colorNum = color;
	AnimationRepository* pAnimRepo = AnimationRepository::getInstance();

	//colorNum = color;
	switch (color) {
	case 0:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	}

}

Ball::Ball(int taskId, Float2 SetPos, int color) : Task(taskId), animPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GRAY), 0, 0)
{
	pos = SetPos;
	isCheck = false;
	isSelect = false;

	//colorNum = color;
	AnimationRepository* pAnimRepo = AnimationRepository::getInstance();

	//colorNum = color;
	switch (color) {
	case 0:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		colorNum = color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	}
}

void Ball::eventProc(Event* pEvent)
{

}

void Ball::update()
{
	animPlayer.update();
}

void Ball::render()
{
	//DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[colorNum]);
	animPlayer.render(pos.x, pos.y);
}


