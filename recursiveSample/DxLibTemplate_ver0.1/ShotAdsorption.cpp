#include "const.h"
#include "keyManager.h"
#include "hitFunc.h"
#include "dxlib/DxLib.h"
#include <cmath>

const int WINDOW_WIDTH_HALF = WINDOW_WIDTH * 0.5f;
const int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT * 0.5f;

const int BALL_OFFSET_X = 315;
// バブルの移動スピード
const double BUBBLE_SPEED = 8.0;

// ボール配列の列
const int BALL_TABLE_COL = 8;
// ボール配列の行
const int BALL_TABLE_ROW = 13;
// 半径
const int BALL_RADIUS = 16;

// ボールの色配列
int colArray[4] =
{
	0xFF0000,	//0: 赤
	0x00FF00,	//1: 緑
	0x0000FF,	//2: 青
	0xFFFFFF,	//3: 白
};

// 方向
enum Direction {
	TOP_LEFT = 0,	// 0
	TOP_RIGHT,		// 1
	LEFT,			// 2
	RIGHT,			// 3
	BOTTOM_LEFT,	// 4
	BOTTOM_RIGHT,	// 5
	DIR_MAX			// 6
};

enum BALL_STATE {
	WAIT,
	MOVE,
	STOP
};

class Ball
{
public:
	Ball()
	{
		pos.x = pos.y = 0.0f;
		moveVec.x = moveVec.y = 0.0f;
		state = WAIT;
		isCheck = false;
		isSelect = false;
		colorNum = 0;
		colIdx = 0;
		rowIdx = 0;
	}
	Ball(Float2 SetPos)
	{
		pos = SetPos;
	}
	void update(float angle)
	{
		switch (state) {
		case WAIT:
			// バブルの発射
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				moveVec.x = cos(angle) * BUBBLE_SPEED;
				moveVec.y = -sin(angle) * BUBBLE_SPEED;

				state = MOVE;
			}
			break;
		case MOVE:
			pos.x += moveVec.x;
			pos.y += moveVec.y;
			break;
		case STOP:

			break;
		default:

			break;

		}
	}

	Float2 pos;
	Float2 moveVec;
	int state;
	bool isCheck;
	bool isSelect;
	int colorNum;
	int colIdx;
	int rowIdx;

};

class Cannon
{
public:
	Cannon()
	{
		pos.x = WINDOW_WIDTH_HALF - 75;
		pos.y = WINDOW_HEIGHT - 70;
		angle = 3.14159265 / 2.0; // 90度(真上)
	}

	void update()
	{
		// 左右キーで角度変更
		if (CheckHitKey(KEY_INPUT_LEFT))  angle += 0.05;
		if (CheckHitKey(KEY_INPUT_RIGHT)) angle -= 0.05;
		if (CheckHitKey(KEY_INPUT_UP)) angle = 3.14159265 / 2.0;

		// 角度の制限(真横や下には撃てないようにする)
		angle = min(max(0.2f, angle), 3.141592f - 0.2f);
		
	}

	void draw()
	{
		//DrawCircle(pos.x, pos.y, BALL_RADIUS, 0xFF00FF);
		// 大砲（発射の軌道線）を描画
		DrawLine(pos.x, pos.y, pos.x + (int)(cos(angle) * 50), pos.y - (int)(sin(angle) * 50), GetColor(255, 255, 255), 4);
	}

	Float2 pos;
	float angle;
};



// 一番距離が小さかったボールの行を保存する変数
int nearestBallRow = -1;
// 一番距離が小さかったボールの列を保存する変数
int nearestBallCol = -1;
// 一番距離が小さかった値を保存する変数
float nearestDistance = 0;

// ボールクラスの配列
Ball ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];

// プロトタイプ宣言
void _checkSameColorBall(Ball& ball, int row, int col, int& findNum, int color);

Ball curBall;
Ball nextBall;

Cannon cannon;

// 直接呼び出される再起処理を開始する関数
int checkSameColorBall(Ball& ball, int row, int col)
{
	// 全ボールのチェックを解除
	for (Ball(&row)[8] : ballTable) {
		for (Ball& curBall : row) {
			curBall.isCheck = false;
		}
	}

	// 見つかった数を保存する変数
	int findNum = 0;

	int colorBuffer = ballTable[row][col].colorNum;

	// 再起処理で探索
	_checkSameColorBall(ball, row, col, findNum, colorBuffer);


	return findNum;
}


void _checkSameColorBall(Ball& ball, int row, int col, int& findNum, int color)
{
	// 現在参照しようとしている行の番号が配列の範囲内に収まっているかをチェック
	if (row < 0 || BALL_TABLE_ROW <= row) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		return;
	}
	// 現在参照しようとしている列の番号が配列の範囲内に収まっているかをチェック
	if (col < 0 || BALL_TABLE_COL <= col) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		return;
	}
	// 現在参照しようとしている番号の配列の要素がチェック済みかをチェック
	if (ballTable[row][col].isCheck == true) {
		// 既にチェック(探索)済みなのでここで再起処理を終了
		return;
	}

	ballTable[row][col].isCheck = true;

	// 指定された要素の色が同じかチェック
	if (ballTable[row][col].colorNum != color) {
		// 色が同じでは無いのでここで再帰処理を終了
		return;
	}

	// 同じ色を見つけた数をカウント
	findNum++;
	// 対象として
	ballTable[row][col].isSelect = true;

	// 隣接6方向の探索
	// offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
	// この描画方式に合わせて偶数行/奇数行で隣接を分ける
	const int dr_even[6] = { -1, -1, 0, 0, 1, 1 };
	const int dc_even[6] = { -1,  0, -1, 1, -1, 0 }; // 偶数行の隣接
	const int dr_odd[6] = { -1, -1, 0, 0, 1, 1 };
	const int dc_odd[6] = { 0,  1, -1, 1,  0, 1 }; // 奇数行の隣接

	const int* dr = (row % 2 == 0) ? dr_even : dr_odd;
	const int* dc = (row % 2 == 0) ? dc_even : dc_odd;

	for (int i = 0; i < 6; ++i) {
		int nr = row + dr[i];
		int nc = col + dc[i];
		// 再起処理を行う
		_checkSameColorBall(ballTable[row][col], nr, nc, findNum, color);
	}

}



//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
void Init()
{
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball* pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = &pCurRow[col];
		}
	}

	ballTable[0][0].colorNum = 1;
	ballTable[0][1].colorNum = 1;
	ballTable[0][2].colorNum = 2;
	ballTable[0][3].colorNum = 1;
	ballTable[0][4].colorNum = 3;
	ballTable[0][5].colorNum = 2;
	ballTable[0][6].colorNum = 3;
	ballTable[0][7].colorNum = 1;

	ballTable[1][0].colorNum = 1;
	ballTable[1][1].colorNum = 2;
	ballTable[1][2].colorNum = 3;
	ballTable[1][3].colorNum = 3;
	ballTable[1][4].colorNum = 2;
	ballTable[1][5].colorNum = 2;
	ballTable[1][6].colorNum = 1;

	ballTable[2][0].colorNum = 3;
	ballTable[2][1].colorNum = 2;
	ballTable[2][2].colorNum = 3;
	ballTable[2][3].colorNum = 1;
	ballTable[2][4].colorNum = 2;
	ballTable[2][5].colorNum = 2;
	ballTable[2][6].colorNum = 3;
	ballTable[2][7].colorNum = 1;

	ballTable[3][0].colorNum = 2;
	ballTable[3][1].colorNum = 1;
	ballTable[3][2].colorNum = 1;
	ballTable[3][3].colorNum = 2;
	ballTable[3][4].colorNum = 3;
	ballTable[3][5].colorNum = 3;
	ballTable[3][6].colorNum = 2;

	ballTable[4][0].colorNum = 3;
	ballTable[4][1].colorNum = 1;
	ballTable[4][2].colorNum = 2;
	ballTable[4][3].colorNum = 2;
	ballTable[4][4].colorNum = 3;
	ballTable[4][5].colorNum = 3;
	ballTable[4][6].colorNum = 1;
	ballTable[4][7].colorNum = 3;

	ballTable[5][3].colorNum = 2;

	ballTable[6][3].colorNum = 1;

	ballTable[7][2].colorNum = 3;

	ballTable[8][3].colorNum = 2;

	ballTable[9][2].colorNum = 2;

}


//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void Update()
{
	int x, y;
	GetMousePoint(&x, &y);
	float mouseX = (float)x;
	float mouseY = (float)y;

	// 距離の初期化
	nearestDistance = 10000.0f;
	nearestBallRow = -1;
	nearestBallCol = -1;

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball* pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = &pCurRow[col];
			pBall->isSelect = false;
		}
	}

	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball* pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = &pCurRow[col];

			if (pBall->colorNum <= 0) {
				continue;
			}

			int idx = pBall->colorNum - 1;
			int offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
			float posX = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
			float posY = BALL_RADIUS + row * BALL_RADIUS * 2.0f;

			// 円の当たり判定
			if (CheckCircleHit(mouseX, mouseY, BALL_RADIUS, posX, posY, BALL_RADIUS)) {
				// 二点の距離を測る
				float distance = GetDistance(mouseX, mouseY, posX, posY);
				// 今保存されている値よりも小さい距離だったら
				if (distance < nearestDistance) {
					nearestDistance = distance;
					nearestBallCol = col;
					nearestBallRow = row;
				}

			}
		}
	}

	int findBallNum = 0;
	if (nearestBallRow >= 0 && nearestBallCol >= 0) {
		ballTable[nearestBallRow][nearestBallCol].isSelect = true;

		// 選択ボールとつながっている同色をすべて isSelect = true にする
		// checkSameColorBall の第一引数は Ball& を要求するので渡す（中では使わない）
		findBallNum = checkSameColorBall(ballTable[nearestBallRow][nearestBallCol], nearestBallRow, nearestBallCol);
	}

	if (pushHitKey(KEY_INPUT_RETURN)) {
		if (3 <= findBallNum)
			for (int row = 0; row < BALL_TABLE_ROW; row++) {
				Ball* pCurRow = ballTable[row];
				for (int col = 0; col < BALL_TABLE_COL; col++) {
					Ball* pBall = &pCurRow[col];

					if (ballTable[row][col].isSelect == true) {
						ballTable[row][col].colorNum = 0x000000;
					}
				}
			}

	}


	cannon.update();
}


//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void Draw()
{
	int x, y;
	GetMousePoint(&x, &y);
	float mouseX = (float)x;
	float mouseY = (float)y;

	// 線のみの円でマスを描画する
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball* pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = &pCurRow[col];

			int idx = pBall->colorNum - 1;
			int offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
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
		Ball* pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = &pCurRow[col];


			if (pBall->colorNum <= 0) {
				continue;
			}

			int idx = pBall->colorNum - 1;
			int offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
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
	DrawLine(WINDOW_WIDTH * 0.5f - 200, 0, WINDOW_WIDTH * 0.5f - 200, WINDOW_HEIGHT, 0xFFFFFF);
	DrawLine(WINDOW_WIDTH * 0.5f + 60, 0, WINDOW_WIDTH * 0.5f + 60, WINDOW_HEIGHT, 0xFFFFFF);

	cannon.draw();
}



// それが出来たら再帰的に探索していく
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
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


	DxLib_End();

	return 0;

}
