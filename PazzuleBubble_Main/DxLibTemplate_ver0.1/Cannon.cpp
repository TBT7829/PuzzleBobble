#include "Cannon.h"
#include "const.h"
#include "keyManager.h"
#include "Task.h"
#include "TaskManager.h"
#include "Float2.h"
#include "ShotBall.h"
#include "variable.h"

#include "dxlib/DxLib.h"
#include<cmath>


Cannon::Cannon()
{
	pos.x = WINDOW_WIDTH_HALF;
	pos.y = WINDOW_HEIGHT - 60;
	angle = 3.14159265 / 2.0; // 90度(真上)(-1.57f)
	nextColor = GetRand(2) + 1;
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

		// 新しい ShotBall を生成してタスクマネージャに登録
		pTM->add(new ShotBall(pTM->generateId(), pos, angle * -1, nextColor));

		// 次に装填する色をランダム（1〜4）で決める
		nextColor = GetRand(2) + 1;
	}
}

void Cannon::draw()
{
	DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[nextColor - 1]);
	// 大砲（発射の軌道線）を描画
	DrawLine(pos.x, pos.y,
		pos.x + (int)(cos(angle) * 50),
		pos.y - (int)(sin(angle) * 50),
		GetColor(255, 255, 255), 4);
}
