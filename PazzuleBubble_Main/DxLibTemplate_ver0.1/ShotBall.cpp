#include "ShotBall.h"
#include "const.h"
#include "Float2.h"
#include "Task.h"
#include "TaskManager.h"
#include "variable.h"
#include "function.h"
#include "hitFunc.h"
#include "Ball.h"
#include "FallBall.h"

#include "dxlib/DxLib.h"
#include<cmath>

ShotBall::ShotBall(int taskId, Float2 startPos, float angle, int color) : Task(taskId)
{
	pos = startPos;
	colorNum = color;

	moveVec.x = cos(angle) * BUBBLE_SPEED;
	moveVec.y = sin(angle) * BUBBLE_SPEED;
}

void ShotBall::update()
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
	if (pos.y < BALL_OFFSET_Y + ceilingOffsetY + BALL_RADIUS) {
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


				// if文を通ったということはボールの削除が行われているので
				// 0行目の各ボールから探索をかけて孤立しているボールがいるかどうかを探す
				checkIsolatedBall();

				{
					//	何番目に落ちるかを保存する変数
					float orderNum = 0.0f;
					// パズルボブルAc版では下の行、右側優先の順番でボールが落ちていくので右下からforループを回す
					for (int row = BALL_TABLE_ROW - 1; 0 <= row; row--) {
						Ball** pCurRow = ballTable[row];
						for (int col = BALL_TABLE_COL - 1; 0 <= col; col--) {
							Ball* pBall = pCurRow[col];

							if (pBall == nullptr) continue;

							// 探索されていないかをチェック
							if (pBall->isCheck == false) {
								// 探索されていないボールが見つかったため、
								// FallBallを生成しながら落とす
								orderNum += 1.0f;

								// 落ちるまでの待ち時間
								int wait = orderNum * 1.0f;
				
								Float2 setPos = GetBubblePos(row, col);
								// FallBallを生成
								pTM->add(new FallBall(pTM->generateId(), setPos.x, setPos.y, wait, pBall->colorNum));
								// Ballを消す
								pTM->kill(ballTable[row][col]->getTaskId());
								ballTable[row][col] = nullptr;
								

							}
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

void ShotBall::render()
{
	// 色を描画
	int drawColor = colArray[colorNum];
	DrawCircle((int)pos.x, (int)pos.y, BALL_RADIUS, drawColor);
}
