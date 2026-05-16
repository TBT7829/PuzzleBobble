#include "Cannon.h"
#include "const.h"
#include "keyManager.h"
#include "Task.h"
#include "TaskManager.h"
#include "Float2.h"
#include "ShotBall.h"
#include "variable.h"
#include "function.h"
#include "AnimationRepository.h"
#include "sound.h"

#include "dxlib/DxLib.h"
#include<cmath>


Cannon::Cannon() 
	: curAnimPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_RED), 0, 0), 
	nextAnimPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_RED), 0, 0), 
	cannonAnimPlayer(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_LAUNCH_PAD), 0, 0)
{
	AnimationRepository* pAnimRepo = AnimationRepository::getInstance();

	pos.x = WINDOW_WIDTH_HALF;
	pos.y = WINDOW_HEIGHT - 60;
	angle = 3.14159265 / 2.0; // 90度(真上)(-1.57f)

	arrrowImg = ImageManager::IMAGE_ARROW;

	cannonAnimState = 0;

	cannonAnimPlayer.update();

	curColor = GetRandomExistColor();
	switch (curColor) {
	case 0:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	default:
		abort();
		break;
	}


	nextColor = GetRandomExistColor();
	switch (nextColor) {
	case 0:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	default:
		abort();
		break;
	}


}

void Cannon::update()
{
	// 次になるべきアニメーション状態を一時的に決める
	// （デフォルトは 0:待機）
	int nextState = 0;

	// 計算前の角度を一時保存しておく
	float oldAngle = angle;

	AnimationRepository* pAnimRepo = AnimationRepository::getInstance();

	// 左右キーで角度変更
	if (CheckHitKey(KEY_INPUT_LEFT)  ) {
		angle += 0.05f;
		nextState = 1;
		
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		angle -= 0.05f;
		nextState = 2;
	}

	if (CheckHitKey(KEY_INPUT_UP)) angle = 3.14159265f / 2.0f;

	// 角度の制限(真横や下には撃てないようにする)
	angle = min(max(0.2f, angle), 3.141592f - 0.2f);

	// 角度が変わっていないならアニメーションはさせない
	if (oldAngle == angle) {
		nextState = 0;
	}

	//動いた瞬間にアニメーションを切り替える
	// 止まった瞬間（nextState == 0）はchangeAnimationを呼ばないように
	if (nextState != 0 && nextState != cannonAnimState) {
		if (nextState == 1) {
			cannonAnimPlayer.changeAnimation(AnimationRepository::A_LAUNCH_PAD);
		}
		else if (nextState == 2) {
			cannonAnimPlayer.changeAnimation(AnimationRepository::A_LAUNCH_PPAD_REVERSE);
		}

		cannonAnimState = nextState; // 状態を更新
	}

	// 動いているときだけアニメーションを進める
	if (nextState != 0) {
		cannonAnimPlayer.update();
	}
	else {
		// キーを離して止まったら、今の状態を止まっている状態(0)に戻す
		cannonAnimState = 0;
	}


	// ----------------------------------------
	// SPACEキーで発射！
	// ----------------------------------------
	if (pushHitKey(KEY_INPUT_SPACE)) {
		TaskManager* pTM = TaskManager::getInstance();

		PlaySoundMem(SoundManager::getInstance()->getSoundHandle(SoundManager::SOUND_SHOT), DX_PLAYTYPE_BACK, TRUE);

		// 新しい ShotBall を生成してタスクマネージャに登録
		pTM->add(new ShotBall(pTM->generateId(), pos, angle * -1, curColor));

		// nextColorをcurColorに入れる
		curColor = nextColor;
		switch (curColor) {
		case 0:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
			break;
		case 1:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
			break;
		case 2:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
			break;
		case 3:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
			break;
		case 4:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
			break;
		case 5:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
			break;
		case 6:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
			break;
		case 7:
			curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
			break;
		default:
			abort();
			break;
		}

		// 次に装填する色を場に存在する色の中から決める
		nextColor = GetRandomExistColor();
		switch (nextColor) {
		case 0:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
			break;
		case 1:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
			break;
		case 2:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
			break;
		case 3:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
			break;
		case 4:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
			break;
		case 5:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
			break;
		case 6:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
			break;
		case 7:
			nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
			break;
		default:
			abort();
			break;
		}
	}

	switch (curColor) {
	case 0:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		curAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	default:
		abort();
		break;
	}
	curAnimPlayer.update();


	switch (nextColor) {
	case 0:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_RED));
		break;
	case 1:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		break;
	case 2:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		break;
	case 3:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		break;
	case 4:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		break;
	case 5:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		break;
	case 6:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		break;
	case 7:
		nextAnimPlayer.setAds(pAnimRepo->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		break;
	default:
		abort();
		break;
	}
	nextAnimPlayer.update();
}

void Cannon::draw()
{
	cannonAnimPlayer.render(pos.x, pos.y);

	// 今のボール
	DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[curColor]);
	curAnimPlayer.render(pos.x, pos.y);


	// 次のボール
	int nextPosX = pos.x - 60;
	int nextPosY = pos.y + 20;
	DrawCircle(nextPosX, nextPosY, BALL_RADIUS, colArray[nextColor]);
	nextAnimPlayer.render(nextPosX, nextPosY);


	DrawString(nextPosX - 20, nextPosY + 20, "NEXT", 0xFFFFFF);

	
	// 大砲（発射の軌道線）を描画
	DrawLine(pos.x, pos.y,
		pos.x + (int)(cos(angle) * 50),
		pos.y - (int)(sin(angle) * 50),
		GetColor(255, 255, 255), 4);

	int imgHandle = ImageManager::getInstance()->getImageHandle(arrrowImg);
	// 元の angle は「真上が 90度（M_PI/2）」で「左に回るとプラス」
	// DxLibの画像回転は「真上が 0度」で「右に回るとプラス」なので、引き算で補正します。
	float rotaAngle = (3.14159265f / 2.0f) - angle;
	DrawRotaGraph(pos.x, pos.y, IMAGE_RATE, rotaAngle, imgHandle, TRUE);
}
