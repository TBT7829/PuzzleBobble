#include "variable.h"

// ボールの色配列
int colArray[4] =
{
	0xFF0000,	//0: 赤
	0x00FF00,	//1: 緑
	0x0000FF,	//2: 青
	0xFFFFFF,	//3: 白
};

// 一番距離が小さかったボールの行を保存する変数
int nearestBallRow = -1;
// 一番距離が小さかったボールの列を保存する変数
int nearestBallCol = -1;
// 一番距離が小さかった値を保存する変数
float nearestDistance = 0;

// ボールクラスの配列
Ball* ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];