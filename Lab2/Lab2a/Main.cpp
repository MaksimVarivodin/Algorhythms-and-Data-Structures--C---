#include "Stack_reals.h"
int main() {
	/* небольшая работа с консолью */
	BigColor Color;
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title Stack");
	system("mode con cols=78 lines=50");

	string back_txt = "color " + Color.White.symb + Color.Black.symb;
	system(back_txt.c_str());
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);

	Stack<double> a(true);
	system("pause");
	
	vector<string> str{
	   "МЕНЮ",
	   "1 - Свапнуть первый и последний",
	   "2 - Инвертировать",
	   "3 - Удаление четных элементов",
	   "4 - Вставка спецсимвола \"*\"",
	   "5 - Поиск максимального, вставка \"0\"",
	   "6 - Удаление минимального",
	   "7 - Очистить cтек, оставить первый",
	   "8 - Очистить стек, оставить последний",
	   "9 - Выход"
	};

	vector<int> fil(str.size());
	fil[0] = 20;

	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 10;
	}

	MENU m(str, fil, Color.Black, Color.White);

	for (;;) {

		system("cls");
		int b = m.show();
		system("mode con cols=78 lines=200");//задание размеров окна консоли
		if (b == 1) {
			a.Show();
			cout << endl << "Свапнуть первый и последний" << endl;
			a.Swap(a.Bottom(), a.Top());
			a.Show();
		}
		if (b == 2) {
			a.Show();
			Stack <double> buffer(a.Invert());
			cout << endl << "Инвертировать" << endl;
			buffer.Show();
		}
		if (b == 3) {
			a.Show();
			a.DeleteEven();
			cout << endl << "Удаление четных элементов" << endl;
			a.Show();
		}
		if (b == 4) {
			a.Show();
			cout << endl << "Вставка спецсимвола \"*\"" << endl;
			a.Symbol('*');
		}
		if (b == 5) {
			a.Show();
			cout << endl << "Поиск максимального, вставка \"0\"" << endl;
			a.Zero();
		}
		if (b == 6) {
			a.Show();
			cout << endl << "Удаление минимального" << endl;
			a.DeleteMin();
			a.Show();
		}
		if (b == 7) {
			a.Show();
			cout << endl << "Очистить список, оставить первый" << endl;
			a.DeleteFirstLast(true);
			a.Show();
		}
		if (b == 8) {
			a.Show();
			cout << endl << "Очистить список, оставить последний" << endl;
			a.DeleteFirstLast(false);
			a.Show();
		}		
		a.Renumb();
		if (b == 9 || b == 0) {

			if (!a.SavedCheck()) {
				vector<string> str1{
	            "Данные не сохранены, сохранить?",
	            "1 - Да",
	            "2 - Нет"
				};

				vector<int> fil1(str1.size());
				fil1[0] = 20;

				for (int i = 1; i < fil1.size(); i++) {
					fil1[i] = 10;
				}

				MENU men(str1, fil1, Color.Black, Color.White);
				while (true) {
					int mn = men.show();
					if (mn == 1) { a.Save(); break; }
					if (mn == 2 || mn == 0) { break; }
				}
			}
			break;	
		}
		system("pause");
		system("mode con cols=78 lines=50");//задание размеров окна консоли

	}

}
