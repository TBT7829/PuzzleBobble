#pragma once
#include <array>

class Ball
{
public:
	Ball(int x_, int y_, int radius_);
	void AddBranch(Ball* new_branch);
	void ReleaseBranch(Ball* new_branch);
	bool closed = false;
	bool selected = false;
	void Stack(int frame_);
	void Update();
	void Open();
	void Draw();
	void Select();
	void Unselect();
	int x;
	int y;
	int radius = 5;
	std::array<Ball*, 4> branches = { nullptr };
	unsigned int color = 0x00;
	int frame = -1;
};

