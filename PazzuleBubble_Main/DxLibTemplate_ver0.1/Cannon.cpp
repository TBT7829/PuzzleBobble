#include "Cannon.h"
#include "const.h"
#include "keyManager.h"
#include "Task.h"
#include "TaskManager.h"
#include "Float2.h"
#include "ShotBall.h"
#include "variable.h"
#include "function.h"

#include "sound.h"

#include "dxlib/DxLib.h"
#include<cmath>


Cannon::Cannon()
{
	pos.x = WINDOW_WIDTH_HALF;
	pos.y = WINDOW_HEIGHT - 60;
	angle = 3.14159265 / 2.0; // 90度(真上)(-1.57f)
	curColor = GetRandomExistColor();
	nextColor = GetRandomExistColor();
}

void Cannon::update()
{
	// 左右キーで角度変更
	if (CheckHitKey(KEY_INPUT_LEFT))  angle += 0.05f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) angle -= 0.05f;
	if (CheckHitKey(KEY_INPUT_UP)) angle = 3.14159265f / 2.0f;

	// 角度の制限(真横や下には撃てないようにする)
	angle = min(max(0.2f, angle), 3.141592f - 0.2f);

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
		// 次に装填する色を場に存在する色の中から決める
		nextColor = GetRandomExistColor();
	}
}

void Cannon::draw()
{
	// 今のボール
	DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[curColor]);

	// 次のボール
	int nextPosX = pos.x - 60;
	int nextPosY = pos.y + 20;
	DrawCircle(nextPosX, nextPosY, BALL_RADIUS, colArray[nextColor]);

	DrawString(nextPosX - 20, nextPosY + 20, "NEXT", 0xFFFFFF);

	// 大砲（発射の軌道線）を描画
	DrawLine(pos.x, pos.y,
		pos.x + (int)(cos(angle) * 50),
		pos.y - (int)(sin(angle) * 50),
		GetColor(255, 255, 255), 4);
}
