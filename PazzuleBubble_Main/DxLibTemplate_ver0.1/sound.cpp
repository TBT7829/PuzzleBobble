#include "sound.h"

#include "dxlib/DxLib.h"




SoundManager::SoundManager()
{
	initSoundManager();
}


// 音源IDの正当性チェック関数
static bool checkSoundId(int soundId)
{
	if (soundId < 0 || SOUND_INFO_LENGTH < soundId)
	{
		return false;
	}
	return true;
}

// 音源マネージャーの初期化
void SoundManager::initSoundManager()
{
	for (int i = 0; i < SOUND_INFO_LENGTH; i++)
	{
		SoundInfo* pSoundInfo = &soundInfoArray[i];
		pSoundInfo->soundHandle = -1;
		pSoundInfo->soundPath = NULL;
	}
}

SoundManager* SoundManager::getInstance()
{
	static SoundManager manager;
	return &manager;
}


// 音源マネージャーに管理してほしい音源ファイルの場所(ファイル名)を設定
bool SoundManager::setSoundInfo(int soundId, const char* soundPath)
{
	// 音源IDの正当性チェック
	if (checkSoundId(soundId) == false)
	{
		// 見てはいけない要素番号を指定しているので、
		// これ以上登録処理葉できないということでfalseを返す
		return false;
	}

	// 音源ファイルのパスを登録
	soundInfoArray[soundId].soundPath = soundPath;


	return true;
}

// 音源マネージャーに登録されたファイル名をもとに、
// 全音源を読み込む
void SoundManager::loadSoundAll()
{
	for (int i = 0; i < SOUND_INFO_LENGTH; i++)
	{
		SoundInfo* pSoundInfo = &soundInfoArray[i];
		// すでに音源が読み込まれていたら
		// 今回のループは何もせずスキップ
		if (pSoundInfo->soundHandle != -1)
		{
			continue;
		}

		// 音源ファイル名がセットされていなかったら
		// 音源を読み込むことができないのでスキップ
		if (pSoundInfo->soundPath == NULL)
		{
			continue;
		}

		// ここまで来たということは、音源ファイル名がセットされていて、
		// まだ音源が読み込まれていないということなので、
		// ここで音源を読み込んでやる。
		pSoundInfo->soundHandle = LoadSoundMem(pSoundInfo->soundPath);
	}
}

// 音源IDからDrawGraph等で必要な音源識別番号を取得
int SoundManager::getSoundHandle(int soundId)
{
	if (checkSoundId(soundId) == false)
	{
		return -1;
	}
	// 読み込まれた音源の識別番号を返す
	return soundInfoArray[soundId].soundHandle;
}

// 全音源の削除(メモリからの解放)と、音源ファイルパスの無力化
void SoundManager::clearSoundManager()
{
	for (int i = 0; i < SOUND_INFO_LENGTH; i++)
	{
		SoundInfo* pSoundInfo = &soundInfoArray[i];
		int* pSoundHandle = &pSoundInfo->soundHandle;
		// 音源が読み込まれていたら
		if (*pSoundHandle != -1)
		{
			DeleteSoundMem(*pSoundHandle);
		}
		*pSoundHandle = -1;

		// 音源ファイルパスにNULLを設定して、ファイルパスを無効(未設定)にする
		pSoundInfo->soundPath = NULL;
	}
}

void SoundManager::setSoundVolume(int volume)
{
	for (int i = 0; i < SOUND_INFO_LENGTH; i++)
	{
		SoundInfo* pSoundInfo = &soundInfoArray[i];
		if (pSoundInfo->soundHandle == -1 || pSoundInfo->soundPath == NULL)
		{
			continue;
		}
		ChangeVolumeSoundMem(volume, pSoundInfo->soundHandle);
	}
}