#include "Ball.h"
#include "ShotBall.h"
#include "Cannon.h"
#include "TaskManager.h"
#include "variable.h"
#include "keyManager.h"

#include "dxlib/DxLib.h"
#include <cmath>

Cannon cannon;

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
void Init()
{
	TaskManager* pTM = TaskManager::getInstance();

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = pCurRow[col];

			pBall = nullptr;
		}
	}

	pTM->add(ballTable[0][0] = new Ball(pTM->generateId()));
	ballTable[0][0]->colorNum = 1;
	pTM->add(ballTable[0][1] = new Ball(pTM->generateId()));
	ballTable[0][1]->colorNum = 1;
	pTM->add(ballTable[0][2] = new Ball(pTM->generateId()));
	ballTable[0][2]->colorNum = 2;
	pTM->add(ballTable[0][3] = new Ball(pTM->generateId()));
	ballTable[0][3]->colorNum = 1;
	pTM->add(ballTable[0][4] = new Ball(pTM->generateId()));
	ballTable[0][4]->colorNum = 3;
	pTM->add(ballTable[0][5] = new Ball(pTM->generateId()));
	ballTable[0][5]->colorNum = 2;
	pTM->add(ballTable[0][6] = new Ball(pTM->generateId()));
	ballTable[0][6]->colorNum = 3;
	pTM->add(ballTable[0][7] = new Ball(pTM->generateId()));
	ballTable[0][7]->colorNum = 1;

	pTM->add(ballTable[1][0] = new Ball(pTM->generateId()));
	ballTable[1][0]->colorNum = 1;
	pTM->add(ballTable[1][1] = new Ball(pTM->generateId()));
	ballTable[1][1]->colorNum = 2;
	pTM->add(ballTable[1][2] = new Ball(pTM->generateId()));
	ballTable[1][2]->colorNum = 3;
	pTM->add(ballTable[1][3] = new Ball(pTM->generateId()));
	ballTable[1][3]->colorNum = 3;
	pTM->add(ballTable[1][4] = new Ball(pTM->generateId()));
	ballTable[1][4]->colorNum = 2;
	pTM->add(ballTable[1][5] = new Ball(pTM->generateId()));
	ballTable[1][5]->colorNum = 2;
	pTM->add(ballTable[1][6] = new Ball(pTM->generateId()));
	ballTable[1][6]->colorNum = 1;

	pTM->add(ballTable[2][0] = new Ball(pTM->generateId()));
	ballTable[2][0]->colorNum = 3;
	pTM->add(ballTable[2][1] = new Ball(pTM->generateId()));
	ballTable[2][1]->colorNum = 2;
	pTM->add(ballTable[2][2] = new Ball(pTM->generateId()));
	ballTable[2][2]->colorNum = 3;
	pTM->add(ballTable[2][3] = new Ball(pTM->generateId()));
	ballTable[2][3]->colorNum = 1;
	pTM->add(ballTable[2][4] = new Ball(pTM->generateId()));
	ballTable[2][4]->colorNum = 2;
	pTM->add(ballTable[2][5] = new Ball(pTM->generateId()));
	ballTable[2][5]->colorNum = 2;
	pTM->add(ballTable[2][6] = new Ball(pTM->generateId()));
	ballTable[2][6]->colorNum = 3;
	pTM->add(ballTable[2][7] = new Ball(pTM->generateId()));
	ballTable[2][7]->colorNum = 1;

	pTM->add(ballTable[3][0] = new Ball(pTM->generateId()));
	ballTable[3][0]->colorNum = 2;
	pTM->add(ballTable[3][1] = new Ball(pTM->generateId()));
	ballTable[3][1]->colorNum = 1;
	pTM->add(ballTable[3][2] = new Ball(pTM->generateId()));
	ballTable[3][2]->colorNum = 1;
	pTM->add(ballTable[3][3] = new Ball(pTM->generateId()));
	ballTable[3][3]->colorNum = 2;
	pTM->add(ballTable[3][4] = new Ball(pTM->generateId()));
	ballTable[3][4]->colorNum = 3;
	pTM->add(ballTable[3][5] = new Ball(pTM->generateId()));
	ballTable[3][5]->colorNum = 3;
	pTM->add(ballTable[3][6] = new Ball(pTM->generateId()));
	ballTable[3][6]->colorNum = 2;

	pTM->add(ballTable[4][0] = new Ball(pTM->generateId()));
	ballTable[4][0]->colorNum = 3;
	pTM->add(ballTable[4][1] = new Ball(pTM->generateId()));
	ballTable[4][1]->colorNum = 1;
	pTM->add(ballTable[4][2] = new Ball(pTM->generateId()));
	ballTable[4][2]->colorNum = 2;
	pTM->add(ballTable[4][3] = new Ball(pTM->generateId()));
	ballTable[4][3]->colorNum = 2;
	pTM->add(ballTable[4][4] = new Ball(pTM->generateId()));
	ballTable[4][4]->colorNum = 3;
	pTM->add(ballTable[4][5] = new Ball(pTM->generateId()));
	ballTable[4][5]->colorNum = 3;
	pTM->add(ballTable[4][6] = new Ball(pTM->generateId()));
	ballTable[4][6]->colorNum = 1;
	pTM->add(ballTable[4][7] = new Ball(pTM->generateId()));
	ballTable[4][7]->colorNum = 3;

	pTM->add(ballTable[5][3] = new Ball(pTM->generateId()));
	ballTable[5][3]->colorNum = 2;

	pTM->add(ballTable[6][3] = new Ball(pTM->generateId()));
	ballTable[6][3]->colorNum = 1;

	pTM->add(ballTable[7][2] = new Ball(pTM->generateId()));
	ballTable[7][2]->colorNum = 3;

	pTM->add(ballTable[8][3] = new Ball(pTM->generateId()));
	ballTable[8][3]->colorNum = 2;

	pTM->add(ballTable[9][2] = new Ball(pTM->generateId()));
	ballTable[9][2]->colorNum = 2;


}


//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void Update()
{
	TaskManager* pTM = TaskManager::getInstance();
	pTM->updateAll();

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			if (pBall == nullptr) continue;

			pBall->isSelect = false;
		}
	}

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			if (pBall == nullptr) continue;

			if (pBall->colorNum <= 0) {
				continue;
			}

			int idx = pBall->colorNum - 1;
			int offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
			float posX = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
			float posY = BALL_RADIUS + row * BALL_RADIUS * 2.0f;


		}
	}




	cannon.update();
}


//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void Draw()
{
	TaskManager* pTM = TaskManager::getInstance();

	// 線のみの円でマスを描画する
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			int offsetX = (row % 2 == 0) ? 0 : BALL_RADIUS;
			float posX = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
			float posY = BALL_RADIUS + row * BALL_RADIUS * 2.0f;

			// 奇数列は最後のマスを使用しない
			if (row % 2 != 0 && BALL_TABLE_COL - 1 <= col)
			{
				continue;
			}

			DrawCircle(posX, posY, BALL_RADIUS, 0xFFFFFF, 0);

		}

	}

	// ballTableに入っているボールを描画
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			if (pBall == nullptr) continue;

			if (pBall->colorNum <= 0) {
				continue;
			}

			int idx = pBall->colorNum - 1;
			int offsetX = (row % 2 == 0) ? 0 : BALL_RADIUS;
			float posX = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
			float posY = BALL_RADIUS + row * BALL_RADIUS * 2.0f;

			int drawColor = colArray[idx];
			if (pBall->isSelect == true) {
				drawColor = 0xFFFF00;
			}

			DrawCircle(posX, posY, BALL_RADIUS, drawColor);

		}
	}





	// ステージの壁の線
	DrawLine(LEFT_WALL_X, 0, LEFT_WALL_X, WINDOW_HEIGHT, 0xFFFFFF);
	DrawLine(RIGHT_WALL_X, 0, RIGHT_WALL_X, WINDOW_HEIGHT, 0xFFFFFF);

	cannon.draw();
	pTM->renderAll();
}



// それが出来たら再帰的に探索していく
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	// 垂直同期を有効にする
	SetWaitVSyncFlag(TRUE);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);


	//---------------------------------------
	// 変数の作成や初期化、その他初期設定
	// ↓ システム初期化 ↓
	initKeyManager();
	// ↑ システム初期化 ↑
	//---------------------------------------
	Init();




	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		updateKeyState();
		// ↑ システム更新 ↑
		//---------------------------------------
		Update();



		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		Draw();


		ScreenFlip();
	}

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = pCurRow[col];

			pBall = nullptr;
		}
	}

	DxLib_End();

	return 0;

}