#include <iostream>
#include<windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

int width, height, walls, speed, score = 0, length = 1, X_apple, Y_apple;
char snake = 111, apple = 4, head = 2;
const int max_length = 400; // установка максимальной длины "змейки"
int array_X[max_length], array_Y[max_length];
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // создание хендла потока вывода
COORD c; // объект для хранения координат
CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; // создание параметров на отображение курсора

void Menu() {
	setlocale(LC_ALL, "Russian");
	int map_size, wall, speeed;
	bool flag = true;
	cout << "\t\t\t\t\t\tSNAKE\n";
	cout << "\t\t\t\t\t    ПРАВИЛА ИГРЫ\n";
	cout << "На поле появляются 'яблоки'(зелёные ромбики), каждое съеденое яблоко увеличивает длину змейки\n";
	cout << "Цель игры: достичь наибольшей длины змейки\n";
	cout << "Управление: клавиши вверх, вниз, влево и вправо(стрелочеки) или клавиши 'w', 'a', 's', 'd'\n";
	cout << "Игра заканчивается если змейка врезается сама в себя или в стену(в зависимости от режима)\n";
	cout << "Далее вам предстоит выбрать размер поля, режим и скорость змейки\n\n\n";
	cout << "Выберите размер поля: 1 - Маленькое(12x12); 2 - Среднее(18x18); 3 - Большое(24x24)   (Введите нужное число) " << endl;
	while (flag) {
		if (_kbhit()) {
			map_size = _getch();
			switch (map_size) { //выбор размера поля
			case '1':
				cout << 1 << endl;
				width = 27;
				height = 14;
				flag = false;
				break;
			case '2':
				cout << 2 << endl;
				width = 39;
				height = 20;
				flag = false;
				break;
			case '3':
				cout << 3 << endl;
				width = 51;
				height = 26;
				flag = false;
				break;
			}
		}
	}
	flag = true;
	cout << "Выберите режим: 1 - со стенами, 2 - с прохождением через стены" << endl;
	while (flag) {
		if (_kbhit()) {
			wall = _getch();
			switch (wall) { //выбор режима игры
			case '1':
				cout << 1 << endl;
				walls = 1;
				flag = false;
				break;
			case '2':
				cout << 2 << endl;
				walls = 0;
				flag = false;
				break;
			}
		}
	}
	flag = true;
	cout << "Выберите скорость змейки: 1 - медленно, 2 - нормально , 3 - быстро" << endl;
	while (flag) {
		if (_kbhit()) {
			speeed = _getch();
			switch (speeed) { //выбор скорости змейки
			case '3':
				cout << 3 << endl;
				speed = 100;
				flag = false;
				break;
			case '2':
				cout << 2 << endl;
				speed = 160;
				flag = false;
				break;
			case '1':
				cout << 1 << endl;
				speed = 200;
				flag = false;
				break;
			}
		}
	}
	setlocale(0, "C");
	system("cls");

}
void Map() {// отрисовка поля игры
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char s;
			if (x == 0 && y == 0)
			{
				SetConsoleTextAttribute(h, 4);
				s = 218;
			}
			else if (x == 0 && y == height - 1)
			{
				SetConsoleTextAttribute(h, 4);
				s = 192;
			}
			else if (y == 0 && x == width - 1)
			{
				SetConsoleTextAttribute(h, 4);
				s = 191;
			}
			else if (y == height - 1 && x == width - 1)
			{
				SetConsoleTextAttribute(h, 4);
				s = 217;
			}
			else if (y == 0 || y == height - 1)
			{
				SetConsoleTextAttribute(h, 4);
				s = 196;
			}
			else if (x == 0 || x == width - 1)
			{
				SetConsoleTextAttribute(h, 4);
				s = 179;
			}

			else if (x % 2 == 0) {
				SetConsoleTextAttribute(h, 8);
				s = 250;
			}
			else s = ' ';

			putchar(s); 
		}
		cout << endl;

	}
	SetConsoleTextAttribute(h, 7);
	cout << endl << "Score: 0";
	SetConsoleTextAttribute(h, 8);
	cout << endl << "to exit the game, press esc";
}
void Console() {
	system("mode con cols=51 lines=31"); // установка размеров окна консоли
	MoveWindow(GetConsoleWindow(), 1, 1, 100, 100, true); 
}
void Start_position() {// Стартовая позиция змейки и генерация первого "яблока"
	array_X[0] = width / 2 - 1;
	array_Y[0] = height / 2;
	do 
	{
		X_apple = rand() % (width - 3) + 1;
		if (X_apple % 2 == 1)
			X_apple += 1;
		Y_apple = rand() % (height - 2) + 1;
	} while (X_apple != array_X[length - 1] && Y_apple != array_Y[length - 1]);
	c.X = X_apple; 
	c.Y = Y_apple;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 2);
	putchar(apple);
	c.X = array_X[0]; 
	c.Y = array_Y[0];
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 3);
	putchar(head);
}
void Apple() {// Рандомная генерация "яблока"
	int i; 
	do
	{
		X_apple = rand() % (width - 3) + 1; 
		if (X_apple % 2 == 1)
			X_apple += 1;
		Y_apple = rand() % (height - 2) + 1;
		i = 0; 
		for (; i < length; i++) 
			if (X_apple == array_X[i] && Y_apple == array_Y[i]) 
				break; 
	} while (i < length); 
	c.X = X_apple; 
	c.Y = Y_apple;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 2);
	putchar(apple);
}
void Snake() {//цикл игры

	bool flag = true; // переменная для управления ходом цикла
	int dx = 0, dy = 0; 
	do
	{
		Sleep(speed); 

		if (_kbhit()) // проверяем, была ли нажата какая-либо клавиша 
		{
			int k = _getch(); 
			if (k == 0 || k == 224) 
				k = _getch();
			switch (k) 
			{
			case 80: case 's':case 'S': case 235: case 155:
				dy = 1;
				dx = 0;
				break;
			case 72: case 'w':case 'W': case 230: case 150:
				dy = -1;
				dx = 0;
				break;
			case 75:case 'a':case 'A':  case 228: case 148:
				dy = 0;
				dx = -2;
				break;
			case 77:case 'd':case 'D': case 162: case 130:
				dy = 0;
				dx = 2;
				break;
			case 27: // Esc
				flag = false; 
				break;
			}
		}

		int X = array_X[length - 1] + dx; 
		int Y = array_Y[length - 1] + dy; 
		if (walls == 1) {//режим со стенами, если змейка достигла стены, то игра заканчивается
			if (X <= 0 || X >= width - 1 || Y <= 0 || Y >= height - 1) {
				flag = false;
			}
		}
		else {//режим с прохождением через стены, если змейка достигла стены, то она перемещается на противоположную сторону
			if (X <= 0) {
				X = width - 3;
			}
			if (X >= width - 1) {
				X = 2;
			}
			if (Y >= height - 1) {
				Y = 1;
			}
			if (Y <= 0) {
				Y = height - 2;
			}
		}

		if (X == X_apple && Y == Y_apple) // проверка на достижение "яблока"
		{
			c.X = array_X[length - 1]; 
			c.Y = array_Y[length - 1];
			SetConsoleCursorPosition(h, c); 
			putchar(snake); 

			length++; 
			c.X = array_X[length - 1] = X; 
			c.Y = array_Y[length - 1] = Y;
			SetConsoleCursorPosition(h, c); 
			putchar(head); 

			if (length == max_length) 
			{
				break; 
			}
			Apple();

			SetConsoleTextAttribute(h, 7);
			score += 1;// Изменение результата
			c.X = 7;
			c.Y = height + 1;
			SetConsoleCursorPosition(h, c);
			cout << score;
			SetConsoleTextAttribute(h, 3);
		}
		else // случай, когда голова "змейки" оказалась на новой пустой позиции
		{
			int i = 1; 
			for (; i < length; i++)
				if (X == array_X[i] && Y == array_Y[i]) 
					break;
			if (i < length) 
			{
				break;
			}
			else // а иначе запускаем обработку сдвига "змейки"
			{
				c.X = array_X[0]; 
				c.Y = array_Y[0];
				SetConsoleCursorPosition(h, c); 
				SetConsoleTextAttribute(h, 8);
				putchar(250); 
				SetConsoleTextAttribute(h, 3);
				if (length > 1) 
				{
					c.X = array_X[length - 1]; 
					c.Y = array_Y[length - 1];
					SetConsoleCursorPosition(h, c);  
					putchar(snake); 
				}

				for (int i = 0; i < length - 1; i++) 
				{
					array_X[i] = array_X[i + 1]; 
					array_Y[i] = array_Y[i + 1];
				}

				c.X = array_X[length - 1] = X; 
				c.Y = array_Y[length - 1] = Y;
				SetConsoleCursorPosition(h, c); 
				putchar(head); 
			}
		}
	} while (flag); // выходим из цикла, если сброшена управляющая переменная
	system("cls"); 
	SetConsoleTextAttribute(h, 4);
	cout << "\n\n\n\n\t\tGAME OVER\n\n"; 
	cout << "\t\tScore: " << score << "\n\n\n";
	system("pause");
}
int main()
{
	srand(time(0)); // запуск генератора случайных чисел
	Menu();
	SetConsoleCursorInfo(h, &cci); //связывание параметров и хендла
	Console();
	Map();
	Start_position();
	Snake();
}