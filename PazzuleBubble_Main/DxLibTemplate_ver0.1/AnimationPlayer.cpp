#include <stdlib.h>
#include "Dxlib/dxlib.h"

#include "ImageManager.h"

#include "AnimationDataSet.h"
#include "AnimationPlayer.h"

#include "sound.h"


// コンストラクタ
AnimationPlayer::AnimationPlayer(AnimationDataSet* pAnimDataSet, int x, int y)
{
	// 表示したいアニメーションを設定
	this->pAnimDataSet = pAnimDataSet;
	// アニメーション再生に必要な物
	imgId = 0;
	wait = 0;
	animIdx = 0;
	animNo = 0;
	this->x = x;
	this->y = y;
	// 画像切り出し開始位置
	cropX = 0;
	cropY = 0;
	// 画像切り出しサイズ
	cropW = 0;
	cropH = 0;
	// 再生中で開始
	state = AnimationPlayerState::AP_PLAY;
}

// 現在再生中のアニメーションの番号を取得
int AnimationPlayer::getCurrentAnimationNumber()
{
	return animNo;
}

// 再生するアニメーションの変更
void AnimationPlayer::changeAnimation(int no)
{
	// 指定された番号は正常なものかチェック
	if (pAnimDataSet == NULL && !pAnimDataSet->isAnimationDataNoValid(no))
	{
		// 異常ならここで弾く
		return;
	}

	animNo = no;
	animIdx = 0;
	wait = 0;
	state = AnimationPlayerState::AP_PLAY;
}

void AnimationPlayer::update()
{
	// アニメーションが再生中かどうか
	if (state != AnimationPlayerState::AP_PLAY)
	{
		// 再生中ではないので更新せずに抜ける
		return;
	}

	wait--;
	while (wait <= 0)
	{
		AnimationData* pAd = pAnimDataSet->getAnimationData(animNo);
		// pAdがおかしければ弾く
		if (pAd == NULL)
		{
			return;
		}

		// 現在解釈(処理)するべきアニメーションデータを取得
		const AnimationDataElem* pAde = pAd->getData(animIdx);
		// pAdeがおかしければ弾く
		if (pAde == NULL)
		{
			return;
		}

		// アニメーションデータを取得したら、次のデータを見るように
		// インデックスを一つ進める。
		animIdx++;

		// 現在のコマンドに対する処理
		switch (pAde->command)
		{
		case AnimationCommand::AC_END:
			state = AnimationPlayerState::AP_STOP;
			// whileから抜けてくれないからreturn
			return;
		case AnimationCommand::AC_SET_IMAGE:
			imgId = pAde->data[0];
			break;
		case AnimationCommand::AC_SET_WAIT:
			wait = pAde->data[0];
			break;
		case AnimationCommand::AC_JUMP:
			animIdx = pAde->data[0];
			break;
		case AnimationCommand::AC_PLAY_SOUND:
			//PlaySoundMem(soundArray[pAde->data[0]], DX_PLAYTYPE_BACK);
			break;
		case AnimationCommand::AC_SET_CROP_BEGIN:
			cropX = pAde->data[0];
			cropY = pAde->data[1];
			break;
		case AnimationCommand::AC_SET_CROP_SIZE:
			cropW = pAde->data[0];
			cropH = pAde->data[1];
			break;
		default:
			abort();
			break;
		}


	}
}

// 現在のアニメーションの状態で表示

// 絶対座標で表示
// (基準となるxとyの座標を貰わないので、画面左上、つまり絶対座標で表示を行う)
void AnimationPlayer::render()
{
	render(0, 0);
}

// 相対座標で表示
// (こちらは基準となる座標を貰うので、その座標を基準として、つまり相対座標で表示を行う)
void AnimationPlayer::render(int baseX, int baseY)
{
	

	// 自分の座標を相対座標として扱い、引数に貰った基準となる座標を加えて絶対座標に変換する
	//DrawGraph(x + baseX, y + baseY, imageArray[imgId], TRUE);
	DrawRotaGraph
	(
		x + baseX, y + baseY,
		IMAGE_RATE, 0.0f,
		imgId, TRUE
	);

	/*
	// デバッグ表示
	printfDx("pAnimDataSet: %llu\n", pAnimDataSet);
	printfDx("imgId: %d\n", imgId);
	printfDx("wait: %d\n", wait);
	printfDx("animIdx: %d\n", animIdx);
	printfDx("animNo: %d\n", animNo);
	printfDx("state: %d\n", state);
	printfDx("cropX: %d\n", cropX);
	printfDx("cropY: %d\n", cropY);
	printfDx("cropW: %d\n", cropW);
	printfDx("cropH: %d\n", cropH);
	*/
}