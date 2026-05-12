#pragma once
#include "Float2.h"

//---------------------------------------------------------------------------------
//	二点の距離を求める
//---------------------------------------------------------------------------------
float GetDistance(float x1, float y1, float x2, float y2);
// float2クラスを使った二点の距離を測る
float GetDistance(Float2 pos1, Float2 pos2);

// 円同士の当たり判定
bool CheckCircleHit(float x1, float y1, float radius1, float x2, float y2, float radius2);
// 円同士の当たり判定（座標に Float2 を渡すバージョン）
bool CheckCircleHit(Float2 circle1, float radius1, Float2 circle2, float radius2);
