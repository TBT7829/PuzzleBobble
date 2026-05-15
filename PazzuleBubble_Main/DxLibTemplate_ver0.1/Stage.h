#pragma once
#include "Scene.h"
#include "Cannon.h"
#include "const.h"

class Ball;

class Stage : public Scene
{
//-------------------------
// メンバ関数
//-------------------------
public:
	// デストラクタ
	virtual ~Stage();

public:
	// コンストラクタ
	Stage(int mapData[BALL_DATA_MAX][BALL_TABLE_ROW][BALL_TABLE_COL]);
	// 初期化関数
	void init();
	// 更新関数
	void update();
	// 描画関数
	void render();
	// 終了関数
	void exit();

//-------------------------
// メンバ変数
//-------------------------
private:
	// タイマー
	//Timer moveDemoTimer;
	
	// 背景保存用の変数
	int imageBG;

	// タイトルテキスト用の画像変数
	//int titleTextIMG;
	
	// 「ボタンを入力してください」と説明を
	// 入れておく変数
	//TextItem explainText;

	// 次のシーン
	int nextScene;
	// 大砲
	Cannon cannon;

};