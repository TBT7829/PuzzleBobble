#include<iostream>
using namespace std;


int numArray[8] = { 1, 3, 5, 5, 2, 4, 4, 4};
bool checkArray[8];

// 指定された値が連続して並んでいる限り表示
// findNUm: 連続して見つかった個数をカウントする参照引数
void dispContinueNum(int idx, int target, int& findNum)
{
	// 指定された番号(idx)の要素に対象の値(target)が保存されているかチェック
	if (numArray[idx] != target) {
		// 指定された値が存在していないのでここで再帰処理を終了
		return;
	}

	findNum++;

	// 今の要素(指定された番号)の中身を表示
	cout << numArray[idx] << "," << flush;

	// 次の要素(右)を探索するために要素数に1を足してもう一度dispContinueNumを呼び出す
	dispContinueNum(idx + 1, target, findNum);

}


int main()
{
	// 範囲for
	for (int& elem : numArray) {
		cout << elem << "," << flush;
	}
	cout << endl;

	// 配列のstartIdx番目の要素からtargetNumという値が連続している限り表示する再帰処理を呼び出す。
	int startIdx = 5;
	int targetNum = 4;
	int findNum = 0;
	dispContinueNum(startIdx, targetNum, findNum);

	cout << findNum << "個連続していました。" << endl;;

	return 0;
}