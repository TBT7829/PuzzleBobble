#pragma once
#include"AnimationDataSet.h"
#include"ImageManager.h"

class AnimationRepository
{
private :
	AnimationRepository();
	AnimationRepository(const AnimationRepository& other) = delete;
	AnimationRepository& operator = (const AnimationRepository& other) = delete;

public :
	static AnimationRepository* getInstance();

	static enum AnimationObjectType
	{
		AOT_PLAYER_LEFT,

		AOT_PLAYER_RIGHT,

		AOT_LAUNCH_PAD,
		AOT_CRANK,
		AOT_PIPE,
		AOT_ARROW,

		AOT_BUBBLE_BLUE,

		AOT_BUBBLE_RED,


		AOT_BUBBLE_PURPLE,

		AOT_BUBBLE_GRAY,

		AOT_BUBBLE_YELLOW,

		AOT_BUBBLE_GREEN,

		AOT_BUBBLE_ORANGE,

		AOT_BUBBLE_WHITE,


		AOT_NUM,
	};

	static enum PlayerAnimLeft
	{
		A_PLAYER_LEFT_IDLE,
		A_PLAYER_LEFT_WIN,
		A_PLAYER_LEFT_RELOAD,
		A_PLAYER_LEFT_FAILED,
		A_PLAYER_LEFT_OVER,
		A_PLAYER_LEFT_SHOOT,
	};

	static enum PlayerAnimRight
	{
		A_PLAYER_RIGHT_IDLE,
		A_PLAYER_RIGHT_WIN,
		A_PLAYER_RIGHT_CRANK,
		A_PLAYER_RIGHT_CRANK_REVERSE,
		A_PLAYER_RIGHT_OVER,
	};

	static enum LaunchPadAnim
	{
		A_LAUNCH_PAD,
		A_LAUNCH_PPAD_REVERSE,	
	};

	static enum CrankAnim
	{
		A_CRANK,
		A_CRANK_REVERSE,
	};


	static enum BubbleBlueAnim
	{
		A_BUBBLE_BLUE,
		A_BUBBLE_BLUE_BRIGHT,
		A_BUBBLE_BLUE_BURST,
		A_BUBBLE_BLUE_BANISH,
		A_BUBBLE_BLUE_ENEMY,
	};

	static enum BubbleRedAnim
	{
		A_BUBBLE_RED,
		A_BUBBLE_RED_BRIGHT,
		A_BUBBLE_RED_BURST,
		A_BUBBLE_RED_BANISH,
		A_BUBBLE_RED_ENEMY,
	};

	static enum BubblePurpleAnim
	{
		A_BUBBLE_PURPLE,
		A_BUBBLE_PURPLE_BRIGHT,
		A_BUBBLE_PURPLE_BURST,
		A_BUBBLE_PURPLE_BANISH,
		A_BUBBLE_PURPLE_ENEMY,
	};

	static enum BubbleGrayAnim
	{
		A_BUBBLE_GRAY,
		A_BUBBLE_GRAY_BRIGHT,
		A_BUBBLE_GRAY_BURST,
		A_BUBBLE_GRAY_BANISH,
		A_BUBBLE_GRAY_ENEMY,
	};

	static enum BubbleYellowAnim
	{
		A_BUBBLE_YELLOW,
		A_BUBBLE_YELLOW_BRIGHT,
		A_BUBBLE_YELLOW_BURST,
		A_BUBBLE_YELLOW_BANISH,
		A_BUBBLE_YELLOW_ENEMY,
	};

	static enum BubbleGreenAnim
	{
		A_BUBBLE_GREEN,
		A_BUBBLE_GREEN_BRIGHT,
		A_BUBBLE_GREEN_BURST,
		A_BUBBLE_GREEN_BANISH,
		A_BUBBLE_GREEN_ENEMY,
	};

	static enum BubbleOrangeAnim
	{
		A_BUBBLE_ORANGE,
		A_BUBBLE_ORANGE_BRIGHT,
		A_BUBBLE_ORANGE_BURST,
		A_BUBBLE_ORANGE_BANISH,
		A_BUBBLE_ORANGE_ENEMY,
	};

	static enum BubbleWhiteAnim
	{
		A_BUBBLE_WHITE,
		A_BUBBLE_WHITE_BRIGHT,
		A_BUBBLE_WHITE_BURST,
		A_BUBBLE_WHITE_BANISH,
		A_BUBBLE_WHITE_ENEMY,
	};


private :
	AnimationDataSet ads[AOT_NUM];

public :
	void initAnimationRepository();
	AnimationDataSet* getAds(int AnimobjectType);

};