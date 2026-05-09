#include<iostream>
using namespace std;

#define IS_DEBUG

// 課題1: 配列の範囲外を見ないようにする
// 課題2: 検索対象を右だけではなく左右にできるように

// プロトタイプ宣言
void _dispContinueNum(int idx, int target, int& findNum);


int numArray[] = { 1, 5, 5, 5, 5, 5, 1, 0 };
const int NUM_ARRAY_LENGTH = sizeof(numArray) / sizeof(*numArray);

bool checkArray[NUM_ARRAY_LENGTH];


// 再起探索を開始するための関数(外部からはこちらを直接呼ぶ)
int dispContinueNum(int idx, int target)
{
	// checkArrayをfalseで初期化
	for (bool& elem : checkArray) {
		elem = false;
	}

	int findNum = 0;

	// 再起処理で探索
	_dispContinueNum(idx, target, findNum);


	return findNum;
}

// 指定された値が連続して並んでいる限り表示する関数(直接呼ばない)
// findNUm: 連続して見つかった個数をカウントする参照引数
void _dispContinueNum(int idx, int target, int& findNum)
{
#ifdef IS_DEBUG

	cout << endl << idx << "番目の要素の探索を開始します" << endl;
	system("pause");
#endif 

	// 現在参照しようとしている要素の番号が配列の範囲内に収まっているかをチェック
	if (idx < 0 || NUM_ARRAY_LENGTH <= idx) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		return;
	}

	// 現在参照しようとしている番号の配列の要素がチェック済みかをチェック
	if (checkArray[idx] == true) {
		// 既にチェック(探索)済みなのでここで再起処理を終了
		return;
	}

	checkArray[idx] = true;

	// 指定された番号(idx)の要素に対象の値(target)が保存されているかチェック
	if (numArray[idx] != target) {
		// 指定された値が存在していないのでここで再帰処理を終了
		return;
	}

	
	findNum++;

	// 今の要素(指定された番号)の中身を表示
	cout << numArray[idx] << "," << endl;

	// 前の要素(左)を探索するために要素数から1を引いてもう一度_dispContinueNumを呼び出す
	_dispContinueNum(idx - 1, target, findNum);

	// 次の要素(右)を探索するために要素数から1を足してもう一度_dispContinueNumを呼び出す
	_dispContinueNum(idx + 1, target, findNum);

}


int main()
{
	// 範囲for
	for (int& elem : numArray) {
		cout << elem << "," << flush;
	}
	cout << endl;

	// 配列のstartIdx番目の要素からtargetNumという値が連続している限り表示する再帰処理を呼び出す。
	int startIdx = 3;
	int targetNum = 5;
	
	cout << dispContinueNum(startIdx, targetNum) << "個連続していました。" << endl;;

	

	return 0;
}