#include <iostream>

using namespace std;

const int queenNums = 8;						//皇后数量
int chessBoard[queenNums][queenNums] = { 0 };	//棋盘大小
int solveNum = 0;

bool check(int row, int col)
{
	if (row == 0)
		return true;

	for (int i = 0; i != row; i++)		//检查列内是否有其它皇后
	{
		if (chessBoard[i][col] == 1)
			return false;
	}

	for (int j = 0; j != col; j++)		//检查行内是否有其它皇后
	{
		if (chessBoard[row][j] == 1)
			return false;
	}

	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)	//检查左对角线上是否有其它皇后
	{
		if (chessBoard[i][j] == 1)
			return false;
	}

	for (int i = row - 1, j = col + 1; i >= 0 && j != queenNums; i--, j++)	//检查左对角线上是否有其它皇后
	{
		if (chessBoard[i][j] == 1)
			return false;
	}

	return true;
}

void show()		//用于打印结果
{
	int row, col;
	solveNum++;
	cout << "解法" << solveNum << "：" << endl;
	for (row = 0; row != queenNums; row++)
	{
		for (col = 0; col != queenNums; col++)
		{
			cout << chessBoard[row][col] << " ";
		}
		cout << endl;
	}
}

void solve(int row)
{
	int col;
	for (col = 0; col != queenNums; col++)
	{
		chessBoard[row][col] = 1;		//在当前行的其中一个位置放一个皇后
		if (check(row, col) == true)
		{
			if (row == queenNums - 1)	//如果这一轮检查到最后一行都合法，说明找到了一种解法，直接打印
				show();
			else
			{
				solve(row + 1);				//不是最后一行就接着看下一行皇后要放在哪
			}
		}
		chessBoard[row][col] = 0;		//如果所有的都不能放，把上一次的皇后撤走，换一个位置
	}
}

int main()
{
	solve(0);
	cout << "一共" << solveNum << "种解法" << endl;
	return 0;
}

