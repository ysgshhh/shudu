#include<iostream>
#include<map>
#include<vector>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<fstream>
#include<ctime>
#include<random>
#include<cstring>
#include<string>
using namespace std;
int matrix[9][9];
bool sign = 0;
int n;


bool checking(int matrix[9][9],int value, int x, int y)
{
	for (int i = 0;i < 9;i++)
	{
		if (matrix[x][i] == value)	return false;
	}
	for (int i = 0;i < 9;i++)
	{
		if (matrix[i][y] == value)	return false;
	}
	int x_3 = (x / 3) * 3;
	int y_3 = (y / 3) * 3;
	for (int i = x_3;i < x_3 + 3;i++)  //checking3*3宫内
	{
		for (int j = y_3;j < y_3 + 3;j++)
		{
			if (matrix[i][j] == value)	return false;
		}
	}
	return true;
}

void DFS(int n) //剪枝——回溯
{
	if (n >= 81)
	{
		sign = 1;
		return;
	}
	int x = n / 9;
	int y = n % 9;
	if (matrix[x][y] != 0)	DFS(n + 1);
	else
	{
		for (int i = 1;i <= 9;i++)
		{
			if (checking(matrix,i, x, y))
			{
				matrix[x][y] = i;
				DFS(n + 1);
				if (sign == 1)	return;
				matrix[x][y] = 0;
			}
		}

	}
}

void init(int n) //剪枝——回溯
{
	srand(time(0));
	if (n >= 81)
	{
		sign = 1;
		return;
	}
	int x = n / 9;
	int y = n % 9;
	random_device rd;
	mt19937  r_eng(rd());
	int ran = r_eng();
	for (int i = abs(ran);i <= 8+abs(ran);i++)
	{
		int j = i % 9+1;
		if (checking(matrix, j, x, y))
		{
			matrix[x][y] = j;
			init(n + 1);
			if (sign == 1)	return;
			matrix[x][y] = 0;
		}
	}

}
void generate_final(int num) {
	int co = num;
	ofstream out;
	out.open("final.txt");
	out << num << endl;
	while (num) {
		memset(matrix, 0, sizeof(matrix));
		sign = 0;
		init(0);
		for (int i = 0;i < 9;i++)
		{
			for (int j = 0;j < 9;j++) {
				out << matrix[i][j] << " ";
			}
			out << endl;
		}
		out << endl;
		num--;
	}
	cout << "成功生成" << co << "个终盘数独！" << endl;
}

void selectBlank(int nums, int matrix[9][9])
{
	random_device rd;
	mt19937  r_eng(rd());
	int ran = r_eng();
	while (nums)
	{
		int row = r_eng() % 9;
		row = abs(row);
		int col = r_eng() % 9;
		col = abs(col);
		if (matrix[row][col] != 0)
		{
			matrix[row][col] = 0;
			nums--;
		}
	}
}

void generate_game(int n,int blank=20) {
	ifstream in;
	in.open("final.txt");
	ofstream out;
	out.open("game.txt");
	out << n<<endl;
	int num;
	in >> num;
	int co = num;
	int matrix[9][9];
	int log = n;
	while (n > 0) {
		if (num==0) {
			in.seekg(0, in.beg);
			in >> co;
			num = co;
		}
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				in >> matrix[i][j];
			}
		}
		
		selectBlank(blank, matrix);
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				out<<matrix[i][j]<<" ";
			}
			out << endl;
		}
		out << endl;
		n--;
		num--;
	}
	cout << "生成了" << log << "个数独游戏,挖空数为" << blank<<endl;
}


int main()
{
/***************************
*		生成终盘数独
*		存入final.txt
***************************/
	generate_final(11);
	string instr;
	//getline(cin, instr);
	


/***************************
*		产生数独游戏
*		存入game.txt
****************************/
	generate_game(300);
}
