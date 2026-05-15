#include <stdlib.h>
#include "AnimationDataSet.h"


// 指定した番号のアニメーション情報を取得
AnimationData* AnimationDataSet::getAnimationData(int no)
{
	AnimationData* ret = NULL;
	if (isAnimationDataNoValid(no))
	{
		ret = &animationDataArray[no];
	}

	return ret;
}


// 指定されたアニメーション番号が、有効な物かチェック
// 引数に番号(no)をもらう
bool AnimationDataSet::isAnimationDataNoValid(int no)
{
	bool ret = false;
	if (0 <= no && no < ANIMATION_DATA_NUM)
	{
		ret = true;
	}

	return ret;
}