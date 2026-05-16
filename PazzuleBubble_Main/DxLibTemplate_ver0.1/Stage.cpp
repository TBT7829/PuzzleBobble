#include "Stage.h"
#include "TaskManager.h"
#include "Ball.h"
#include "variable.h"
#include "function.h"
#include "ImageManager.h"
#include "dxlib/DxLib.h"


Stage::Stage(int mapData[BALL_DATA_MAX][BALL_TABLE_ROW][BALL_TABLE_COL])
{
	TaskManager* pTM = TaskManager::getInstance();
	for (int i = 0; i < BALL_DATA_MAX; i++) {

		for (int row = 0; row < BALL_TABLE_ROW; row++) {
			for (int col = 0; col < BALL_TABLE_COL; col++) {

				// もし古いボールが残っていたら消す（再スタート時のメモリリーク防止）
				if (ballTable[row][col] != nullptr) {
					pTM->kill(ballTable[row][col]->getTaskId());
					ballTable[row][col] = nullptr;
				}

				// マップデータが -1 なら nullptr のまま
				if (mapData[i][row][col] == -1) {
					ballTable[row][col] = nullptr;
				}
				// 0以上ならボールを生成
				else {
					int color = mapData[i][row][col];
					ballTable[row][col] = new Ball(
						pTM->generateId(), color);
					// マップデータの数値をそのまま色番号として渡す
					ballTable[row][col]->colorNum = color;
					pTM->add(ballTable[row][col]);
				}
			}
		}

	}
	cannon.curColor = GetRandomExistColor();
	cannon.nextColor = GetRandomExistColor();

	init();
}

Stage::~Stage()
{
	exit();
}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
void Stage::init()
{
	TaskManager* pTM = TaskManager::getInstance();

	imageBG = ImageManager::IMAGE_BG;
	
	nextScene = -1;

}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void Stage::update()
{
	TaskManager* pTM = TaskManager::getInstance();
	cannon.update();
	pTM->updateAll();


	// ballTableに入っているボール座標更新
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			if (pBall == nullptr) continue;

			if (pBall->colorNum <= -1) {
				continue;
			}

			Float2 _pos = GetBubblePos(row, col);
			pBall->pos = _pos;

		}
	}

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			if (pBall == nullptr) continue;

			pBall->isSelect = false;
		}
	}

	CheckGameOver();
	
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void Stage::render()
{
	TaskManager* pTM = TaskManager::getInstance();

	int bgImageHandle = ImageManager::getInstance()->getImageHandle(imageBG);
	DrawGraph(0, 0, bgImageHandle, TRUE);

	// 線のみの円でマスを描画する
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			Float2 pos = GetBubblePos(row, col);

			// 奇数列は最後のマスを使用しない
			if (row % 2 != 0 && BALL_TABLE_COL - 1 <= col)
			{
				continue;
			}

			DrawCircle(pos.x, pos.y, BALL_RADIUS, 0xFFFFFF, 0);

		}

	}

	

	// ステージの壁の線
	//DrawLine(LEFT_WALL_X, 0, LEFT_WALL_X, WINDOW_HEIGHT, 0xFFFFFF);
	//DrawLine(RIGHT_WALL_X, 0, RIGHT_WALL_X, WINDOW_HEIGHT, 0xFFFFFF);
	// 天井
	DrawFillBox(LEFT_WALL_X, BALL_OFFSET_Y, RIGHT_WALL_X, BALL_OFFSET_Y + ceilingOffsetY, 0x808080);
	DrawLine(LEFT_WALL_X, BALL_OFFSET_Y + ceilingOffsetY, RIGHT_WALL_X, BALL_OFFSET_Y + ceilingOffsetY, 0xFFFFFFF, 3);

	// ゲームオーバー線
	if (CheckGameOver() == false) {
		DrawLine(LEFT_WALL_X, DEAD_LINE_Y, RIGHT_WALL_X, DEAD_LINE_Y, 0xFFFF00);
	}
	else {
		DrawLine(LEFT_WALL_X, DEAD_LINE_Y, RIGHT_WALL_X, DEAD_LINE_Y, 0xFF0000);
	}
	SetFontSize(40);
	DrawFormatString(10, 10, 0xFFFFFF, "%.8d", score);
	SetFontSize(16);

	cannon.draw();
	pTM->renderAll();
}

void Stage::exit()
{
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = pCurRow[col];

			pBall = nullptr;
		}
	}
}
