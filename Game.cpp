#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

bool GameOver;
const int width = 20;//������ ����
const int height = 20;
int x, y;//���������� ������
int FX, FY;//���������� �������
int score;//���� ����
int tailX[100], tailY[100];//���������� ������
int nTail;//����� ������
enum Move {stop=0,mright,mleft,up,down};//������������ ������ (���� ��� ������, ����� ������ �����) ��������� ��������
Move movesnake;

void Setup()//��������� ����������� ��� ������
{
	GameOver = false;//�� ������� �� ���������
	movesnake = stop;//������ ������ ����� �� �����
	x = width / 2-1;
	y = height / 2-1;//������ ������ � �������� ����
	srand(time(NULL));
	FX = 1+rand() % (width-3);
	FY = 1+rand() % (height-3);//���������� ������ - ��������� ���������� � �������� ����
	score = 0;
}

void Draw()//�������� �����
{
	system("cls");//������� ��������� ��� ������ draw
	for (int i = 0; i < width+1; i++)//
	{
		cout << "#";
	}
	cout<<endl;
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "#";
			}
			if (i == y && j == x)
			{
				cout << "0";
			}
			else if (i == FY && j == FX)
			{
				cout << "+";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)//���� ���������� ������ ������ ��������� � ������������ ����
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width+1; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "SCORE: " << score;
	cout << endl;
}

void Input()//����������� �������
{
	if (_kbhit())//���������� true ���� ������ ������������ ������ �� ������
	{
		switch (_getch())//����������� �������
		{
		case 'a':
			movesnake = mleft;//����� �� � � ��.
			break;
		case 'w':
			movesnake = up;
			break;
		case 'd':
			movesnake = mright;
			break;
		case 's':
			movesnake = down;
			break;
		case'r':
			break;//��� ������� �� r ����� ����
		}
	}
}

void Logic()//������ ����
{
	int prevX = tailX[0];//���������� ������ ������
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;//��������� ����������
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];//���������� ������������ ������
		prev2Y = tailY[i];
		tailX[i] = prevX;//���������� ������������ ������ �������� �� ���������� ����������
		tailY[i] = prevY;
		prevX = prev2X;//��������� ���������� ����� ������������ ������������
		prevY = prev2Y;
	}
	switch (movesnake)//����������� �����������
	{
	case mleft://���� ������������ left ��������� ���������� ������ � �� � ��.
		x--;
		break;
	case mright:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	}

	if (x > width -2|| x < 0||y>height-1||y<1)
	{
		GameOver = true;

		
	}
	for (int j = 0; j < nTail; j++)
	{
		if (tailX[j] == x && tailY[j] == y)//��������� ����� �� ���� �����
		{
			GameOver = true;
		}
	}
	

	if (x == FX && y == FY)
	{
		score += +1;
		FX = 1 + rand() % (width - 3);
		FY = 1 + rand() % (height - 3);
		nTail++;
	}
}

int main()
{
	Setup();
	
	while (GameOver == 0)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}