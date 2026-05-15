#include "variable.h"
#include "const.h"
#include "Ball.h"

// ボールの色配列
int colArray[BALL_COLOR_NUM] =
{
	0xFF0000,	//0: 赤
	0x00FF00,	//1: 緑
	0x0000FF,	//2: 青
	0xFFFF00,	//3: 黄
	0xFFA500,	//4: オレンジ
	0xFF00FF,	//5: 紫
	0xC0C0C0,	//6: 銀
	0x1E1E1E,	//7: 灰色
};

// ボールクラスの配列
Ball* ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];


// 一番距離が小さかったボールの行を保存する変数
int nearestBallRow = -1;
// 一番距離が小さかったボールの列を保存する変数
int nearestBallCol = -1;
// 一番距離が小さかった値を保存する変数
float nearestDistance = 0;
// 天井のずれ
 float ceilingOffsetY = 0.0f;


int stage1Data[BALL_DATA_MAX][BALL_TABLE_ROW][BALL_TABLE_COL] =
{
	{
		{0,   0,  1,  0,  2,  1,  5,  0},
		{0,   1,  2,  2,  1,  1,  0, -1},
		{2,   1,  2,  0,  1,  1,  2,  0},
		{1,   0,  0,  1,  2,  2,  1, -1},
		{2,   0,  1,  1,  2,  2,  0,  2},
		{-1, -1, -1,  1, -1, -1, -1, -1},
		{-1, -1, -1,  0, -1, -1, -1, -1},
		{-1, -1,  2, -1, -1, -1, -1, -1},
		{-1, -1, -1,  1, -1, -1, -1, -1},
		{-1, -1,  1, -1, -1, -1, -1, -1},
		{-1, -1,  -1, -1, -1, -1, -1, -1},
		{-1, -1,  -1, -1, -1, -1, -1, -1},
		{-1, -1,  -1, -1, -1, -1, -1, -1}
	},
};

int score;