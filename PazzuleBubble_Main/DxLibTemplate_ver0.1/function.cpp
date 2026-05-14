#include "function.h"
#include "Ball.h"
#include "variable.h"
#include "const.h"

#include "dxlib/DxLib.h"

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

// 0行目の各ボールから再起探索をかけて
// つながっているボールにチェックをつけていく関数
// ボールが消えた後に出来る繋がっていないボールを削除するために利用
int checkIsolatedBall()
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

	if (ballTable[row][col] == nullptr) return;

	// 現在参照しようとしている番号の配列の要素がチェック済みかをチェック
	if (ballTable[row][col]->isCheck == true) {
		// ボールが無いか既にチェック(探索)済みなのでここで再起処理を終了
		return;
	}

	// 探索されたという判定を付ける
	ballTable[row][col]->isCheck = true;

	// 繋がっているボールを見つけたカウントを足す
	findNum++;

	// 隣接6方向の探索
	// offsetX = (row % 2 == 0) ? BALL_RADIUS : BALL_RADIUS * 2.0f;
	// この描画方式に合わせて偶数行/奇数行で隣接を分ける
	const int (*dir)[2] = (row % 2 == 0) ? dirEven : dirOdd;

	for (int i = 0; i < 6; ++i) {
		int nr = row + dir[i][0];
		int nc = col + dir[i][1];

		// 再起探索
		_checkIsolatedBall(nr, nc, findNum);
	}

}

// 座標を持たせていないため
// 行(Row)と列(Col)から、画面上のXY座標を計算して第三四引数に入れてやる
Float2 GetBubblePos(int row, int col)
{
	Float2 ret;
	// 奇数なら半径分さらにずらす
	int offsetX = (row % 2 == 0) ? 0 : BALL_RADIUS;

	// X座標を求める
	ret.x = BALL_OFFSET_X + offsetX + col * BALL_RADIUS * 2.0f;
	// Y座標を求める(天井のずれも加算する)
	ret.y = BALL_OFFSET_Y + BALL_RADIUS + row * BALL_RADIUS * 2.0f + ceilingOffsetY;

	return ret;
}

int GetRandomExistColor()
{
	// 存在する色を溜めるバッファ
	int colorBuffer[BALL_COLOR_NUM]; 
	// 今バッファに何種類入っているか
	int bufferCount = 0;             

	// 盤面を探索
	for (int r = 0; r < BALL_TABLE_ROW; r++) {
		for (int c = 0; c < BALL_TABLE_COL; c++) {

			if (ballTable[r][c] == nullptr) continue;

			
			int targetColor = ballTable[r][c]->colorNum;

			// 2. バッファに同じ色番号が既に入っているかチェック
			bool isExits = false;
			for (int i = 0; i < bufferCount; i++) {
				if (colorBuffer[i] == targetColor) {
					isExits = true;
					break;
				}
			}

			// 3. まだ入っていなければバッファに追加
			if (isExits == false) {
				colorBuffer[bufferCount] = targetColor;
				bufferCount++;
			}
			
		}
	}

	// 4. 全消し等でバッファが空なら全色からランダム
	if (bufferCount == 0) {
		return GetRand(BALL_COLOR_NUM - 1) + 1;
	}

	// 5. バッファの中からランダムに選出
	return colorBuffer[GetRand(bufferCount - 1)];
}

void ShiftCeilingDown()
{
	// 天井をボール一行分ずらす
	ceilingOffsetY += BALL_RADIUS * 2.0f;
}