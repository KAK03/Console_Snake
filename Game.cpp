#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

bool GameOver;
const int width = 20;//размер поля
const int height = 20;
int x, y;//координаты змейки
int FX, FY;//координаты фруктов
int score;//счет игры
int tailX[100], tailY[100];//координаты хвоста
int nTail;//длина хвоста
enum Move {stop=0,mright,mleft,up,down};//перечисление команд (стоп это начало, когда змейка стоит) остальные движения
Move movesnake;

void Setup()//настройка парамметров при старте
{
	GameOver = false;//мы сначала не проиграли
	movesnake = stop;//снчала змейка стоит на месте
	x = width / 2-1;
	y = height / 2-1;//змейка начнет в середине поля
	srand(time(NULL));
	FX = 1+rand() % (width-3);
	FY = 1+rand() % (height-3);//координаты фрукта - случайные координаты в пределах поля
	score = 0;
}

void Draw()//отрсовка карты
{
	system("cls");//очистка терминала при вызове draw
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
					if (tailX[k] == j && tailY[k] == i)//если координаты начала хвоста совпадают с координатами змеи
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

void Input()//отслеживает нажатия
{
	if (_kbhit())//возвращает true если нажата определенная кнопка на клавае
	{
		switch (_getch())//отслеживает клавишу
		{
		case 'a':
			movesnake = mleft;//влево на а и тд.
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
			break;//при нажатии на r конец игры
		}
	}
}

void Logic()//логика игры
{
	int prevX = tailX[0];//координаты начала хвоста
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;//начальные координаты
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];//координаты появившегося хвоста
		prev2Y = tailY[i];
		tailX[i] = prevX;//координаты появившегося хвоста меняются на координаты начального
		tailY[i] = prevY;
		prevX = prev2X;//начальные координаты стали координатами появившегося
		prevY = prev2Y;
	}
	switch (movesnake)//отслеживаем перемещение
	{
	case mleft://если задействован left уменьшаем координату змейки и тд и тп.
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
		if (tailX[j] == x && tailY[j] == y)//проверяем съели ли свой хвост
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