#pragma once

//---------------------------------------------------------------------------------
//	Float2 クラス
//---------------------------------------------------------------------------------
class Float2
{
	//-------------------------
	// メンバ関数
	//-------------------------
public:
	Float2();									//	デフォルトコンストラクタ
	Float2(float x, float y);					//	引数ありコンストラクタ

	void Clear();								//	ゼロ初期化
	void Set(float x, float y);					//	値のセット
	void Set(Float2& f2);
	float GetLength();							//	長さ取得
	void Normalize();							//	正規化
	void SetLength(float length);				//	長さ設定

	Float2& operator = (const Float2& f2);		//	= 演算子のオーバーロード
	Float2& operator += (const Float2& f2);		//	+= 演算子のオーバーロード
	Float2& operator -= (const Float2& f2);		//	-= 演算子のオーバーロード
	Float2& operator *= (const float f);		//	*= 演算子のオーバーロード
	Float2& operator /= (const float f);		//	/= 演算子のオーバーロード

	//-------------------------
	// メンバ変数
	//-------------------------
public:
	float x;
	float y;

};

//	+ 演算子のオーバーロード
Float2 operator + (const Float2& f2_1, const Float2& f2_2);
//	- 演算子のオーバーロード
Float2 operator - (const Float2& f2_1, const Float2& f2_2);
//	* 演算子のオーバーロード
Float2 operator * (const Float2& f2, const float f);
//	/ 演算子のオーバーロード
Float2 operator / (const Float2& f2, const float f);
