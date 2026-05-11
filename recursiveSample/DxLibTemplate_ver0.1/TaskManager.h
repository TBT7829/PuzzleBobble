#pragma once

// 実体ではなくポインタしか使ってないし処理内容なども書いてないのでので
// "Taskというクラスがある"ということが分かればいいだけなので
// includeではなく前方宣言しておく
class Task;


// タスクマネージャークラス
// Taskクラス継承するクラスを一括管理するクラス
class TaskManager final
{
private:
	// 登録できるタスクオブジェクトの上限数
	static const int TASK_MAX = 128;

	// 開始するTaskのID
	// 32から開始しているので0から31までは自由に使える
	// つまりプレイヤーや背景など変わらないIDはここに使ってあげれる(固定IPと同じ考え)
	static const int GENERATE_START_ID = 32;


	// コンストラクタ( オブジェクトが生成された時に自動的に呼ばれる関数 )
	// 今回はシングルトンパターンを守るためにprivateにする	
	TaskManager();

	// デストラクタ
	~TaskManager();

	// コピーコンストラクタと代入演算子を削除
	// これはシングルトンパターン(生成するインスタンス(実体)を一つに制限するというデザインパターン)を守るための
	// ものであり、これによって代入やコピーでオブジェクトが作れることを防ぐ
	// EventServer(const EventServer& obj);
	// とコピーコンストラクタを定義しておき、ヘッダーファイルで
	// EventServer(const EventServer& obj){}
	// と空関数にしてやってもよいがdeleteする方が早いので今回は この「 = delete」の書き方で

	// コピーコンストラクタを削除
	TaskManager(const TaskManager& obj) = delete;

	// 代入演算子を削除
	TaskManager& operator = (const TaskManager& obj) = delete;


public:
	//-----------------------
	// シングルトン
	//-----------------------
	//「あるクラスのインスタンス（実体）が、全体で常に1つしか存在しないことを保証する」オブジェクト指向プログラミングのデザインパターンの一つ
	// この関数は「"static修飾子のついた自分の型(今回ならTaskManager型)の実体のポインタ"を戻り値として返してくる」
	static inline TaskManager* getInstance()
	{
		// static修飾子の付いメンバ変数なので、プログラムが終了するまでこのTaskManager型のs_instanceという変数の実体は消えない。
		// なので初めてこの関数を呼んだ場合s_instanceが存在しないので作成されて、
		// それ以降何回この関数を呼んだとしても既に存在するTaskManager型のs_instanceが呼ばれることになる。
		static TaskManager s_instance;
		return &s_instance;
	}

	// マネージャにタスクを登録
	bool add(Task* pTask);

	// オブジェクトの削除
	bool kill(int id);

	// 更新関数
	void updateAll();

	// 描画関数
	void renderAll();

	// IDを引数として受け取り、そのIDのタスクを探す
	Task* search(int id);

	// IDを生成する
	inline int generateId()
	{
		return ++lastId;
	}

	// タスクマネージャの情報を表示
	void dump();

private:

	// タスクポインタ配列
	Task* pTaskArray[TASK_MAX];

	// 現在登録されているtaskの数
	int taskNum;

	// ID生成に使用する変数
	int lastId;


};
