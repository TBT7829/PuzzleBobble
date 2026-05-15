#include <stdlib.h>
#include "AnimationData.h"

// コンストラクタ
AnimationData::AnimationData()
{
	// 登録されたアニメーションデータの個数を0に
	dataLength = 0;

	// 終了コマンドで初期化を行い、誤動作を防止する
	for (int i = 0; i < DATA_ELEM_LENGTH; i++)
	{
		dataElemArray[i].command = AnimationCommand::AC_END;
	}
}

// アニメーションデータが満杯でないかチェック
bool AnimationData::isFull()
{
	bool ret = false;
	if (DATA_ELEM_LENGTH <= dataLength)
	{
		// 満杯
		ret = true;
	}

	return ret;
}

// 指定した番号のアニメーションデータを取得
// (アニメーションデータをいじられないためにconstを付けておく)
const AnimationDataElem* AnimationData::getData(int idx)
{
	AnimationDataElem* ret = NULL;
	// 正常な値なら
	if (0 <= idx && idx < dataLength)
	{
		ret = &dataElemArray[idx];
	}

	return ret;
}

// アニメーションの終了命令を追加する
void AnimationData::pushEnd()
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_END;
	dataLength++;
}

// アニメーションデータに画像変更命令を追加する
// dataLengthが今のアニメーションデータの命令の個数を
// 覚えている
void AnimationData::pushSetImage(int imageId)
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_IMAGE;
	pElem->data[0] = imageId;
	dataLength++;
}

void AnimationData::pushSetWait(int wait)
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_WAIT;
	pElem->data[0] = wait;
	dataLength++;
}

// 移動先の要素数をもらう
void AnimationData::pushJump(int idx)
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_JUMP;
	pElem->data[0] = idx;
	dataLength++;
}

// アニメーションデータに指定された音声を再生する命令を追加する
void AnimationData::pushPlaySound(int soundId)
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_PLAY_SOUND;
	pElem->data[0] = soundId;
	dataLength++;
}

// アニメーションデータに指定された画像切り出し開始位置設定命令を追加する
void AnimationData::pushSetCropBegin(int x, int y)
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_CROP_BEGIN;
	pElem->data[0] = x;
	pElem->data[1] = y;
	dataLength++;
}

// アニメーションデータに指定された画像切り出しサイズ設定命令を追加する
void AnimationData::pushSetCropSize(int w, int h)
{
	// アニメーションデータが満杯ならこれ以上登録はしない。
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_CROP_SIZE;
	pElem->data[0] = w;
	pElem->data[1] = h;
	dataLength++;
}