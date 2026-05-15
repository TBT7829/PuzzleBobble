#pragma once
#include "const.h"

class Ball;

// ボールの色配列
extern int colArray[BALL_COLOR_NUM];

// ボールクラスの配列
extern Ball* ballTable[BALL_TABLE_ROW][BALL_TABLE_COL];

// 一番距離が小さかったボールの行を保存する変数
extern int nearestBallRow;
// 一番距離が小さかったボールの列を保存する変数
extern int nearestBallCol;
// 一番距離が小さかった値を保存する変数
extern float nearestDistance;

// 天井のずれ
extern float ceilingOffsetY;

extern 	int score;

extern int stage1Data[BALL_DATA_MAX][BALL_TABLE_ROW][BALL_TABLE_COL];