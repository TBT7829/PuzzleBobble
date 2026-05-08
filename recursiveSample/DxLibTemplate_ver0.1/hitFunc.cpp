#include "Float2.h"
#include "hitFunc.h"
#include<cmath>


//---------------------------------------------------------------------------------
//	二点の距離を求める（ float バージョン）
//---------------------------------------------------------------------------------
float GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

//---------------------------------------------------------------------------------
//	二点の距離を求める
//---------------------------------------------------------------------------------
// float2クラスを使った二点の距離を測る
float GetDistance(Float2 pos1, Float2 pos2)
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float distance = sqrtf(x * x + y * y);
	return distance;
}

//---------------------------------------------------------------------------------
//	円同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleHit(float x1, float y1, float radius1, float x2, float y2, float radius2)
{
	float distance = GetDistance(x1, y1, x2, y2);
	float radius = radius1 + radius2;
	if (distance <= radius) {
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------
//	円同士の当たり判定（座標に float2 を渡す）
//---------------------------------------------------------------------------------
bool CheckCircleHit(Float2 circle1, float radius1, Float2 circle2, float radius2)
{
	float distance = GetDistance(circle1, circle2);
	float radius = radius1 + radius2;
	if (distance <= radius) {
		return true;
	}
	return false;
}