#include "const.h"
#include "keyManager.h"
#include "hitFunc.h"
#include "dxlib/DxLib.h"
#include "Task.h"
#include "TaskManager.h"
#include <cmath>

const int WINDOW_WIDTH_HALF = WINDOW_WIDTH * 0.5f;
const int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT * 0.5f;

// 壁からボールの半径分ずらしている
const int BALL_OFFSET_X = 312;

// 左の壁
const int LEFT_WALL_X = 288;
// 右の壁
const int RIGHT_WALL_X = 672;
const int PLAY_AREA_WIDTH = RIGHT_WALL_X - LEFT_WALL_X;

// バブルの移動スピード
const double BUBBLE_SPEED = 8.0;

// ボール配列の列
const int BALL_TABLE_COL = 8;
// ボール配列の行
const int BALL_TABLE_ROW = 13;
// 半径
const int BALL_RADIUS = 24;

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

// 一番距離が小さかったボールの行を保存する変数
int nearestBallRow = -1;
// 一番距離が小さかったボールの列を保存する変数
int nearestBallCol = -1;
// 一番距離が小さかった値を保存する変数
float nearestDistance = 0;

// プロトタイプ宣言
int checkSameColorBall(int row, int col);
void _checkSameColorBall(int row, int col, int& findNum, int color);
Float2 GetBubblePos(int row, int col);

class Cannon;
class Ball;



// ボールクラスの配列
Ball* ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];

class Ball : public Task
{
public:
	Ball(int taskId) : Task(taskId)
	{
		pos.x = pos.y = 0.0f;
		
		isCheck = false;
		isSelect = false;
		colorNum = 0;
		
	}
	Ball(int taskId, Float2 SetPos) : Task(taskId)
	{
		pos = SetPos;
		isCheck = false;
		isSelect = false;
		colorNum = 0;
	}
	void update()
	{
		
	}
	void render()
	{

	}
	void eventProc(Event* pEvent)
	{

	}

	
	Float2 pos;
	bool isCheck;
	bool isSelect;
	int colorNum;

};

class ShotBall : public Task
{
public:
	ShotBall(int taskId, Float2 startPos, float angle, int color) : Task(taskId)
	{
		pos = startPos;
		colorNum = color;

		moveVec.x = cos(angle) * BUBBLE_SPEED;
		moveVec.y = sin(angle) * BUBBLE_SPEED;
	}
	void update()
	{
		// 移動
		pos.x += moveVec.x;
		pos.y += moveVec.y;

		// 左の壁に当たった場合
		if (pos.x < LEFT_WALL_X + BALL_RADIUS) {
			// めりこまないようにする
			pos.x = LEFT_WALL_X + BALL_RADIUS;
			// Xの移動方向を反転
			moveVec.x *= -1.0f;
		}
		// 右の壁に当たった場合
		else if (RIGHT_WALL_X - BALL_RADIUS < pos.x) {
			// めりこまないようにする
			pos.x = RIGHT_WALL_X - BALL_RADIUS;
			// Xの移動方向を反転
			moveVec.x *= -1.0f;

		}

		// ボールか天井との当たり判定
		bool isHit = false;
		// 天井に当たったかどうか
		if (pos.y < BALL_RADIUS) {
			isHit = true;
		}
		// 既存のボールとの当たり判定
		else {
			// 全ての固定ボールと衝突判定
			for (int r = 0; r < BALL_TABLE_ROW; r++) {
				for (int c = 0; c < BALL_TABLE_COL; c++) {
					//	もし配列の中身がnullptrなら弾く
					if (ballTable[r][c] == nullptr) continue;

					// 既存のボールの座標を取得
					Float2 taragetPos = GetBubblePos(r, c);
					// 今のshotBallと当たり判定
					if (CheckCircleHit(pos.x, pos.y, BALL_RADIUS,
						taragetPos.x, taragetPos.y, BALL_RADIUS))
					{
						// 当たっていたら
						isHit = true;
						break;
					}

				}
			}
		}

		if (isHit == true) {
			// 距離の初期化
			nearestDistance = 10000.0f;
			nearestBallRow = -1;
			nearestBallCol = -1;

			// 全ての空きマスの探索
			for (int r = 0; r < BALL_TABLE_ROW; r++) {
				for (int c = 0; c < BALL_TABLE_COL; c++)
				{
					// 中身があるならここではじく
					if (ballTable[r][c] != nullptr) continue;
					// 奇数行の右端は入れないので弾く
					if (r % 2 != 0 && BALL_TABLE_COL - 1 <= c) continue;

					// 今見ているボールの座標を取る
					Float2 cellPos = GetBubblePos(r, c);
					// 距離の計算
					float distance = GetDistance(pos.x, pos.y, cellPos.x, cellPos.y);
					//今保存されている値よりも小さい距離だったら
					if (distance < nearestDistance) {
						nearestDistance = distance;
						nearestBallCol = c;
						nearestBallRow = r;
					}
				}
			}

			// 一番近い空きマスが見つかったら、そこに固定ボールを生成
			if (nearestBallRow != -1 && nearestBallCol != -1) {
				TaskManager* pTM = TaskManager::getInstance();
				ballTable[nearestBallRow][nearestBallCol] = new Ball(pTM->generateId());
				ballTable[nearestBallRow][nearestBallCol]->colorNum = this->colorNum;
				pTM->add(ballTable[nearestBallRow][nearestBallCol]);

				int findBallNum = 0;
				// 選択ボールとつながっている同色をすべて isSelect = true にする
				findBallNum = checkSameColorBall(nearestBallRow, nearestBallCol);
				// 三つ以上つながっていれば削除
				if (3 <= findBallNum) {
					for (int row = 0; row < BALL_TABLE_ROW; row++) {
						Ball** ppCurRow = ballTable[row];
						for (int col = 0; col < BALL_TABLE_COL; col++) {
							Ball* pBall = ppCurRow[col];
							if (pBall == nullptr) continue;

							if (ballTable[row][col]->isSelect == true) {
								pTM->kill(ballTable[row][col]->getTaskId());
								ballTable[row][col] = nullptr;
							}
						}
					}

				}
			}

			// 自分（弾）を消す
			TaskManager::getInstance()->kill(getTaskId());
		}

		

		// 更新処理の終了
	}
	void render()
	{
		// 色を描画
		int drawColor = colArray[colorNum - 1];
		DrawCircle((int)pos.x, (int)pos.y, BALL_RADIUS, drawColor);
	}
	void eventProc(Event* pEvent)
	{

	}

	Float2 pos;
	Float2 moveVec;
	int colorNum;

};

class Cannon
{
public:
	Cannon()
	{
		pos.x = WINDOW_WIDTH_HALF;
		pos.y = WINDOW_HEIGHT - 60;
		angle = 3.14159265 / 2.0; // 90度(真上)(-1.57f)
		nextColor = GetRand(2) + 1;
	}

	void update()
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

	void draw()
	{
		DrawCircle(pos.x, pos.y, BALL_RADIUS, colArray[nextColor - 1]);
		// 大砲（発射の軌道線）を描画
		DrawLine(pos.x, pos.y, 
			pos.x + (int)(cos(angle) * 50), 
			pos.y - (int)(sin(angle) * 50), 
			GetColor(255, 255, 255), 4);
	}

	Float2 pos;
	float angle;
	int nextColor; // 装填されている玉の色
};


Cannon cannon;


// 直接呼び出される再起処理を開始する関数
int checkSameColorBall(int _row, int _col)
{
	// 全ボールのチェックを解除
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		Ball** ppCurRow = ballTable[row];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			Ball* pBall = ppCurRow[col];

			if (pBall == nullptr) continue;

			pBall->isCheck = false;
			pBall->isSelect = false;
		}
	}

	// 見つかった数を保存する変数
	int findNum = 0;

	int colorBuffer = ballTable[_row][_col]->colorNum;

	// 再起処理で探索
	_checkSameColorBall(_row, _col, findNum, colorBuffer);


	return findNum;
}


void _checkSameColorBall(int _row, int _col, int& findNum, int color)
{
	// 現在参照しようとしている行の番号が配列の範囲内に収まっているかをチェック
	if (_row < 0 || BALL_TABLE_ROW <= _row) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		return;
	}
	// 現在参照しようとしている列の番号が配列の範囲内に収まっているかをチェック
	if (_col < 0 || BALL_TABLE_COL <= _col) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		return;
	}

	if (ballTable[_row][_col] == nullptr) return;

	// 現在参照しようとしている番号の配列の要素がチェック済みかをチェック
	if (ballTable[_row][_col]->isCheck == true) {
		// 既にチェック(探索)済みなのでここで再起処理を終了
		return;
	}

	ballTable[_row][_col]->isCheck = true;

	// 指定された要素の色が同じかチェック
	if (ballTable[_row][_col]->colorNum != color) {
		// 色が同じでは無いのでここで再帰処理を終了
		return;
	}

	// 同じ色を見つけた数をカウント
	findNum++;
	// 対象として
	ballTable[_row][_col]->isSelect = true;

	// 隣接6方向の探索
	// offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
	// この描画方式に合わせて偶数行/奇数行で隣接を分ける
	const int dr_even[6] = { -1, -1, 0, 0, 1, 1 };
	const int dc_even[6] = { -1,  0, -1, 1, -1, 0 }; // 偶数行の隣接
	const int dr_odd[6] = { -1, -1, 0, 0, 1, 1 };
	const int dc_odd[6] = { 0,  1, -1, 1,  0, 1 }; // 奇数行の隣接

	const int* dr = (_row % 2 == 0) ? dr_even : dr_odd;
	const int* dc = (_row % 2 == 0) ? dc_even : dc_odd;

	for (int i = 0; i < 6; ++i) {
		int nr = _row + dr[i];
		int nc = _col + dc[i];
		// 再起処理を行う
		_checkSameColorBall(nr, nc, findNum, color);
	}

}

// 座標を持たせていないため
// 行(Row)と列(Col)から、画面上のXY座標を計算して第三四引数に入れてやる
Float2 GetBubblePos(int row, int col)
{
	Float2 ret;
	int offsetX = (row % 2 == 0) ? 0 : BALL_RADIUS;
	ret.x = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
	ret.y = BALL_RADIUS + row * BALL_RADIUS * 2.0f;
	return ret;
}


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
	
	//int x, y;
	//GetMousePoint(&x, &y);
	//float mouseX = (float)x;
	//float mouseY = (float)y;


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

	int x, y;
	GetMousePoint(&x, &y);
	float mouseX = (float)x;
	float mouseY = (float)y;

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
