#include<iostream>
using namespace std;

#define IS_DEBUG

#ifdef IS_DEBUG
	#define DBG_PRINT( ... ) {printf( __VA_ARGS__ ); system("pause");}
#else
	#define DBG_PRINT( ... ) 
#endif

// 課題: 下の1dArray_2のコードを書き換えて二次元配列で再起探索を行う

// Todo
//	二次元配列の作成、見る順番を決める(先ほどの一次元配列では左→右。例: 上→左→下→右など)


// 課題1: 配列の範囲外を見ないようにする
// 課題2: 検索対象を右だけではなく左右にできるように
// 課題3: 2dArrayを作成して二次元配列で行う



// プロトタイプ宣言
void _dispContinueNum(int row, int col, int target, int& findNum);

int numArray[4][8] = {
	{1, 5, 5, 5, 5, 5, 4, 4},
	{1, 3, 2, 5, 5, 2, 6, 1},
	{3, 2, 1, 5, 5, 5, 1, 3},
	{2, 3, 5, 5, 1, 6, 3, 3}
};

// 二次元配列の行の最大数(縦)
const int NUM_ARRAY_ROW = sizeof(numArray) / sizeof(numArray[0]);
// 二次元配列の列の最大数(横)
const int NUM_ARRAY_COL = sizeof(numArray[0]) / sizeof(numArray[0][0]);


bool checkArray[NUM_ARRAY_ROW][NUM_ARRAY_COL];



// 直接呼び出される再起処理を開始する関数
int dispContinueNum(int row, int col, int target)
{
	// checkArrayをfalseで初期化
	for (bool(&row)[8] : checkArray) {
		for (bool& col : row) {
			col = false;
		}

	}
	

	int findNum = 0;

	// 再起処理で探索
	_dispContinueNum(row, col, target, findNum);


	return findNum;
}

// 指定された値が連続して並んでいる限り表示する関数(直接呼ばない)
// findNUm: 連続して見つかった個数をカウントする参照引数
void _dispContinueNum(int row, int col, int target, int& findNum)
{
	DBG_PRINT("%d行%d列目の探索を開始します。\n", row, col);


	// 現在参照しようとしている行の番号が配列の範囲内に収まっているかをチェック
	if (row < 0 || NUM_ARRAY_ROW <= row) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		DBG_PRINT( "配列外を参照しようとしたので今回の要素の探索を終了します。\n" );
		return;
	}
	// 現在参照しようとしている列の番号が配列の範囲内に収まっているかをチェック
	if (col < 0 || NUM_ARRAY_COL <= col) {
		// 配列外を参照しようとしているのでここで再起処理を終了
		DBG_PRINT("配列外を参照しようとしたので今回の要素の探索を終了します。\n");
		return;
	}

	// 現在参照しようとしている番号の配列の要素がチェック済みかをチェック
	if (checkArray[row][col] == true) {
		// 既にチェック(探索)済みなのでここで再起処理を終了
		DBG_PRINT("参照した要素が探索済みだったため今回の要素の探索を終了します。\n");
		return;
	}

	checkArray[row][col] = true;

	// 指定された番号(idx)の要素に対象の値(target)が保存されているかチェック
	if (numArray[row][col] != target) {
		// 指定された値が存在していないのでここで再帰処理を終了
		DBG_PRINT("参照した要素に指定された値が入っていなかったため今回の要素の探索を終了します。\n");
		return;
	}


	findNum++;

	// 今の要素(指定された番号)の中身を表示
	cout << numArray[row][col] << "," << endl;

	// 前の行(上)を探索するためにrowから1を引いてもう一度_dispContinueNumを呼び出す
	_dispContinueNum(row - 1, col, target, findNum);

	// 前の列(左)を探索するためにcolから1を引いてもう一度_dispContinueNumを呼び出す
	_dispContinueNum(row, col - 1, target, findNum);

	// 次の行(下)を探索するためにrowに1を足してもう一度_dispContinueNumを呼び出す
	_dispContinueNum(row + 1, col, target, findNum);

	// 次の列(右)を探索するためにcolに1を足してもう一度_dispContinueNumを呼び出す
	_dispContinueNum(row, col + 1, target, findNum);

}


int main()
{
	// 範囲for
	for (int(&row)[8] : numArray) {
		for (int& col : row) {
			cout << col << "," << flush;
		}
		cout << endl;
	}
	cout << endl;

	// 配列のstartRow行目のstartCol列目からtargetNumという値が連続している限り表示する再帰処理を呼び出す。
	int startRow = 0;
	int startCol = 0;
	int targetNum = 1;

	cout << dispContinueNum(startRow, startCol, targetNum) << "個連続していました。" << endl;;
	

	

	return 0;
}