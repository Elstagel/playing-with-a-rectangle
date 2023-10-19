#include <iostream>
#include <time.h>
#include<Windows.h>//	Sleep;
#include<conio.h>
using namespace std;
enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получаем дискриптор активного окна

void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };

void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
	SetConsoleCursorPosition(hStdOut, myCoords);
}

class myRectangle
{
	//поля класса
	int height = 2;
	int width = 3;
	Color color = Red;
	char symbol = '+';
	COORD startCoords{ 5,5 };

	//методы:
public:

	//set-методы  блок методов, которые принимают в качестве аругментов значение и устанавливаюют его в качесвте значения поля класса (с предварительной валидацией)
	void setRectColor(Color func_color)
	{
		if (func_color != Black)
		{
			color = func_color;
		}
	}

	void setRectSymbol(char func_char)
	{
		symbol = func_char;
	}

	void setCoords(int X, int Y)
	{
		if (X >= 0 and Y >= 0 and X <= 70 and Y <= 70)
		{
			startCoords.X = X;
			startCoords.Y = Y;
		}
	}
	void setWidth(int Width)
	{
		if (Width > 1 && Width < 50)
		{
			width = Width;
		}
	}
	void setHeight(int Height)
	{
		//перед присвоением значения проверяем его
		if (Height > 1 && Height < 50)
		{
			height = Height;
		}
	}
	//блок методов, которые возвращают значения каждого поля
	int getHeight()
	{
		return height;
	}
	int getWidth()
	{
		return width;
	}
	Color getColor()
	{
		return color;
	}
	char getChar()
	{
		return symbol;
	}

	COORD getCOORD()
	{
		return startCoords;
	}

	int getX()
	{
		return startCoords.X;
	}
	int getY()
	{
		return startCoords.Y;
	}
	int getSquare()
	{
		return height * width;
	}
	void printRectangle()
	{
		setColor(color, Black);
		for (size_t i = 0; i < height; i++)
		{
			setCursor(startCoords.X, startCoords.Y + i);
			for (size_t j = 0; j < width; j++)
			{
				cout << symbol;
			}
		}
		setColor(White, Black);
	}

	//метод для перемещения прямоугольника по нажатию клавиши
	int moveRect(int maxRight, int maxDown)
	{
		int key;

		do {
			printRectangle();
			key = _getch();
			clearRectangle();
			switch (key)
			{
			case Up:
				if (startCoords.Y > 1)
				{
					startCoords.Y--;
				}
				//если столкновение с верхней границей - возвращаем Up
				if (startCoords.Y == 1)
				{
					return Up;
				}
				break;
			case Left:
				if (startCoords.X > 1)
				{
					startCoords.X--;
				}
				if (startCoords.X == 1)
				{
					return Left;
				}
				break;
			case Right:
				if (startCoords.X > 0 && startCoords.X < 15)
				{
					startCoords.X++;
				}
				if (startCoords.X == 15)
				{
					return Right;
				}
				break;
			case Down:
				if (startCoords.Y > 0 && startCoords.Y < 15)
				{
					startCoords.Y++;
				}
				if (startCoords.Y == 15)
				{
					return Down;
				}
				break;
			case Enter:
				return Enter;
				break;
			case esc:
				return esc;
			}
		} while (true);
		return esc;
	}
	//метод для затирания прямоугольника
	void clearRectangle()
	{
		setColor(Black, Black);
		for (size_t i = 0; i < height; i++)
		{
			setCursor(startCoords.X, startCoords.Y + i);
			for (size_t j = 0; j < width; j++)
			{
				cout << symbol;
			}
		}
		setColor(White, Black);
	}
	void PrintMet()
	{
		setColor(color, Black);
		cout << "visota " << height << endl;
		cout << "shirina " << width << endl;
		cout << "ploshad " << getSquare() << endl;
		setColor(White, Black);
	}
};

//функция для заполнения массива объектов
void setFill(myRectangle massiv[], int size)
{
	for (size_t i = 0; i < size; i++)
	{

		massiv[i].setCoords(rand() % 10, rand() % 20);
		massiv[i].setHeight(2 + rand() % 20);
		massiv[i].setWidth(2 + rand() % 15);
		massiv[i].setRectColor(Color(rand() % 15));
	}
}
//функуия для вывода данных по массиву объектов
void Printmas(myRectangle massiv[], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		massiv[i].PrintMet();
		cout << "\n";
	}
}
//функция, возвращающая индекс объекта с самой большой площадью
int Getindex(myRectangle massiv[], int size)
{
	int max = massiv[0].getSquare(), index_pos = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (massiv[i].getSquare() > max)
		{
			max = massiv[i].getSquare();
			index_pos = i;
		}
	}
	return index_pos;
}

class myFrame
{
	int height = 18;
	int width = 19;
	Color colorleft = Red;
	Color colorright = DarkGray;
	Color colorup = Blue;
	Color colordown = Green;

public:
	void SetHeight(int H)
	{
		if (H >= 10 && H <= 40)
		{
			height = H;
		}
	}
	void SetWidth(int W)
	{
		if (W >= 10 && W <= 40)
		{
			width = W;
		}
	}
	void SetColorLeft(Color color)
	{
		colorleft = color;
	}
	void SetColorRigth(Color color)
	{
		colorright = color;
	}
	void SetColorUp(Color color)
	{
		colorup = color;
	}
	void SetColorDown(Color color)
	{
		colordown = color;
	}

	int GetHeight()
	{
		return height;
	}
	int GetWidth()
	{
		return width;
	}
	Color GetColorLeft()
	{
		return colorleft;
	}
	Color GetColorRight()
	{
		return colorright;
	}
	Color GetColorUp()
	{
		return colorup;
	}
	Color GetColorDown()
	{
		return colordown;
	}

	void printFrame()
	{
		int X = 0, Y = 0;
		for (size_t i = 0; i < height; i++)
		{
			setCursor(X, Y + i);
			for (size_t j = 0; j < width; j++)
			{
				if (i == 0)
				{
					setColor(colorup, colorup);
				}
				else if (j == 0)
				{
					setColor(colorleft, colorleft);
				}
				else if (i == height - 1)
				{
					setColor(colordown, colordown);
				}
				else if (j == width - 1)
				{
					setColor(colorright, colorright);
				}
				else {
					setColor(Black, Black);
				}
				cout << " ";
			}
		}
	}

};

void main()
{
	//перемещение прямоугольника вынести как функцию

	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	myFrame frameObj;
	myRectangle rect;
	int code;
	do
	{
		frameObj.printFrame();

		code = rect.moveRect(frameObj.GetWidth(), frameObj.GetHeight());//определяем с какой стороной произошло столкновение
		switch (code)
		{
		case Up:
			//установить для прямоугольника цвет как у верхней границы
			//для этой границы сменить цвет на случайный
			rect.setRectColor(frameObj.GetColorUp());
			frameObj.SetColorUp(Color(1 + rand() % 15));
			break;
		case Left:
			rect.setRectColor(frameObj.GetColorLeft());
			frameObj.SetColorLeft(Color(1 + rand() % 15));
			break;
		case Right:
			rect.setRectColor(frameObj.GetColorRight());
			frameObj.SetColorRigth(Color(1 + rand() % 15));
			break;
		case Down:
			rect.setRectColor(frameObj.GetColorDown());
			frameObj.SetColorDown(Color(1 + rand() % 15));

			break;
		case Enter:
			rect.setRectColor(Color(1 + rand() % 15));
			break;
		}
		//если произошло столкновение - 
	} while (code != esc);



}
