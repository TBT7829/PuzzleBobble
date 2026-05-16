#include"AnimationRepository.h"
#include"DxLib/dxlib.h"


AnimationRepository::AnimationRepository()
{

}

AnimationRepository* AnimationRepository::getInstance()
{
	static AnimationRepository instance;
	return &instance;
}

void AnimationRepository::initAnimationRepository()
{
	ImageManager* pImageManager = ImageManager::getInstance();

	AnimationDataSet* pAds = getAds(AOT_PLAYER_LEFT);
	AnimationData* pAd = pAds->getAnimationData(A_PLAYER_LEFT_IDLE);


	int imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_IDLE);
	pAd->pushSetImage(DerivationGraph(0,0,17,19, imageHandle));
	pAd->pushSetWait(120);
	pAd->pushSetImage(DerivationGraph(17 +15,0,18,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 +15 +18 +15,0,18,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_WIN);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_WIN);
	pAd->pushSetImage(DerivationGraph(0,0,20,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +12,0,21,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +12 +21 +13,0,21,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +12 +21 +13 +21 +13,0,21,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_RELOAD);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_RELOAD);
	pAd->pushSetImage(DerivationGraph(0,0,17,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(17 +14,0,19,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(17 +14 +19 +13,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(17 +14 +19 +13 +21 +13,0,20,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(17 +14 +19 +13 +21 +13 +20 +10,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_FAILED);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_FAILED);
	pAd->pushSetImage(DerivationGraph(0,0,20,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +8,0,26,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +8 +26 +8,0,25,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +8 +26 +8 +25 +8,0,24,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_OVER);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_OVER);
	pAd->pushSetImage(DerivationGraph(0,0,24 ,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(24 +8,0,25,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(24 +8 +25 +8,0,25,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(24 +8 +25 +8 +25 +8,0,25,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_SHOOT);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_SHOOT);
	pAd->pushSetImage(DerivationGraph(0,0,17,18, imageHandle));
	pAd->pushSetWait(3);
	pAd->pushSetImage(DerivationGraph(17 +15,0,23,18, imageHandle));
	pAd->pushSetWait(3);
	pAd->pushSetImage(DerivationGraph(17 +15 +23 +10,0,23,18, imageHandle));
	pAd->pushSetWait(3);
	pAd->pushEnd();


	pAds = getAds(AOT_PLAYER_RIGHT);
	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_IDLE);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_IDLE);

	pAd->pushSetImage(DerivationGraph(0,0,19,19, imageHandle));
	pAd->pushSetWait(120);
	pAd->pushSetImage(DerivationGraph(19 +13,0,19,19, imageHandle));
	pAd->pushSetWait(10);
	pAd->pushSetImage(DerivationGraph(19 +13 +19 +14,0,20,19, imageHandle));
	pAd->pushSetWait(10);
	pAd->pushSetImage(DerivationGraph(19 +13 +19 +14 +20 +12,0,21,19, imageHandle));
	pAd->pushSetWait(10);
	pAd->pushSetImage(DerivationGraph(19 +13 +19 +14 +20 +12 +21 +10,0,22,19, imageHandle));
	pAd->pushSetWait(10);
	pAd->pushSetImage(DerivationGraph(19 +13 +19 +14 +20 +12 +21 +10 +22 +8,0,25,19, imageHandle));
	pAd->pushSetWait(60);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_WIN);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_WIN);

	pAd->pushSetImage(DerivationGraph(0,0,20,19,imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +13,0,20,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +13 +20 +13,0,20,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +13 +20 +13 +20 +13,0,20,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 +13 +20 +13 +20 +13 +20 +12,0,20,19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_CRANK);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_CRANK);
	pAd->pushSetImage(DerivationGraph(0,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14,0,20,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10,0,20,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10 +20 +11,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10 +20 +11 +23 +8,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10 +20 +11 +23 +8 +23 +10,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_CRANK_REVERSE);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_CRANK));
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_CRANK);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10 +20 +11 +23 +8 +23 +10,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10 +20 +11 +23 +8,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10 +20 +11,0,23,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12 +21 +10,0,20,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14 +21 +12,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14 +20 +14,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(21 +14,0,20,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushSetImage(DerivationGraph(0,0,21,19, imageHandle));
	pAd->pushSetWait(2);
	pAd->pushJump(0);


	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_OVER);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_OVER);
	pAd->pushSetImage(DerivationGraph(0,0,22,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(22 +10,0,21,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	pAds = getAds(AOT_LAUNCH_PAD);
	pAd = pAds->getAnimationData(A_LAUNCH_PAD);
	// cycle through launch pad frames1..12
	for (int i =1; i <=12; ++i)
	{
		pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_LAUNCH_PAD_1 + (i -1)));
		pAd->pushSetWait(1);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_LAUNCH_PPAD_REVERSE);
	// reverse order
	for (int i =12; i >=1; --i)
	{
		pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_LAUNCH_PAD_1 + (i -1)));
		pAd->pushSetWait(1);
	}
	pAd->pushJump(0);

	pAds = getAds(AOT_CRANK);
	pAd = pAds->getAnimationData(A_CRANK);
	// simple crank animation: use single image (sprite may contain frames, but fall back to single-handle loop)
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_CRANK);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pAd->pushSetImage(DerivationGraph(i * 16, j * 16, 16, 16, imageHandle));
			pAd->pushSetWait(5);
		}
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_CRANK_REVERSE);
	for (int i = 2; 0 < i; i--)
	{
		for (int j = 2; 0 < j; j--)
		{
			pAd->pushSetImage(DerivationGraph(i * 16, j * 16, 16, 16, imageHandle));
			pAd->pushSetWait(5);
		}
	}
	pAd->pushJump(0);

	// Pipe
	pAds = getAds(AOT_PIPE);
	pAd = pAds->getAnimationData(0);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PIPE);
	pAd->pushSetImage(DerivationGraph(0, 0, 17, 27, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17, 0, 17, 27, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(34, 0, 17, 27, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(51, 0, 14, 27, imageHandle));
	pAd->pushSetWait(5);

	pAd->pushJump(0);

	// Arrow
	pAds = getAds(AOT_ARROW);
	pAd = pAds->getAnimationData(0);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_ARROW));
	pAd->pushSetWait(1);
	pAd->pushJump(0);

	// Bubbles: for each color set basic, bright, burst, banish, enemy

	// Blue
	pAds = getAds(AOT_BUBBLE_BLUE);
	pAd = pAds->getAnimationData(A_BUBBLE_BLUE);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_BLUE);
	pAd->pushSetImage(DerivationGraph(0, 0, 16, 16, imageHandle));
	pAd->pushSetWait(180);
	for (int i = 1; i < 5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 + 1), 0, 16, 16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_BLUE_BRIGHT);
	for (int i = 5; i < 10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 + 1), 0, 16, 16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_BLUE_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_BLUE_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_BLUE_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_BLUE_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_BLUE_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_BLUE_BANISH);
	for (int i = 0; i < 4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 + 1), 0, 32, 31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();


	pAd = pAds->getAnimationData(A_BUBBLE_BLUE_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_BLUE_ENEMY);
	pAd->pushSetImage(DerivationGraph(0, 0, 15, 14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 + 1, 0, 14, 14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 + 1 + 14 + 2, 0, 15, 14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 + 1 + 14 + 2 + 15 + 4, 0, 13, 14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);	

	// Red
	pAds = getAds(AOT_BUBBLE_RED);
	pAd = pAds->getAnimationData(A_BUBBLE_RED);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_RED);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	{
		// red has damaged frames at index3 and4, so use frames1,2 and5
		int idxs[] = {0,1,4};
		for (int k =0; k <3; ++k)
		{
			int i = idxs[k];
			pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
			pAd->pushSetWait(5);
		}
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_RED_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_RED_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_RED_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_RED_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_RED_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_RED_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_RED_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_RED_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_RED_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	// Purple
	pAds = getAds(AOT_BUBBLE_PURPLE);
	pAd = pAds->getAnimationData(A_BUBBLE_PURPLE);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_PURPLE);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	for (int i =1; i <5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_PURPLE_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_PURPLE_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_PURPLE_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_PURPLE_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_PURPLE_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_PURPLE_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_PURPLE_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_PURPLE_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_PURPLE_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	// Gray
	pAds = getAds(AOT_BUBBLE_GRAY);
	pAd = pAds->getAnimationData(A_BUBBLE_GRAY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GRAY);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	for (int i =1; i <5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_GRAY_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_GRAY_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GRAY_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GRAY_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GRAY_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_GRAY_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GRAY_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_GRAY_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GRAY_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	// Yellow
	pAds = getAds(AOT_BUBBLE_YELLOW);
	pAd = pAds->getAnimationData(A_BUBBLE_YELLOW);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_YELLOW);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	for (int i =1; i <5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_YELLOW_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_YELLOW_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_YELLOW_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_YELLOW_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_YELLOW_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_YELLOW_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_YELLOW_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_YELLOW_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_YELLOW_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	// Green
	pAds = getAds(AOT_BUBBLE_GREEN);
	pAd = pAds->getAnimationData(A_BUBBLE_GREEN);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GREEN);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	for (int i =1; i <5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_GREEN_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_GREEN_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GREEN_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GREEN_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GREEN_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_GREEN_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GREEN_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_GREEN_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_GREEN_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	// Orange
	pAds = getAds(AOT_BUBBLE_ORANGE);
	pAd = pAds->getAnimationData(A_BUBBLE_ORANGE);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_ORANGE);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	for (int i =1; i <5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_ORANGE_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_ORANGE_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_ORANGE_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_ORANGE_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_ORANGE_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_ORANGE_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_ORANGE_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_ORANGE_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_ORANGE_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);

	// White
	pAds = getAds(AOT_BUBBLE_WHITE);
	pAd = pAds->getAnimationData(A_BUBBLE_WHITE);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_WHITE);
	pAd->pushSetImage(DerivationGraph(0,0,16,16, imageHandle));
	pAd->pushSetWait(180);
	for (int i =1; i <5; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_WHITE_BRIGHT);
	for (int i =5; i <10; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (16 +1),0,16,16, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushJump(0);

	pAd = pAds->getAnimationData(A_BUBBLE_WHITE_BURST);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_WHITE_BURST_1));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_WHITE_BURST_2));
	pAd->pushSetWait(4);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_WHITE_BURST_3));
	pAd->pushSetWait(6);
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_WHITE_BANISH);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_WHITE_BANISH);
	for (int i =0; i <4; i++)
	{
		pAd->pushSetImage(DerivationGraph(i * (32 +1),0,32,31, imageHandle));
		pAd->pushSetWait(5);
	}
	pAd->pushEnd();

	pAd = pAds->getAnimationData(A_BUBBLE_WHITE_ENEMY);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BUBBLE_WHITE_ENEMY);
	pAd->pushSetImage(DerivationGraph(0,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1,0,14,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2,0,15,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(15 +1 +14 +2 +15 +4,0,13,14, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(0);










}

AnimationDataSet* AnimationRepository::getAds(int AnimobjectType)
{
	if (AOT_NUM < AnimobjectType)
	{
		return NULL;
	}
	return &ads[AnimobjectType];
}
