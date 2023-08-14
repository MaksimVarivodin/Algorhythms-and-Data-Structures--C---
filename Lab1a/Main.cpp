#include "List_reals.h"

int main() {
	BigColor Color;
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title List");//задание описания окна консоли
	system("mode con cols=78 lines=50");//задание размеров окна консоли
	string back_txt = "color " + Color.White.symb + Color.Black.symb;
	system(back_txt.c_str());
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
	CONSOLE_CURSOR_INFO cursor = { 100,false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
	SetConsoleCursorInfo(hCons, &cursor);
	
	vector<string> str{
	   "МЕНЮ",
	   "1 - Cформировать список",
	   "2 - Добавить элементы",
	   "3 - Удалить элементы",
	   "4 - Показать количество элементов",
	   "5 - Поменять два элемента местами",
	   "6 - Создать новый список и объединить его с текущим",
	   "7 - Очистить список",
	   "8 - Информация о разработчике",
	   "9 - Выход"
	},
		str1{
   "Текущие данные не сохранены! Хотите сохранить?",
   "1 - Да",
   "2 - Нет"
	};

	vector<int> fil(str.size()), fil1(str1.size());
	fil[0] = 20;
	fil1[0] = 5;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 10;
	}
	for (int i = 1; i < fil1.size(); i++) {
		fil1[i] = 10;
	}
	MENU m(str, fil, Color.Black, Color.White),
		m1(str1, fil1, Color.Black, Color.White);
	
	List<int>* list = nullptr;
	while (true) {
		system("cls");
		int b = m.show();
		system("mode con cols=78 lines=9999");//задание размеров буфера консоли
		if (b == 1)
		{
			if (list != nullptr) { delete list; }
			list = new List<int>{ true };
		}
		if (b == 8)
		{
			list->Info();
		}
		if (b == 9 || b == 0)
		{
			if (list == nullptr) return 0;
			else if (!list->SavedCheck()) {
				while (true)
				{
					int b2 = m1.show();
					if (b2 == 1) {
						list->Save();
					}
				    break;
				}
			}
				
			break;
		}
		else if (list != nullptr) {
			if (b == 2){
			
				list->FrontAdd();
			}
			else if (b == 3)
			{
				list->FrontDel();
			}
			else if (b == 4)
			{
				list->Show();
			}
			else if (b == 5)
			{
				List <int>* oldList = new List<int>{ *list };
				list->Swap();
				cout << "Изначальный список выглядит так:" << endl;
				oldList->Show(false);
				cout << "Измененный список выглядит так:" << endl;
				list->Show(false);
			}
			else if (b == 6)
			{
				
				List <int>* oldList = new List<int>{ *list };
				List<int>* bufferList = new List<int>{ true };
				cout << "Изначальный список выглядит так:" << endl;
				oldList->Show(false);
				cout << "Буфферный список выглядит так:" << endl;
				bufferList->Show(false);
				*list += *bufferList;
				cout << "Объедененный список выглядит так:" << endl;
				list->Show(false);
			}
			else if (b == 7)
			{
			   list->Clear();
			   cout << "Очистка завершена" << endl;
			   list->Show(false);
			}
			list->Renumb();
		}
		else {
			cout << "Невозможно выполнить операции до создания списка!" << endl;
		}
		system("pause");
		system("mode con cols=78 lines=50");//задание размеров окна консоли
	}

}