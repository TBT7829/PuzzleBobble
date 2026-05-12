#include "TaskManager.h"
#include "Task.h"
#include <stdlib.h>
#include "dxlib/DxLib.h"

//---------------------------------------------------------
// TaskManagerの処理
//---------------------------------------------------------


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TaskManager::TaskManager()
{
	// 配列の初期化
	for (int i = 0; i < TASK_MAX; i++)
	{
		pTaskArray[i] = NULL;
	}

	// 登録されているtaskの数は0から
	taskNum = 0;

	// 生成するIDの開始点の設定
	lastId = GENERATE_START_ID;
}


//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TaskManager::~TaskManager()
{
	// 全タスクの削除
	for (int i = 0; i < TASK_MAX; i++)
	{
		// ダブルポインタ(ポインタのポインタ)
		Task** ppElem = &pTaskArray[i];
		Task* pTask = *ppElem;

		// NULLじゃなければ何か入っているので
		if (pTask != NULL)
		{
			// deleteしてNULLを代入
			delete pTask;
			*ppElem = NULL;
		}
	}
}


//---------------------------------------------------------
// マネージャにタスクを登録する関数
//---------------------------------------------------------
bool TaskManager::add(Task* pTask)
{
	// すでに配列がいっぱいならもう登録はしない
	if (TASK_MAX <= taskNum)
	{
		return false;
	}

	// 同じIDのタスクが存在しないかチェック
	// NULLじゃない、つまり見つかったら既に存在するので
	if (search(pTask->getTaskId()) != NULL)
	{
		return false;
	}

	// 配列の空きを検索
	Task** ppElem = NULL;
	for (int i = 0; i < TASK_MAX; i++)
	{
		Task** ppCurElem = &pTaskArray[i];


		if (*ppCurElem == NULL)
		{
			// 今の要素数の状態を登録
			ppElem = ppCurElem;
			break;
		}
	}

	// 空きが見つからなかったので何もせず抜ける
	if (ppElem == NULL)
	{
		return false;
	}

	// 空きが見つかったので、貰ったタスクを登録
	*ppElem = pTask;

	// 登録タスク数をカウントアップ
	taskNum++;



	return true;
}

//---------------------------------------------------------
// オブジェクト
//---------------------------------------------------------
bool TaskManager::kill(int id)
{
	// 削除対象のタスクを検索
	Task* pTask = search(id);
	// 削除対象が見つからなかったなら何もせず抜ける
	if (pTask == NULL)
	{
		return false;
	}

	// 削除対象を死亡状態にする
	pTask->deactivate();



	return true;
}

//---------------------------------------------------------
// 更新関数
//---------------------------------------------------------
void TaskManager::updateAll()
{
	for (int i = 0; i < TASK_MAX; i++)
	{
		// 現在参照している要素のポインタを取得
		Task** ppElem = &pTaskArray[i];
		// 現在参照している要素に入っているタスクのポインタ
		Task* pTask = *ppElem;

		// 現在参照されているタスクがNULLなら
		if (pTask == NULL)
		{
			continue;
		}

		// 今の状態を取得
		int curState = pTask->getTaskState();


		// タスク死亡状態か
		if (curState == Task::TASK_STATE::INACTIVE)
		{
			// 死んでいるならタスクを削除
			delete pTask;
			// 現在参照している要素にNULLを設定
			*ppElem = NULL;
			// タスクの登録数をカウントダウン
			taskNum--;

			// 現在参照しているタスクはもう死んでこれ以上やることがないので、
			// 次の要素に進む
			continue;
		}

		// タスク登録後初の実行の更新なら専用の更新処理を呼び出す
		if (curState == Task::TASK_STATE::READY)
		{
			pTask->activate();
		}

		// 現在参照しているタスクの更新処理を行う
		pTask->update();
	}

}

//---------------------------------------------------------
// 描画関数
//---------------------------------------------------------
void TaskManager::renderAll()
{
	for (int i = 0; i < TASK_MAX; i++)
	{
		// 現在参照している要素のポインタを取得
		Task* pTask = pTaskArray[i];

		// 現在参照しているタスクがNULLなら
		if (pTask == NULL)
		{
			continue;
		}

		// 状態を取得
		int state = pTask->getTaskState();

		// 現在のタスクの状態が実行中でなければ表示処理は実行しない
		if (state != Task::TASK_STATE::ACTIVE) //|| state == Task::TASK_STATE::PAUSE) 
		{
			// 今回の要素は中断し配列の検索を続行
			continue;
		}

		// 現在参照しているタスクの表示処理を行う
		pTask->render();

	}
}

//---------------------------------------------------------
// 渡されたIDのタスクを探す
//---------------------------------------------------------
Task* TaskManager::search(int id)
{
	Task* ret = NULL;

	//	渡されたIDが異常な値(0未満)だった場合
	if (id < 0)
	{
		// ここでNULLを返す
		return ret;
	}

	// 配列を探す
	for (int i = 0; i < TASK_MAX; i++)
	{
		// 現在参照している要素のポインタを取得
		Task* pTask = pTaskArray[i];

		// taskのポインタ配列から現在の要素を取ってきて
		// もし中身がNULLだったら
		if (pTask == NULL)
		{
			// 今回の要素は中断し配列の検索を続行
			continue;
		}

		// 指定されたIDが存在すれば
		if (pTask->getTaskId() == id)
		{
			// そのタスクオブジェクトを返す
			ret = pTask;
			break;
		}
	}

	return ret;
}

//---------------------------------------------------------
// タスクマネージャの情報を表示
//---------------------------------------------------------
void TaskManager::dump()
{
	for (int i = 0; i < TASK_MAX; i++)
	{
		// デバッグ用情報表示
		int col = i / 24;
		int row = i % 24;


		DrawFormatString(col * 180, row * 24, 0xFFFFFF, "[%d]: %llu\n", i, pTaskArray[i]);
	}
}