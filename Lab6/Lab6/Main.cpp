#include "Hash.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<HashLine>table;
	int size = 0;
	vector<int> keys1{ 51, 52, 53, 54, 55 };
	vector<int> keys2{ 21, 31, 24, 10, 40, 41, 9, 2, 20 };
	vector<int> data{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	HashLine::CreateTable(table, keys1);
	vector<ChainLine*> chtable(9, nullptr);
	int counter = 0;
	for (int a : keys2) {
		ChainLine::Add(chtable, a, data[counter]);
		counter++;
	}
	vector<LinOpLine> lotable(11);
	counter = 0;
	for (int a : keys2) {
		LinOpLine::Add(lotable, a, data[counter]);
		counter++;
	}
	vector<KvOpLine> kotable(11);
	counter = 0;
	for (int a : keys2) {
		KvOpLine::Add(kotable, a, data[counter]);
		counter++;
	}
	vector<DvHshLine> dvhstable(11);
	counter = 0;
	for (int a : keys2) {
		DvHshLine::Add(dvhstable, a, data[counter]);
		counter++;
	}
	vector<string> menu{"1 - Вставка", "2 - Удаление", "3 - Печать", "4 - Поиск", "5 - Переход к следующему"};
	int p = 1;
	int k = 0, x = 0;
	cout << "1. Обычная Хеш-таблица" << endl;
	while (p != 5) {
		for (string a : menu)cout << a << endl;
		cout << endl << "Введите пункт:";
		Enter_check(p,5, 1);		
		if (p == 1) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			cout << endl << "Введите значение:";
			Enter_check(x, 100, 0);
			HashLine::Add(table, k, x);
		}
		else if(p == 2) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			HashLine::DeleteLine(table, k);
		}
		else if (p == 3) {
			HashLine::Print(table);
		}
		else if (p == 4) {
			int f = 0;
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			HashLine::Search(table, k, f);
			cout << f << "\t" << table[f].key << "\t" << table[f].data << "\t" << table[f].changed << endl;
		}
	}
	system("cls");
	cout << "2. Хеш-таблица с разрешением колизий методом цепочек" << endl;
	p = 0; 
	while (p != 5) {
		for (string a : menu)cout << a << endl;
		cout << endl << "Введите пункт:";
		Enter_check(p, 5, 1);
		if (p == 1) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			cout << endl << "Введите значение:";
			Enter_check(x, 100, 0);
			ChainLine::Add(chtable, k, x);
		}
		else if (p == 2) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			ChainLine::DeleteElem(chtable, k);
		}
		else if (p == 3) {
			ChainLine::DisplayTable(chtable);
			ChainLine::TraceTable(chtable);
		}
		else if (p == 4) {
			int f = 0;
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			ChainLine::Search(chtable, k, f);
			cout << f << "\t" << table[f].key << "\t" << table[f].data << "\t" << table[f].changed << endl;
		}
	}
	system("cls");
	cout << "3. Хеш-таблица с линейным пробированием" << endl;
	p = 0;
	while (p != 5) {
		for (string a : menu)cout << a << endl;
		cout << endl << "Введите пункт:";
		Enter_check(p, 5, 1);
		if (p == 1) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			cout << endl << "Введите значение:";
			Enter_check(x, 100, 0);
			LinOpLine::Add(lotable, k, x);
		}
		else if (p == 2) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			LinOpLine::DeleteLine(lotable, k);
		}
		else if (p == 3) {
			LinOpLine::Print(lotable);
		}
		else if (p == 4) {
			int f = 0;
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			LinOpLine::Search(lotable, k, f);
			cout << f << "\t" << table[f].key << "\t" << table[f].data << "\t" << table[f].changed << endl;
		}
	}
	system("cls");
	cout << "4. Хеш-таблица с квадратичным пробированием" << endl;
	p = 0;
	while (p != 5) {
		for (string a : menu)cout << a << endl;
		cout << endl << "Введите пункт:";
		Enter_check(p, 5, 1);
		if (p == 1) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			cout << endl << "Введите значение:";
			Enter_check(x, 100, 0);
			KvOpLine::Add(kotable, k, x);
		}
		else if (p == 2) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			KvOpLine::DeleteLine(kotable, k);
		}
		else if (p == 3) {
			KvOpLine::Print(kotable);
		}
		else if (p == 4) {
			int f = 0;
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			KvOpLine::Search(kotable, k, f);
			cout << f << "\t" << kotable[f].key << "\t" << kotable[f].data << "\t" << kotable[f].changed << endl;
		}
	}
	system("cls");
	cout << "5. Хеш-таблица с двойным хешированием" << endl;
	p = 0;
	while (p != 5) {
		for (string a : menu)cout << a << endl;
		cout << endl << "Введите пункт:";
		Enter_check(p, 5, 1);
		if (p == 1) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			cout << endl << "Введите значение:";
			Enter_check(x, 100, 0);
			DvHshLine::Add(dvhstable, k, x);
		}
		else if (p == 2) {
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			DvHshLine::DeleteLine(dvhstable, k);
		}
		else if (p == 3) {
			DvHshLine::Print(dvhstable);
		}
		else if (p == 4) {
			int f = 0;
			cout << endl << "Введите ключ:";
			Enter_check(k, 100, 0);
			DvHshLine::Search(dvhstable, k, f);
			cout << f << "\t" << dvhstable[f].key << "\t" << dvhstable[f].data << "\t" << dvhstable[f].changed << endl;
		}
	}
	ChainLine::DeleteTable(chtable);
}