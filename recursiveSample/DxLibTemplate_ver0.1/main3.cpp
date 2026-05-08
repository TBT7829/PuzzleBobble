#include "dxlib/DxLib.h"
#include "const.h"
#include "keyManager.h"

// ボールの色配列
int colArray[4] =
{
	0xFF0000,	//0: 赤
	0x00FF00,	//1: 緑
	0x0000FF,	//2: 青
	0xFFFFFF,	//3: 白
};

enum Direction {
	TOP_LEFT = 0,	// 0	
	TOP_RIGHT,		// 1
	LEFT,			// 2
	RIGHT,			// 3
	BOTTOM_LEFT,	// 4
	BOTTOM_RIGHT,	// 5
	DIR_MAX			// 6
};

// 六角形グリッドにおける隣接する6方向のインデックス（偶数行と奇数行で計算が変わる）
// 偶数(y, x)
int dirEven[DIR_MAX][2] = {
	{-1, -1},	// 左上
	{-1, 0},	// 右上
	{0, -1},	// 左
	{0, 1},		// 右
	{1, -1},	// 左下
	{1, 0}		// 右下
};

// 奇数(y, x)
int dirOdd[DIR_MAX][2] = {
	{-1, 0},	// 左上
	{-1, 1},	// 右上
	{0, -1},	// 左
	{0, 1},		// 右
	{1, 0},		// 左下
	{1, 1}		// 右下
};	






class Ball
{
public:
	Ball()
	{
		isCheck = false;
		isSelect = false;
		colNum = 0;
	}
	bool isCheck;
	bool isSelect;
	int colNum;

};


//typedef int Ball;

// ボール配列の列
const int BALL_TABLE_COL = 8;
// ボール配列の行
const int BALL_TABLE_ROW = 10;

// 半径
const int BALL_RADIUS = 16;

// ボールクラスの配列
Ball ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];

// 今選ばれているx, y
int select_x = 0;
int select_y = 0;

void Marking(int row, int col) {
	// 最初にすべてのボールのフラグをfalseにする
	for (int y = 0; y < BALL_TABLE_ROW; y++) {
		for (int x = 0; x < BALL_TABLE_COL; x++) {
			ballTable[y][x].isCheck = false;
		}
	}

	// 偶数行か奇数行かで参照するテーブルを切り替える
	// "int (*dir)[2] は「int[2]型の配列」を指すポインタです!!!!!!!!"
	// dirには選ばれた配列のポインタが入る
	int (*dir)[2] = (row % 2 == 0) ? dirEven : dirOdd;

	for (int i = 0; i < DIR_MAX; i++) {
		int nextRow = row + dir[i][0];
		int nextCol = col + dir[i][1];

		// 配列の範囲内かチェック
		if (nextRow >= 0 && nextRow < BALL_TABLE_ROW && nextCol >= 0 && nextCol < BALL_TABLE_COL) {
			if (nextRow % 2 != 0 && nextCol == BALL_TABLE_COL - 1) continue; // 奇数行の端は存在しない
			
			// 周囲を白(colNum=4)にする
			//ballTable[nextRow][nextCol].colNum = 4;
			ballTable[nextRow][nextCol].isCheck = true;
		}
	}
}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
void Init()
{
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		int& y = row;
		Ball* pCurRow = ballTable[y];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			int& x = col;
			Ball* pBall = &pCurRow[x];

			//*pBall = 0;
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

}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void Update()
{
	if (pushHitKey(KEY_INPUT_DOWN) && select_y < BALL_TABLE_ROW) {
		select_y++;
		
	}

	if (pushHitKey(KEY_INPUT_UP) && select_y > 0) {
		select_y--;
		
	}

	if (pushHitKey(KEY_INPUT_RIGHT) && select_x < BALL_TABLE_COL) {
		select_x++;
	}

	if (pushHitKey(KEY_INPUT_LEFT) && select_x > 0) {
		select_x--;
	}


	Marking(select_y, select_x);
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void Draw()
{
	for (int row = 0; row < BALL_TABLE_ROW; row++) {
		int& y = row;
		Ball* pCurRow = ballTable[y];
		for (int col = 0; col < BALL_TABLE_COL; col++) {
			int& x = col;
			Ball* pBall = &pCurRow[x];

			if (pBall->colNum <= 0) {
				continue;
			}
			
			int idx = pBall->colNum - 1;
			int offsetX = (y % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2;
			int drawColor = (select_x == x && select_y == y) ? 0xFFFF00 : colArray[idx];
			if (pBall->isCheck == true) {
				drawColor = 0xFFFFFF;
			}
			/*if (y % 2 == 0) {
				if (select_x == x && select_y == y) {
					DrawCircle(BALL_RADIUS + x * BALL_RADIUS * 2, BALL_RADIUS + y * BALL_RADIUS * 2, BALL_RADIUS, 0xFFFF00);
				}
				else {
					DrawCircle(BALL_RADIUS + x * BALL_RADIUS * 2, BALL_RADIUS + y * BALL_RADIUS * 2, BALL_RADIUS, colArray[idx]);
				}
				
			}
			else {
				if (select_x == x && select_y == y) {
					DrawCircle((BALL_RADIUS * 2) + x * BALL_RADIUS * 2, BALL_RADIUS + y * BALL_RADIUS * 2, BALL_RADIUS, 0xFFFF00);
				}
				else {
					DrawCircle((BALL_RADIUS * 2) + x * BALL_RADIUS * 2, BALL_RADIUS + y * BALL_RADIUS * 2, BALL_RADIUS, colArray[idx]);
				}
			}*/
			DrawCircle(offsetX + x * BALL_RADIUS * 2, BALL_RADIUS + y * BALL_RADIUS * 2, BALL_RADIUS, drawColor);

		}
	}
	
}

// Marking関数を作ってボールの周りの六か所を見る。
// 選択されているボールの周りの見る場所を白いボールにする。
// 配列外を見そうになったらifで弾く(試験的な動きが有線なので汚いコードでいい)





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