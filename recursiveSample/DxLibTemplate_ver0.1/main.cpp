#include "dxlib/DxLib.h"
#include "const.h"
#include "keyManager.h"
#include "Ball.h"
#include <memory>
#include <array>

void Init();
void Update();
void Draw();
void Exit();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
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
	Init();



	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		updateKeyState();
		// ↑ システム更新 ↑
		//---------------------------------------

		Update();


		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		Draw();



		ScreenFlip();
	}

	Exit();
	DxLib_End();

	return 0;
}

std::array<std::array< std::unique_ptr<Ball>, 10>, 10> balls;


void Init()
{
	for (int y = 0; y < balls.size(); y++) {
		for (int x = 0; x < balls[y].size(); x++) {
			if (GetRand(10) < 5)
				balls[y][x] = std::make_unique<Ball>(x, y, 20);
		}
	}
	for (int y = 0; y < balls.size(); y++) {
		for (int x = 0; x < balls[y].size(); x++) {
			if (!balls[y][x])
				continue;
			if (y > 0)
				balls[y][x]->AddBranch(balls[y - 1][x].get());
			if (y < balls.size() - 1)
				balls[y][x]->AddBranch(balls[y + 1][x].get());
			if (x > 0)
				balls[y][x]->AddBranch(balls[y][x - 1].get());
			if (x < balls[y].size() - 1)
				balls[y][x]->AddBranch(balls[y][x + 1].get());

		}
	}
}

int select_x = 0;
int select_y = 0;
void Update()
{
	if (pushHitKey(KEY_INPUT_DOWN) && select_y < balls.size() - 1) {
		if (auto& b = balls[select_y][select_x]) {
			b->Unselect();
		}
		select_y++;
		if (auto& b = balls[select_y][select_x]) {
			b->Select();
		}
	}

	if (pushHitKey(KEY_INPUT_UP) && select_y > 0) {
		if (auto& b = balls[select_y][select_x]) {
			b->Unselect();
		}
		select_y--;
		if (auto& b = balls[select_y][select_x]) {
			b->Select();
		}
	}

	if (pushHitKey(KEY_INPUT_RIGHT) && select_x < balls[0].size() - 1) {
		if (auto& b = balls[select_y][select_x]) {
			b->Unselect();
		}
		select_x++;
		if (auto& b = balls[select_y][select_x]) {
			b->Select();
		}
	}

	if (pushHitKey(KEY_INPUT_LEFT) && select_x > 0) {
		if (auto& b = balls[select_y][select_x]) {
			b->Unselect();
		}
		select_x--;
		if (auto& b = balls[select_y][select_x]) {
			b->Select();
		}
	}
	if (pushHitKey(KEY_INPUT_RETURN)) {
		if (auto& b = balls[select_y][select_x]) {
			b->Stack(0);
		}
	}

	if (pushHitKey(KEY_INPUT_SPACE)) {
		if (auto& b = balls[select_y][select_x]) {
			b->Open();
		}
	}

	for (std::array<std::unique_ptr<Ball>, 10>&row : balls) {
		for (std::unique_ptr<Ball>& ball : row) {
			if (ball)
				ball->Update();
		}
	}

}


void Draw()
{
	for (std::array<std::unique_ptr<Ball>, 10>&row : balls) {
		for (std::unique_ptr<Ball>& ball : row) {
			if (ball)
				ball->Draw();
		}
	}

	printfDx("x: %d, y: %d", select_x, select_y);
}

void Exit()
{
	for (std::array<std::unique_ptr<Ball>, 10>&row : balls) {
		for (std::unique_ptr<Ball>& ball : row) {
			ball.reset();
		}
	}
}
