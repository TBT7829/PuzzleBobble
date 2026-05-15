#pragma once

#include "Float2.h"

// 直接呼び出される再起処理を開始する関数
int checkSameColorBall(int _row, int _col);
void _checkSameColorBall(int _row, int _col, int& findNum, int color);

// 0行目の各ボールから再起探索をかけて
// つながっているボールにチェックをつけていく関数
// ボールが消えた後に出来る繋がっていないボールを削除するために利用
int checkIsolatedBall();
void _checkIsolatedBall(int row, int col, int& findNum);

// 座標を持たせていないため
// 行(Row)と列(Col)から、画面上のXY座標を計算して第三四引数に入れてやる
Float2 GetBubblePos(int row, int col);

int GetRandomExistColor();

void ShiftCeilingDown();

bool CheckGameOver();