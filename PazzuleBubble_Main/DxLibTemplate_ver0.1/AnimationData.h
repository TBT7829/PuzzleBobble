#ifndef __ANIMATION_DATA_H__
#define __ANIMATION_DATA_H__

#include "AnimationdataElem.h"

// 一つのパターンのアニメーション情報を保持するクラス
class AnimationData
{
private:
	// 一つのアニメーションに設定できるコマンドの最大数
	static const int DATA_ELEM_LENGTH = 32;

	// アニメーションデータ配列
	AnimationDataElem dataElemArray[DATA_ELEM_LENGTH];

	// アニメーションデータが持つ命令の個数
	int dataLength;

public:
	// コンストラクタ
	AnimationData();


	// アニメーションデータが満杯でないかチェック
	bool isFull();

	// 指定した番号のアニメーションデータを取得
	// (アニメーションデータをいじられないためにconstを付けておく)
	const AnimationDataElem* getData(int idx);

	// アニメーションの終了命令を追加する
	void pushEnd();

	// アニメーションデータに画像変更命令を追加する
	// dataLengthが今のアニメーションデータの命令の個数を
	// 覚えている
	void pushSetImage(int imageId);

	// アニメーションデータに次のコマンドを解釈し始めるまでの待機時間設定命令を追加する
	void pushSetWait(int wait);

	// アニメーションデータに指定されたコマンドへ移動するジャンプ命令を追加する
	// 移動先の要素数をもらう
	void pushJump(int idx);

	// アニメーションデータに指定された音声を再生する命令を追加する
	void pushPlaySound(int soundId);

	// アニメーションデータに指定された画像切り出し開始位置設定命令を追加する
	void pushSetCropBegin(int x, int y);

	// アニメーションデータに指定された画像切り出しサイズ設定命令を追加する
	void pushSetCropSize(int w, int h);


};







#endif

