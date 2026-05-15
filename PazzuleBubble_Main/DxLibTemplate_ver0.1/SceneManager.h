#pragma once

#include "scene.h"

//	Sceneクラスを継承し、Sceneクラスのポインタ配列を持ち、Sceneクラスを継承したものを
//	一括管理するSceneManagerクラス
class SceneManager final
{
	//-------------------------
	// 定数
	//-------------------------
public:
	// SCENEの数
	// シーンの種類を列挙
	enum SceneType {
		SCENE_NONE = 0,		//	0：画面なし
		SCENE_TITLE,		//	1：タイトル
		SCENE_GAMESELECT,	//	2：ゲームセレクト
		SCENE_DEMO,			//	3：デモムービー
		SCENE_STAGE,		//	4：ステージ
		SCENE_CLEAR,		//	5：クリア
		SCENE_GAMEOVER,		//	6：ゲームオーバー
		SCENE_CLEAR_TIME,	//	7：クリアタイム
		SCENE_MAX_NUM		//　８：シーンの数
	};


	//-------------------------
	// 静的メンバ関数
	//-------------------------
public:
	// シングルトン
	static SceneManager* getInstance();

	//-------------------------
	// メンバ関数
	//-------------------------
private:
	//	コンストラクタ
	SceneManager();

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// コピーコンストラクタをprivateに封印
	// これをしないと実体が複数作れてしまう
	SceneManager(const SceneManager& obj);

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// 代入演算子をオーバーロードしてprivateに封印
	SceneManager& operator = (const SceneManager& obj);

	//	デストラクタ
	~SceneManager();

public:
	//	切り替え関数
	void changeScene(int nextSceneType);
	//	更新関数
	void update();
	//	描画関数
	void render();

	//-------------------------
	// メンバ関数
	//-------------------------
private:
	// 今のシーンタイプを保存する変数
	Scene* pScene;

public:
	// 現在のシーン
	int currentType;
	// 次のシーン
	int nextType;
	// ゲームが終了するかを見るフラグ
	bool gameFinish;


};
