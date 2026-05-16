#include "BanishBall.h"
#include "TaskManager.h"
#include "const.h"
#include "variable.h"
#include "AnimationRepository.h"

#include "dxlib/DxLib.h"


BanishBall::BanishBall(int taskId, float x, float y, int _color) : Task(taskId), animPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GRAY), 0, 0)
{
	pos.x = x;
	pos.y = y;

	int state = BURST;

	AnimationRepository* pAnimRepo = AnimationRepository::getInstance();

	//colorNum = color;
	switch (_color) {
	case 0:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_RED_BURST);
		break;
	case 1:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_GREEN_BURST);
		break;
	case 2:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_BLUE_BURST);
		break;
	case 3:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_YELLOW_BURST);
		break;
	case 4:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_ORANGE_BURST);
		break;
	case 5:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_PURPLE_BURST);
		break;
	case 6:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_WHITE_BURST);
		break;
	case 7:
		color = _color;
		animPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_GRAY_BURST);
		break;
	default:
		abort();
		break;
	}
}

BanishBall::~BanishBall()
{

}

void BanishBall::update()
{
	switch (state) {
	//-------------------------
	case BURST:
		animPlayer.update();
		if (animPlayer.getState() == AP_STOP) {
			state = CHANGE_BANISH;
		}
		break;

	//-------------------------
	case CHANGE_BANISH:

		switch (color) {
		case 0:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_RED));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_RED_BANISH);
			state = BANISH;
			break;
		case 1:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_GREEN_BANISH);
			state = BANISH;
			break;
		case 2:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_BLUE_BANISH);
			state = BANISH;
			break;
		case 3:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_YELLOW_BANISH);
			state = BANISH;
			break;
		case 4:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_ORANGE_BANISH);
			state = BANISH;
			break;
		case 5:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_PURPLE_BANISH);
			state = BANISH;
			break;
		case 6:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_WHITE_BANISH);
			state = BANISH;
			break;
		case 7:
			animPlayer.setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
			animPlayer.changeAnimation(AnimationRepository::A_BUBBLE_GRAY_BANISH);
			state = BANISH;
			break;
		default:
			abort();
			break;
		}
		break;


	//-------------------------
	case BANISH:
		animPlayer.update();
		if (animPlayer.getState() == AP_STOP) {
			TaskManager::getInstance()->kill(getTaskId());
		}
		break;
	}
}

void BanishBall::render()
{
	animPlayer.render(pos.x, pos.y);
}