#include "const.h"
#include "Task.h"
#include "TaskManager.h"
#include "keyManager.h"
#include "hitFunc.h"
#include "dxlib/DxLib.h"

const int BALL_OFFSET_X = 315;
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

// 偶数行 (y, x) または (row, col)
const int dirEven[DIR_MAX][2] = {
	{1, -1},	// 左下
	{1, 0},		// 右下
	{0, -1},	// 左
	{0, 1},		// 右
	{-1, -1},	// 左上
	{-1, 0},	// 右上

};

// 奇数行 (y, x) または (row, col)
const int dirOdd[DIR_MAX][2] = {
	{1, 0},		// 左下
	{1, 1},		// 右下
	{0, -1},	// 左
	{0, 1},		// 右
	{ -1, 0 },	// 左上
	{-1, 1},	// 右上
};

// ボールクラス
class Ball
{
public:
	Ball()
	{
		isCheck = false;
		isSelect = false;
		colNum = 0;
	}
	// 座標を持たせていないため
	// 行(Row)と列(Col)から、画面上のXY座標を計算して第三、四引数に入れてやる
	void GetBubblePos(int row, int col, float& x, float& y) {
		int offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
		x = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
		y = BALL_RADIUS + row * BALL_RADIUS * 2.0f;
	}
	// 探索されているかのフラグ
	bool isCheck;
	bool isSelect;
	int colNum;



};

// しっかりと機能分けなどをするならDrawableを継承させて作る
class FallBall : public Task
{
public:
	FallBall(int taskId, float x, float y, float _wait) : Task(taskId)
	{
		pos.x = x;
		pos.y = y;
		wait = _wait;
		moveVec.x = moveVec.y = 1.0f;
	}
	virtual ~FallBall()
	{

	}

	virtual void update()
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

	virtual void render()
	{
		DrawCircle(pos.x, pos.y, BALL_RADIUS, 0xFF00FF);
	}

	virtual void eventProc(Event* pEvent)
	{

	}

	Float2 pos;
	Float2 moveVec;
	float wait;

};

// 一番距離が小さかったボールの行の数を保存する変数
int nearestBallRow = -1;
// 一番距離が小さかったボールの列の数をを保存する変数
int nearestBallCol = -1;
// 一番距離が小さかった値を保存する変数
float nearestDistance = 0;

// ボールクラスの配列
Ball ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];

// プロトタイプ宣言
void _checkSameColorBall(int row, int col, int& findNum, int color);
void _checkIsolatedBall(int row, int col, int& findNum);

// 直接呼び出される再起処理を開始する関数
int checkSameColorBall(int row, int col)
{
	// 全ボールのチェックを解除
	for (Ball(&row)[8] : ballTable) {
		for (Ball& curBall : row) {
			curBall.isCheck = false;
			curBall.isSelect = false;
		}
	}

	// 見つかった数を保存する変数
	int findNum = 0;

	int colorBuffer = ballTable[row][col].colNum;

	// 再起処理で探索
	_checkSameColorBall(row, col, findNum, colorBuffer);

	return findNum;
}


void _checkSameColorBall(int row, int col, int& findNum, int color)
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
	if (ballTable[row][col].colNum != color) {
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
	//const int dr_even[6] = { -1, -1, 0, 0, 1, 1 };
	//const int dc_even[6] = { -1,  0, -1, 1, -1, 0 }; // 偶数行の隣接
	//const int dr_odd[6] = { -1, -1, 0, 0, 1, 1 };
	//const int dc_odd[6] = { 0,  1, -1, 1,  0, 1 };   // 奇数行の隣接

	//const int* dr = (row % 2 == 0) ? dr_even : dr_odd;
	//const int* dc = (row % 2 == 0) ? dc_even : dc_odd;

	// 現在の行が偶数か奇数かで参照する配列を切り替える
	const int (*dir)[2] = (row % 2 == 0) ? dirEven : dirOdd;

	for (int i = 0; i < 6; ++i) {
		int nr = row + dir[i][0];
		int nc = col + dir[i][1];

		// 再起処理を行う
		_checkSameColorBall(nr, nc, findNum, color);
	}

}


// 0行目の各ボールから再起探索をかけて
// つながっているボールにチェックをつけていく関数
// ボールが消えた後に出来る繋がっていないボールを削除するために利用
int checkIsolatedBall()
{
	// 全ボールのチェックを解除
	for (Ball(&row)[8] : ballTable) {
		for (Ball& curBall : row) {
			curBall.isCheck = false;
			curBall.isSelect = false;
		}
	}

	// 見つかった数を保存する変数
	int findNum = 0;

	// 0行目の各ボールからのみを起点として探索を開始する
	// なぜなら天井が張り付いているボール以外から探索する必要が無いため
	for (int col = 0; col < BALL_TABLE_COL; col++) {
		// 再起処理で繋がっているボールを探索
		_checkIsolatedBall(0, col, findNum);
	}



	return findNum;
}


void _checkIsolatedBall(int row, int col, int& findNum)
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
	// colNumが0以下(ボールが設定されていない)、もしくは
	// 現在参照しようとしている番号の配列の要素がチェック済みかをチェック
	if (ballTable[row][col].colNum <= 0 || ballTable[row][col].isCheck == true) {
		// ボールが無いか既にチェック(探索)済みなのでここで再起処理を終了
		return;
	}

	// 探索されたという判定を付ける
	ballTable[row][col].isCheck = true;

	// 繋がっているボールを見つけたカウントを足す
	findNum++;

	// 隣接6方向の探索
	// offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
	// この描画方式に合わせて偶数行/奇数行で隣接を分ける
	//const int dr_even[6] = { -1, -1, 0, 0, 1, 1 };
	//const int dc_even[6] = { -1,  0, -1, 1, -1, 0 }; // 偶数行の隣接
	//const int dr_odd[6] = { -1, -1, 0, 0, 1, 1 };
	//const int dc_odd[6] = { 0,  1, -1, 1,  0, 1 };   // 奇数行の隣接

	//const int* dr = (row % 2 == 0) ? dr_even : dr_odd;
	//const int* dc = (row % 2 == 0) ? dc_even : dc_odd;

	const int (*dir)[2] = (row % 2 == 0) ? dirEven : dirOdd;

	for (int i = 0; i < 6; ++i) {
		int nr = row + dir[i][0];
		int nc = col + dir[i][1];

		// 再起探索
		_checkIsolatedBall(nr, nc, findNum);
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

	ballTable[0][0].colNum = 1;
	ballTable[0][1].colNum = 1;
	ballTable[0][2].colNum = 2;
	ballTable[0][3].colNum = 1;
	ballTable[0][4].colNum = 3;
	ballTable[0][5].colNum = 2;
	ballTable[0][6].colNum = 3;
	ballTable[0][7].colNum = 1;

	ballTable[1][0].colNum = 1;
	ballTable[1][1].colNum = 2;
	ballTable[1][2].colNum = 3;
	ballTable[1][3].colNum = 3;
	ballTable[1][4].colNum = 2;
	ballTable[1][5].colNum = 2;
	ballTable[1][6].colNum = 1;

	ballTable[2][0].colNum = 3;
	ballTable[2][1].colNum = 2;
	ballTable[2][2].colNum = 3;
	ballTable[2][3].colNum = 1;
	ballTable[2][4].colNum = 2;
	ballTable[2][5].colNum = 2;
	ballTable[2][6].colNum = 3;
	ballTable[2][7].colNum = 1;

	ballTable[3][0].colNum = 2;
	ballTable[3][1].colNum = 1;
	ballTable[3][2].colNum = 1;
	ballTable[3][3].colNum = 2;
	ballTable[3][4].colNum = 3;
	ballTable[3][5].colNum = 3;
	ballTable[3][6].colNum = 2;

	ballTable[4][0].colNum = 3;
	ballTable[4][1].colNum = 1;
	ballTable[4][2].colNum = 2;
	ballTable[4][3].colNum = 2;
	ballTable[4][4].colNum = 3;
	ballTable[4][5].colNum = 3;
	ballTable[4][6].colNum = 1;
	ballTable[4][7].colNum = 3;

	ballTable[5][3].colNum = 2;

	ballTable[6][3].colNum = 1;

	ballTable[7][2].colNum = 3;

	ballTable[8][3].colNum = 2;

	ballTable[9][2].colNum = 2;

}


//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void Update()
{
	TaskManager* pTM = TaskManager::getInstance();

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

			if (pBall->colNum <= 0) {
				continue;
			}

			int idx = pBall->colNum - 1;
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
		findBallNum = checkSameColorBall(nearestBallRow, nearestBallCol);
	}

	// 上記の再起探索で当たり判定が取られたボールとそれに繋がっている色の同じボール、
	// 繋がっているボールの合計が取れている。
	// ENTERを押したときに連続して繋がっているボールの数が3つ以上だった場合に
	// そのボール達を消してあげる
	if (pushHitKey(KEY_INPUT_RETURN)) {
		// 連続して繋がっているボールの数が3以上かチェック
		if (3 <= findBallNum) {
			// 配列の列と行を取るためのforループ
			for (int row = 0; row < BALL_TABLE_ROW; row++) {
				Ball* pCurRow = ballTable[row];
				for (int col = 0; col < BALL_TABLE_COL; col++) {
					Ball* pBall = &pCurRow[col];

					// 今見ている配列の要素の中身のisSelectがtrue(繋がっているボールとして算出されている)なら
					if (pBall->isSelect == true) {
						// そのボールを消す(現在はBall配列でポインタ配列を使っていないかつ
						//					 colNumが0以下のボールは表示されないのでこれが消えてる判定)
						pBall->colNum = 0;
					}
				}

			}

			// if文を通ったということはボールの削除が行われているので
			// 0行目の各ボールから探索をかけて孤立しているボールがいるかどうかを探す
			checkIsolatedBall();

			{
				//	何番目に落ちるかを保存する変数
				float orderNum = 0.0f;
				// パズルボブルAc版では下の行、右側優先の順番でボールが落ちていくので右下からforループを回す
				for (int row = BALL_TABLE_ROW - 1; 0 <= row; row--) {
					Ball* pCurRow = ballTable[row];
					for (int col = BALL_TABLE_COL - 1; 0 <= col; col--) {
						Ball* pBall = &pCurRow[col];
						// ボールがある、かつ探索されていないかをチェック
						if (0 < pBall->colNum && pBall->isCheck == false) {
							// 探索されていないボールが見つかったため、
							// FallBallを生成しながら落とす
							orderNum += 1.0f;

							// 落ちるまでの待ち時間
							int wait = orderNum * 1.0f;
							float x, y;
							pBall->GetBubblePos(row, col, x, y);
							// FallBallを生成
							pTM->add(new FallBall(pTM->generateId(), x, y, wait));
							// Ballを消す
							pBall->colNum = 0;

						}
					}
				}
			}
			

			// if文の処理終了地点
		}



	}

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


	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball* pCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = &pCurRow[col];

			if (pBall->colNum <= 0) {
				continue;
			}

			int idx = pBall->colNum - 1;
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

	DrawCircle(mouseX, mouseY, BALL_RADIUS, 0xFFFFFF);

	DrawLine(WINDOW_WIDTH * 0.5f - 200, 0, WINDOW_WIDTH * 0.5f - 200, WINDOW_HEIGHT, 0xFFFFFF);
	DrawLine(WINDOW_WIDTH * 0.5f + 60, 0, WINDOW_WIDTH * 0.5f + 60, WINDOW_HEIGHT, 0xFFFFFF);
}


TaskManager* pTM = TaskManager::getInstance();


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

		pTM->updateAll();


		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		Draw();
		pTM->renderAll();

		ScreenFlip();
	}


	DxLib_End();

	return 0;
}
