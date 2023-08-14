#include "Deque_reals.h"
int main() {
	/* небольшая работа с консолью */
	BigColor Color;
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title Дек");
	system("mode con cols=78 lines=50");

	string back_txt = "color " + Color.White.symb + Color.Black.symb;
	system(back_txt.c_str());
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);

	Deque<double>* a = nullptr;

	vector<string> str{
	   "МЕНЮ ",
	   "1 - Создать дек",
	   "2 - Проверка на пустоту",
	   "3 - Добавить элемент в начало",
	   "4 - Добавить элемент в конец",
	   "5 - Показать 6-й элемент",
	   "6 - Показать последний элемент",
	   "7 - Выйти"
	};

	vector<int> fil(str.size());
	fil[0] = 25;

	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m(str, fil, Color.Black, Color.White);

	for (;;) {

		system("cls");
		int b = m.show();
		system("mode con cols=78 lines=9999");//задание размеров окна консоли

		if (b == 7 || b == 0) {

			if (a!= nullptr && !a->SavedCheck()) {
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
					if (mn == 1) { a->Save(); break; }
					if (mn == 2 || mn == 0) { break; }
				}
			}
			break;
		}

		if (b == 1) {
			if (a != nullptr) delete a;
			a = new Deque<double>{ true };
			cout << "Дек создан." << endl;
			a->Show();
		}

		if (a != nullptr) {
			if (b == 2) {
				a->Show();
				cout << endl << "Проверка на пустоту" << endl;
				if (a->Empty())cout << "Дек пуст." << endl;
				else cout << "Дек заполнен." << endl;
			}
			if (b == 3) {
				a->Show();
				cout << endl << "Добавить элемент в начало" << endl;
				a->AddFront();
				a->Show();
			}
			if (b == 4) {
				a->Show();
				cout << endl << "Добавить элемент в конец" << endl;
				a->AddBack();
				a->Show();
			}
			if (b == 5) {
				a->Show();
				cout << endl << "Показать 6-й элемент" << endl;
				a->ShowElem(6);
			}
			if (b == 6) {
				a->Show();
				cout << endl << "Показать последний элемент" << endl;
				a->ShowLast();
			}
			a->Renumb();
		}
		else {
			system("cls");
			cout << endl << "Операция невозможна так как Дек не заполнен." << endl;
		}
		
		
		system("pause");
		system("mode con cols=78 lines=50");//задание размеров окна консоли

	}
}