#include "sceneManager.h"
#include "scene.h"
#include "Stage.h"
#include "variable.h"
#include "const.h"
#include "keyManager.h"



//---------------------------------------------------------------------------------
//	シーン全体の管理処理
//---------------------------------------------------------------------------------

// 以前はグローバル変数scene_numの中に入っている数値(SCENE_TITLE等)でそれにあわせた関数をswitchで呼んでいるだけ。
// scene_numとscene_nextが違う場合に、まず終了処理をかけ、初期化処理をして更新処理を呼んでいる処理だった

//	現在はSceneクラスを継承した必要なシーンのクラスの実体を生成して、
//	SceneManagerがSceneポインタ型で一括管理するように変更

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
SceneManager::SceneManager()
{
	// タイトルから始める
	currentType = SCENE_NONE;
	nextType = SCENE_NONE;
	changeScene(SCENE_STAGE);
}

//---------------------------------------------------------------------------------
//	コピーコンストラクタ
//---------------------------------------------------------------------------------
SceneManager::SceneManager(const SceneManager& obj)
{
	// 複数実体定義できないようにするためにprivateに作られただけなので
	// 内部での処理は不要
}

//---------------------------------------------------------------------------------
//	= 演算子のオーバーロード
//---------------------------------------------------------------------------------
SceneManager& SceneManager::operator = (const SceneManager& obj)
{
	// 複数実体定義できないようにするためにprivateに作られただけなので
	// 内部での処理は不要
	return *this;
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	if (pScene != nullptr) {
		// pSceneをdeleteする
		delete pScene;
		pScene = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	シングルトン
//---------------------------------------------------------------------------------
SceneManager* SceneManager::getInstance()
{
	static SceneManager s_instance;
	return &s_instance;
}

//---------------------------------------------------------------------------------
//	シーンの切り替え関数
//---------------------------------------------------------------------------------
void SceneManager::changeScene(int nextSceneType)
{
	nextType = nextSceneType;


}

//---------------------------------------------------------------------------------
//	更新関数
//---------------------------------------------------------------------------------
void SceneManager::update()
{
	if (nextType != SCENE_NONE) {
		if (currentType != nextType)
		{
			if (pScene != nullptr) {
				// 今のシーンの終了処理を呼ぶ
				pScene->exit();
				// pSceneをdeleteして
				// 今のシーンを終了
				delete pScene;
				pScene = nullptr;
			}

			// 引数に渡されたシーンタイプのシーンクラスを
			// pSceneにnewしてやる
			switch (nextType) {
				// タイトル
			case SceneType::SCENE_TITLE:
				//pScene = new Title;
				break;
				// ゲームセレクト
			case SceneType::SCENE_GAMESELECT:
				//pScene = new GameSelect;
				break;
				// デモ
			case SceneType::SCENE_DEMO:
				//pScene = new Demo;
				break;
				// ステージ
			case SCENE_STAGE:
				pScene = new Stage(stage1Data);
				break;
				// クリア
			case SCENE_CLEAR:
				//pScene = new Clear;
				break;
				// ゲームオーバー
			case SCENE_GAMEOVER:
				//pScene = new GameOver;
				break;
				// クリアタイム
			case SCENE_CLEAR_TIME:
				//pScene = new ClearTime;
				break;
				// 渡されたシーンがおかしい場合
				// 予期せぬ挙動を防ぎ、このswitchでバグが起こっているのがわかるように
				// abort関数を動かす
			default:
				//abort();
				break;
			}

			// 変更し終えたら今のシーンを保存
			currentType = nextType;
		}

		nextType = SCENE_NONE;
	}


	if (pScene != nullptr) {
		// 今のシーンの更新関数を呼ぶ
		pScene->update();
	}



}

//---------------------------------------------------------------------------------
//	描画関数
//---------------------------------------------------------------------------------
void SceneManager::render()
{
	if (pScene != nullptr) {
		// 今のシーンの描画関数を呼ぶ
		pScene->render();
	}

	//SetFontSize(16);

	// 今のシーンの表示
	//DrawFormatString(20, 20, GetColor(255, 255, 255), " [%s]", fieldTextArray[currentType]);
}