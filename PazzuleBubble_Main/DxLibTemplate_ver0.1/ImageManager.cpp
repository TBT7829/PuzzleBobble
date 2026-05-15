#include"DxLib/dxlib.h"
#include"imageManager.h"


ImageManager::ImageManager()
{
	initImageManager();
}


// 画像IDの正当性チェック関数
static bool checkImageId(int imageId)
{
	if (imageId < 0 || IMAGE_INFO_LENGTH < imageId)
	{
		return false;
	}
	return true;
}

// 画像マネージャーの初期化
void ImageManager::initImageManager()
{
	for (int i = 0; i < IMAGE_INFO_LENGTH; i++)
	{
		ImageInfo* pImageInfo = &imageInfoArray[i];
		pImageInfo->imageHandle = -1;
		pImageInfo->imagePath = NULL;
	}
}

ImageManager* ImageManager::getInstance()
{
	static ImageManager manager;
	return &manager;
}


// 画像マネージャーに管理してほしい画像ファイルの場所(ファイル名)を設定
bool ImageManager::setImageInfo(int imageId, const char* imagePath)
{
	// 画像IDの正当性チェック
	if (checkImageId(imageId) == false)
	{
		// 見てはいけない要素番号を指定しているので、
		// これ以上登録処理葉できないということでfalseを返す
		return false;
	}

	// 画像ファイルのパスを登録
	imageInfoArray[imageId].imagePath = imagePath;


	return true;
}

// 画像マネージャーに登録されたファイル名をもとに、
// 全画像を読み込む
void ImageManager::loadImageAll()
{
	for (int i = 0; i < IMAGE_INFO_LENGTH; i++)
	{
		ImageInfo* pImageInfo = &imageInfoArray[i];
		// すでに画像が読み込まれていたら
		// 今回のループは何もせずスキップ
		if (pImageInfo->imageHandle != -1)
		{
			continue;
		}

		// 画像ファイル名がセットされていなかったら
		// 画像を読み込むことができないのでスキップ
		if (pImageInfo->imagePath == NULL)
		{
			continue;
		}

		// ここまで来たということは、画像ファイル名がセットされていて、
		// まだ画像が読み込まれていないということなので、
		// ここで画像を読み込んでやる。
		pImageInfo->imageHandle = LoadGraph(pImageInfo->imagePath);
	}
}

// 画像IDからDrawGraph等で必要な画像識別番号を取得
int ImageManager::getImageHandle(int imageId)
{
	if (checkImageId(imageId) == false)
	{
		return -1;
	}
	// 読み込まれた画像の識別番号を返す
	return imageInfoArray[imageId].imageHandle;
}

// 全画像の削除(メモリからの解放)と、画像ファイルパスの無力化
void ImageManager::clearImageManager()
{
	for (int i = 0; i < IMAGE_INFO_LENGTH; i++)
	{
		ImageInfo* pImageInfo = &imageInfoArray[i];
		int* pImageHandle = &pImageInfo->imageHandle;
		// 画像が読み込まれていたら
		if (*pImageHandle != -1)
		{
			DeleteGraph(*pImageHandle);
		}
		*pImageHandle = -1;

		// 画像ファイルパスにNULLを設定して、ファイルパスを無効(未設定)にする
		pImageInfo->imagePath = NULL;
	}
}
