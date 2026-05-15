#ifndef __ANIMATION_DATA_ELEM_H__
#define __ANIMATION_DATA_ELEM_H__


enum AnimationCommand
{
	// アニメーションの終了
	AC_END = 0,
	// 表示画像の切り替え
	AC_SET_IMAGE,
	// 待ち時間の設定
	AC_SET_WAIT,
	// 指定したアニメーションデータへ移行
	AC_JUMP,
	// 音声を再生する
	AC_PLAY_SOUND,
	// 切り出し開始位置を設定
	AC_SET_CROP_BEGIN,
	// 切り出しサイズを設定
	AC_SET_CROP_SIZE,

};


// アニメーションアクションの命令とデータを持つ構造体
// (データしか持たないので構造体で)
struct AnimationDataElem
{
	static const int DATA_ARRAY_LENGTH = 8;

	// あるフレームで、実行・設定したい内容の種類
	int command;

	// 上記のコマンドを実行するのに必要なデータ配列
	int data[DATA_ARRAY_LENGTH];

};






#endif
