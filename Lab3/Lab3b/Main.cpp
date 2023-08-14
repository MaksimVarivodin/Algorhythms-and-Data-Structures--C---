#include "RBTree_class.h"
int main() {

	/* небольшая работа с консолью */
	BigColor Color;
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title BinaryTree");
	system("mode con cols=78 lines=50");

	string back_txt = "color " + Color.White.symb + Color.Black.symb;
	system(back_txt.c_str());
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);
	RBTree a{};
	vector<string> str{
	   "МЕНЮ",
	   "1 - Считать данные",
	   "2 - Ввести один элемент",
	   "3 - Распечатать среднее",
	   "4 - Порядок",
	   "5 - Очистка",
	   "6 - Удаление",
	   "7 - Изменить ключевое поле",
	   "8 - Сохранить в виде таблицы",
	   "9 - Сохранить в виде дерева",
	   "10 - Выход"
	};

	vector<int> fil(str.size());
	fil[0] = 20;

	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 10;
	}

	MENU m(str, fil, Color.Black, Color.White);

	while (true) {

		system("cls");
		int b = m.show();
		system("mode con cols=78 lines=200");//задание размеров окна консоли
		if (b == 1) {  a.Open(); cout << "1 - Считать данные" << endl; }
		else if (b == 2) { a.TypeIn(); cout << "2 - Ввести элемент" << endl; }
		else if (b == 3) { a.Show(); cout << "3 - Распечатать среднее" << endl;  }
		else if (b == 4) { a.Order(); cout << "4 - Порядок" << endl;  }
		else if (b == 5) { a.Clear(); cout << "5 - Очистка" << endl;  }
		else if (b == 6) { a.Delete(); cout << "6 - Удаление" << endl; }
		else if (b == 7) { a.KeyVarChange().Show(); cout << "7 - Изменить ключевое поле" << endl; }
		else if (b == 8) { a.Save(); cout << "8 - Сохранить в виде таблицы" << endl;  }
		else if (b == 9) { a.SaveTree(); cout << "9 - Сохранить в виде дерева" << endl; }
		else if (b == 10 || b == 0) { cout << "10 - Выход" << endl;break; }
		  		
        system("pause");
        system("mode con cols=78 lines=50");//задание размеров окна консоли

	}

}