#include<iostream>
#include<map>
#include<vector>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>

using namespace std;
int matrix[9][9];
bool sign = 0;
int n;

bool checking(int value, int x, int y)
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
	for (int i = x_3;i < x_3 + 3;i++)  //checking3*3¹¬ÄÚ
	{
		for (int j = y_3;j < y_3 + 3;j++)
		{
			if (matrix[i][j] == value)	return false;
		}
	}
	return true;
}

void DFS(int n) //¼ôÖ¦¡ª¡ª»ØËÝ
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
			if (checking(i, x, y))
			{
				matrix[x][y] = i;
				DFS(n + 1);
				if (sign == 1)	return;
				matrix[x][y] = 0;
			}
		}

	}

}




int main()
{
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			cin >> matrix[i][j];
		}
	}

	DFS(0);


	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			if (j != 8)	cout << matrix[i][j] << ' ';
			else   cout << matrix[i][j];
		}
		cout << endl;
	}



}
