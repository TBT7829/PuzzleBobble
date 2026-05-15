#pragma once

//	基底クラスのScene
//	抽象クラスなので実体(インスタンス)を作ることができない。
//	また基底クラスから派生したクラスは、
//	絶対に純粋仮想関数と同じ名前の関数を持つ必要がある。
class Scene
{
	//-------------------------
	// メンバ関数
	//-------------------------
public:
	//	= 0がついてるので純粋仮想関数となり
	//	Sceneクラスは抽象クラスとなる

	// 初期化処理
	virtual void init() = 0;
	//	更新関数
	virtual void update() = 0;
	//	描画関数
	virtual void render() = 0;
	// 終了処理
	virtual void exit() = 0;

};

