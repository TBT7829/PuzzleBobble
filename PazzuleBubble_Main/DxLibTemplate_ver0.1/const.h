#ifndef __CONST_H__
#define __CONST_H__
	
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

//const int WINDOW_WIDTH = 1024;
//const int WINDOW_HEIGHT = 576;

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 672;

const int WINDOW_WIDTH_HALF = WINDOW_WIDTH * 0.5f;
const int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT * 0.5f;

//const int WINDOW_WIDTH = 320;
//const int WINDOW_HEIGHT = 224;



// 左の壁
const int LEFT_WALL_X = 288;
// 右の壁
const int RIGHT_WALL_X = 672;

// 左の壁から右の壁までの幅
const int PLAY_AREA_WIDTH = RIGHT_WALL_X - LEFT_WALL_X;

// 半径
const int BALL_RADIUS = 24;
// 壁からボールの半径分ずらしている
const int BALL_OFFSET_X = 312;
// バブルの移動スピード
const double BUBBLE_SPEED = 8.0;
// ボール配列の列
const int BALL_TABLE_COL = 8;
// ボール配列の行
const int BALL_TABLE_ROW = 13;

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


#endif