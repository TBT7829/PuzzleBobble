#ifndef __ANIMATION_DATA_SET_H__
#define __ANIMATION_DATA_SET_H__

#include "AnimationData.h"

// 複数のAnimationDataを持ち、複数のアニメーションを切り替えらえるようにするためのクラス
class AnimationDataSet
{
private:
	static const int ANIMATION_DATA_NUM = 8;

public:
	// 指定した番号のアニメーション情報を取得
	AnimationData* getAnimationData(int no);

	// 指定されたアニメーション番号が、有効な物かチェック
	// 引数に番号(no)をもらう
	bool isAnimationDataNoValid(int no);


private:
	AnimationData animationDataArray[ANIMATION_DATA_NUM];

};





#endif

