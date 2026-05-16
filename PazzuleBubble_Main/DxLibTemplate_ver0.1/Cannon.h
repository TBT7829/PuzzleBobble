#pragma once
#include "Float2.h"
#include "AnimationPlayer.h"

class Cannon
{
public:
	Cannon();

	void update();

	void draw();

	Float2 pos;
	float angle;

	int curColor;  // 現在装填されている玉の色
	AnimationPlayer curAnimPlayer;

	int nextColor; // 次に装填される玉の色
	AnimationPlayer nextAnimPlayer;

	AnimationPlayer cannonAnimPlayer;
	// アニメーションの状態（0:待機, 1:左回転, 2:右回転）
	int cannonAnimState;

	int arrrowImg;

};