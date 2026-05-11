#include "Ball.h"
#include "dxlib/DxLib.h"
#include <algorithm>

/*
Ball::Ball(int x_, int y_, int radius_)
{
	x = x_;
	y = y_;
	radius = radius_;
	color = 0xffff00;
}

void Ball::AddBranch(Ball* new_branch)
{
	if (!new_branch)
		return;
	auto component = std::find(branches.begin(), branches.end(), new_branch);
	if (component != branches.end())
		return;
	auto empty = std::find(branches.begin(), branches.end(), nullptr);
	(*empty) = new_branch;
}

void Ball::ReleaseBranch(Ball* new_branch)
{
	if (!new_branch)
		return;
	auto component = std::find(branches.begin(), branches.end(), new_branch);
	if (component == branches.end())
		return;
	(*component) = nullptr;
}

void Ball::Stack(int frame_)
{

	closed = true;
	frame = frame_;


	for (auto& b : branches) {
		if (b && !b->closed) {
			b->Stack(frame_ + 30);
		}
	}
}


void Ball::Update()
{
	if (frame > 0)
		frame--;
	if (frame == 0) {
		color = 0xff0000;
		for (Ball*& b : branches) {
			//フレームずらししてるので、ここでReleaseBranchすると、
			if (b) {
				b->ReleaseBranch(this);
				ReleaseBranch(b);
			}

		}

	}

}

void Ball::Open()
{
	closed = false;
	color = 0xffff00;
	frame = -1;
	for (Ball*& b : branches) {
		if (b && b->closed)
			b->Open();
	}
}

void Ball::Draw()
{
	DrawCircle(radius + x * radius * 2, radius + y * radius * 2, radius, selected ? 0x0000ff : color);
}

void Ball::Select()
{
	selected = true;
}

void Ball::Unselect()
{
	selected = false;
}
*/

