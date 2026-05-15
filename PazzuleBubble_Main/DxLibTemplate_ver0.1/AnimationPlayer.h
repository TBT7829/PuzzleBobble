#ifndef __ANIMATION_PLAYER_H__
#define __ANIMATION_PLAYER_H__

// 下のAnimationPlayerクラスでは、AnimationDataSetクラスのポインタしか使用してないので、
// AnimationDataSetクラスの詳細な内容を知らなくても良い。
// なぜなら、実体が必要なら中身の詳細が分からないと何Byte取ればいいのか分からないが、
// "ポインタ"を使うには詳細が分からなくても"8( or 4)Byte"用意すれば良いと判断できるからである。

// こういう時には、"こういう型のクラスがあるよ"ということを示す
// "前方宣言"だけ行っても問題ない。(ファイルの読み込みを減らせる)
class AnimationDataSet;

// アニメーション再生クラス
enum AnimationPlayerState
{
	// 再生中
	AP_PLAY = 0,
	// 再生終了
	AP_STOP
};


class AnimationPlayer
{
public:
	// コンストラクタ
	AnimationPlayer(AnimationDataSet* pAnimDataSet, int x, int y);


	// 現在再生中のアニメーションの番号を取得
	int getCurrentAnimationNumber();


	// 再生するアニメーションの変更
	void changeAnimation(int no);

	// 更新関数
	// アニメーションの更新
	void update();

	// 描画関数
	// 現在のアニメーションの状態で表示
	// 絶対座標で表示
	// (基準となるxとyの座標を貰わないので、画面左上、つまり絶対座標で表示を行う)
	void render();
	// 相対座標で表示
	// (こちらは基準となる座標を貰うので、その座標を基準として、つまり相対座標で表示を行う)
	void render(int baseX, int baseY);

	int x;
	int y;

private:
	// どのアニメーションを表示するのか
	AnimationDataSet* pAnimDataSet;

	// アニメーション再生に必要な物
	int imgId;
	int wait;
	int animIdx;
	int animNo;

	// 再生中か終了中か
	int state;

	int cropX;
	int cropY;

	int cropW;
	int cropH;
};


#endif
