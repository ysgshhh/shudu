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
#include<sstream>
using namespace std;
int matrix[9][9];
int matrix_2[9][9];
int sign = 0;
int n;
void generate_game(int,int);

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
	for (int i = x_3;i < x_3 + 3;i++)  //checking3*3����
	{
		for (int j = y_3;j < y_3 + 3;j++)
		{
			if (matrix[i][j] == value)	return false;
		}
	}
	return true;
}

void DFS(int n) //��֦��������
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
			if (checking(matrix, i, x, y))
			{
				matrix[x][y] = i;
				DFS(n + 1);
				if (sign ==1) return;
				matrix[x][y] = 0;
			}
		}
	}
}

void uDFS(int n) //��֦��������
{
	if (n >= 81&&sign==0)
	{
		sign = 1;
		return;
	}
	else if (n >= 81 && sign == 1) {
		sign = 2;
		return;
	}
	int x = n / 9;
	int y = n % 9;
	if (matrix_2[x][y] != 0)uDFS(n + 1);
	else
	{
		for (int i = 1;i <= 9;i++)
		{
			if (checking(matrix_2, i, x, y))
			{
				matrix_2[x][y] = i;
				uDFS(n + 1);
				if (sign == 2) return; 
				matrix_2[x][y] = 0;
			}
		}
	}
}

void unique(int problem_matrix[9][9]) {
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 9;j++) {
			matrix_2[i][j] = problem_matrix[i][j];
		}
	}
	uDFS(0);
	if (sign == 1) return;
	else if (sign == 2) {
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				if (matrix_2[i][j] != matrix[i][j]) {
					cout << "dd";
					problem_matrix[i][j] = matrix[i][j];
					unique(problem_matrix);
				}
			}
		}
	}
}

void gen_unique(int n) {
	generate_game(n, 55);
	ifstream in;
	ofstream out;
	in.open("game.txt");
	out.open("unique_game.txt");
	int num;
	in >> num;
	out << num<<endl;
	while (num) {
		int problem_matrix[9][9];
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				in >> problem_matrix[i][j];
			}
		}
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				matrix[i][j] = problem_matrix[i][j];
			}
		}
		DFS(0);
		sign = 0;
		unique(problem_matrix);
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				out<< problem_matrix[i][j]<<" ";
			}
			out << endl;
		}
		out << endl;
		num--;
	}
}

void init(int n) //��֦��������
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

/***************************
*		������������
*		����final.txt
***************************/
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
	cout << "�ɹ�����" << co << "������������" << endl;
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

/***************************
*		����������Ϸ
*		����game.txt
****************************/
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
	
}

void gen_difficulty(int n, int level) {
	int blank;
	random_device rd;
	mt19937  r_eng(rd());
	blank = r_eng();
	blank = abs(blank);
	if (level == 1) {
		blank = blank% 10 + 20;
		generate_game(n, blank);
	}
	else if (level == 2) {
		blank = blank % 10 + 30;
		generate_game(n, blank);
	}
	else if (level == 3) {
		blank = blank % 15 + 45;
		generate_game(n, blank);
	}
}

void Solute(string file) {
	ifstream in;
	in.open(file);
	ofstream out;
	out.open("sudoku2.txt");
	int num;
	in >> num;
	int co = num;
	out << num<<endl;
	int cur;
	while (num) {

		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				in >> cur;
				matrix[i][j] = cur;
				//cout << num<<" ";
			}
		}
		sign = 0;
		uDFS(0);
		
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 9;j++) {
				out << matrix[i][j] << " ";
			}
			out << endl;
		}
		out << endl;
		num--;
	}
}


int main()
{
	cout << "ָ����ܣ�"<<endl;
	cout << "-c\t������������" << endl << "-s\t�������" << endl << "-n\t����������Ϸ"<<endl;
	cout << "-m\t������Ϸ���Ѷ�" << endl << "-r\t������Ϸ���ڿ�����" << endl << "-u\t����Ψһ�����Ϸ"<<endl;
	cout << "������ָ��:" << endl;
	/***************************
	*		ָ������
	*		��ָ�����
	***************************/
	string a;
	string instr[5];
	int pos;
	getline(cin, a);
	int num = 0;
	while (a.find(" ") < 20) {
		pos = a.find(" ");
		instr[num] = a.substr(0, pos);
		a = a.substr(pos + 1, size(a));
		num++;
	}
	instr[num] = a;
	int operand1;
	int operand2;
	string file;
	stringstream ss,ss2;
	ss << instr[2];
	ss >> operand1;
	ss2 << instr[4];
	ss2 >> operand2;
	enum{Final,Solution,Gen_num,Gen_difficulty,Gen_blank,Gen_unique};
	int op=-1;
	if (instr[1] == "-c") op = 0;
	else if (instr[1] == "-s") { op = 1;file = instr[2]; }
	else if (instr[1] == "-n" && instr[3] == "")op = 2;
	else if (instr[1] == "-n" && instr[3] == "-m")op = 3;
	else if (instr[1] == "-n" && instr[3] == "-r")op = 4;
	else if (instr[1] == "-n" && instr[3] == "-u")op = 5;
	switch (op) {
	case Final:
		generate_final(operand1);
		break;
	case Solution:
		Solute(file);
		break;
	case Gen_num:
		generate_game(operand1);
		cout << "������" << operand1 << "��������Ϸ,�ڿ���Ϊ" << 20 << endl;
		break;
	case Gen_difficulty:
		gen_difficulty(operand1, operand2);
		cout << "������" << operand1 << "��������Ϸ,�Ѷ�Ϊ" << operand2 << endl;
		break;
	case Gen_blank:
		generate_game(operand1, operand2);
		cout << "������" << operand1 << "��������Ϸ,�ڿ���Ϊ" << operand2 << endl;
		break;
	case Gen_unique:
		gen_unique(operand1);
		cout << "������" << operand1 << "������Ψһ���������Ϸ"<< endl;
		break;
	default:
		cout << "��������ȷ��ָ�";
		exit(0);
	}
}
