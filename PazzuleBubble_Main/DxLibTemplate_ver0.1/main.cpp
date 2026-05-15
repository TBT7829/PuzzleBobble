#include "Ball.h"
#include "ShotBall.h"
#include "Cannon.h"
#include "TaskManager.h"
#include "variable.h"
#include "function.h"
#include "keyManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "sound.h"

#include "dxlib/DxLib.h"
#include <cmath>





// それが出来たら再帰的に探索していく
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// シーンマネージャーのシングルトンでインスタンスを取得
	SceneManager* pSceneManager = SceneManager::getInstance();

	SoundManager* pSM = SoundManager::getInstance();

	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	// 垂直同期を有効にする
	SetWaitVSyncFlag(TRUE);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);


	//---------------------------------------
	// 変数の作成や初期化、その他初期設定
	// ↓ システム初期化 ↓
	initKeyManager();
	// ↑ システム初期化 ↑
	//---------------------------------------
	ImageManager* pImageManager = ImageManager::getInstance();

	// BG(背景)
	pImageManager->setImageInfo(ImageManager::IMAGE_BG, "stage1_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_LEFT_IDLE, "player_left_idle.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_LEFT_WIN, "player_left_win.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_LEFT_RELOAD, "player_left_reload.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_LEFT_FAILED, "player_left_failed.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_LEFT_OVER, "player_left_over.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_LEFT_SHOOT, "player_left_shoot.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_RIGHT_IDLE, "player_right_idle.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_RIGHT_WIN, "player_right_win.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_RIGHT_CRANK, "player_right_crank.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PLAYER_RIGHT_OVER, "player_right_over.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BG, "stage1_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_GROUND, "scaffold1_3.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_NUMBER, "number.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BANDLE_1, "bandle_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BANDLE_2, "bandle_2.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_1, "launch_pad_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_2, "launch_pad_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_3, "launch_pad_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_4, "launch_pad_4.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_5, "launch_pad_5.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_6, "launch_pad_6.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_7, "launch_pad_7.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_8, "launch_pad_8.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_9, "launch_pad_9.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_10, "launch_pad_10.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_11, "launch_pad_11.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_LAUNCH_PAD_12, "launch_pad_12.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_CRANK, "crank.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_PIPE, "pipe.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_ARROW, "arrow_1.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_BLUE, "bubble_blue.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_BLUE_BURST_1, "bubble_blue_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_BLUE_BURST_2, "bubble_blue_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_BLUE_BURST_3, "bubble_blue_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_BLUE_BANISH, "bubble_blue_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_BLUE_ENEMY, "bubble_blue_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_RED, "bubble_red.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_RED_BURST_1, "bubble_red_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_RED_BURST_2, "bubble_red_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_RED_BURST_3, "bubble_red_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_RED_BANISH, "bubble_red_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_RED_ENEMY, "bubble_red_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_PURPLE, "bubble_purple.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_PURPLE_BURST_1, "bubble_purple_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_PURPLE_BURST_2, "bubble_purple_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_PURPLE_BURST_3, "bubble_purple_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_PURPLE_BANISH, "bubble_purple_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_PURPLE_ENEMY, "bubble_purple_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GRAY, "bubble_gray.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GRAY_BURST_1, "bubble_gray_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GRAY_BURST_2, "bubble_gray_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GRAY_BURST_3, "bubble_gray_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GRAY_BANISH, "bubble_gray_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GRAY_ENEMY, "bubble_gray_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_YELLOW, "bubble_yellow.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_YELLOW_BURST_1, "bubble_yellow_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_YELLOW_BURST_2, "bubble_yellow_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_YELLOW_BURST_3, "bubble_yellow_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_YELLOW_BANISH, "bubble_yellow_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_YELLOW_ENEMY, "bubble_yellow_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GREEN, "bubble_green.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GREEN_BURST_1, "bubble_green_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GREEN_BURST_2, "bubble_green_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GREEN_BURST_3, "bubble_green_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GREEN_BANISH, "bubble_green_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_GREEN_ENEMY, "bubble_green_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_ORANGE, "bubble_orange.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_ORANGE_BURST_1, "bubble_orange_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_ORANGE_BURST_2, "bubble_orange_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_ORANGE_BURST_3, "bubble_orange_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_ORANGE_BANISH, "bubble_orange_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_ORANGE_ENEMY, "bubble_orange_enemy.png");

	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_WHITE, "bubble_white.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_WHITE_BURST_1, "bubble_white_burst_1.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_WHITE_BURST_2, "bubble_white_burst_2.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_WHITE_BURST_3, "bubble_white_burst_3.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_WHITE_BANISH, "bubble_white_banish.png");
	pImageManager->setImageInfo(ImageManager::IMAGE_BUBBLE_WHITE_ENEMY, "bubble_white_enemy.png");

	pImageManager->loadImageAll();

	pSM->setSoundInfo(SoundManager::SOUND_STAGE, "PB_PLAY_BGM.m4a");
	pSM->setSoundInfo(SoundManager::SOUND_SHOT, "SE_SHOT.m4a");
	pSM->setSoundInfo(SoundManager::SOUND_FALL, "SE_FALLBALL.m4a");
	pSM->setSoundInfo(SoundManager::SOUND_BURST , "SE_BURST.m4a");
	pSM->setSoundInfo(SoundManager::SOUND_ADSORPTION, "SE_ADSORPTION.m4a");

	pSM->loadSoundAll();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		updateKeyState();
		// ↑ システム更新 ↑
		//---------------------------------------
		SoundManager::getInstance()->setSoundVolume(100);
		PlaySoundMem(SoundManager::getInstance()->getSoundHandle(SoundManager::SOUND_STAGE), DX_PLAYTYPE_LOOP, FALSE);
		// シーンマネージャーの更新関数
		pSceneManager->update();



		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		// シーンマネージャーの描画関数
		pSceneManager->render();


		ScreenFlip();
	}

	
	// 画像の解除
	ImageManager::getInstance()->clearImageManager();
	pSM->clearSoundManager();

	DxLib_End();

	return 0;

}