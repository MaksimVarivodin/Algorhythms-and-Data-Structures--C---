#pragma once
#include "Deque_class.h"

template<class T>
inline Elem<T>* Deque<T>::Find(const int & val)
{
	Elem <T>* buffer = Front();
	while (buffer->Index() != val && buffer != nullptr)
		buffer = buffer->Next();
	if (buffer == nullptr)return nullptr;
	return buffer;
}

template<class T>
inline void Deque<T>::Fff(Elem<T>* elmnt)
{
	ifstream CIN;
	ofstream COUT;
	string path1 = "numbs.txt";
	COUT.open(path1, ios::app);
	COUT.close();
	CIN.open(path1, ios::app | ios::in);
	if (!CIN.is_open()) { cout << "Error!"; }
	else {
		vector<T> a(0);
		while (!CIN.eof()) {
			string s;
			getline(CIN, s);
			vector<string> buf(0);
			int iter = 0, i = 0;
			while (iter != s.length())
			{
				if (s[iter] == ' ') { iter++; i++; }
				else if (s[iter] != ' ') {
					if (iter > 0) {
						if (s[iter - 1] == ' ' || buf.size() == 0)
							buf.resize(buf.size() + 1);
					}
					else
						buf.resize(buf.size() + 1);


					buf[i] += s[iter];
					iter++;
				}
			}
			a.resize(a.size() + buf.size());
			int k = a.size() - buf.size(), j = 0;
			for (; j < buf.size(); ) {
				try
				{
					// если дробное
					a[k] = stod(buf[j]);
				}
				catch (const std::exception&)
				{
					// в других случаях
					a[k] = stoll(buf[j]);
				}
				k++; j++;
			}
		}
		try
		{
			string err = "Заполните файл числами!";
			if (a.size() <= 0)throw err;
			int b = rand() % a.size();
			elmnt->Info(a[b]);
		}
		catch (const string& err)
		{
			cout << err << endl;
		}

	}
	CIN.close();
}

template<class T>
inline void Deque<T>::Clear()
{
	while (size > 0)
		PopBack();
}

template<class T>
inline void Deque<T>::Show()
{
	if (Empty()) {
		cout << "Пустой Дек." << endl;
		return;
	}
	Elem<T>* buffer = Front();
	cout << "Дек: " << endl;
	buffer->Shapka(cout);
	while (buffer != nullptr) {
		*(buffer) << cout;
		buffer = buffer->Next();
	}
	cout << endl;
}

template<class T>
inline Elem<T>* Deque<T>::PopFront()
{
	if (Empty())return nullptr;
	size--;
	if (Front()->Next() != nullptr)
		Front()->Next()->Prev(nullptr);
	else Back(nullptr);
	Elem <T>* buffer = Front();
	Front(buffer->Next());
	delete buffer;
	return Front();
}

template<class T>
inline Elem<T>* Deque<T>::PushFront()
{
	size++;
	Elem<T>* buffer = new Elem<T>;
	if (Front() != nullptr) {
		Front()->Prev(buffer);
		buffer->Next(Front());
	}
	else Back(buffer);
	Front(buffer);
	Front()->Index(size);
	return Front();
}

template<class T>
inline Elem<T>* Deque<T>::PopBack()
{
	if (Empty())return nullptr;
	size--;
	Elem<T>* buffer = Back();
	if (Back()->Prev() != nullptr) {
		Back()->Prev()->Next(nullptr);
	}
	else Front(nullptr);
	Back(buffer->Prev());
	delete buffer;
	return Back();
}

template<class T>
inline Elem<T>* Deque<T>::PushBack()
{
	size++;
	Elem<T>* buffer = new Elem<T>;
	if (Back() != nullptr) {
		Back()->Next(buffer);
		buffer->Prev(Back());
	}
	else Front(buffer);
	Back(buffer);
	Back()->Index(size);
	return Back();
}

template<class T>
inline void Deque<T>::Renumb()
{
	Elem<T>* buffer = Front();
	for (int i = 1; i <= size; i++) {
		buffer->Index(i);
		buffer = buffer->Next();
	}
}

template<class T>
inline void Deque<T>::AddFront()
{
	Fff(PushFront());
}

template<class T>
inline void Deque<T>::AddBack()
{
	Fff(PushBack());
}

template<class T>
inline void Deque<T>::ShowElem(const int& num)
{
	if (Empty()) {
		cout << "Дек пуст. Поиск невозможен." << endl;
		return;
	}

	if (num > Size()) {
	cout << "Элемент невозможно найти, дек слишком мал." << endl; 
	return;
	}
	Elem <T>* buffer = Front();

	while (num != buffer->Index()) {
		buffer = buffer->Next();
	}
	*buffer << cout<< endl;
}

template<class T>
inline void Deque<T>::ShowLast()
{
	if (Empty()) {
		cout << "Дек пуст. Поиск невозможен." << endl;
		return;
	}
	*Back() << cout << endl;
}

template<class T>
inline void Deque<T>::Save()
{
	if (Empty()) {
		cout << "Очередь пуста." << endl;
		return;
	}

	vector<string>
		str1
	{
	"Выберите путь:",
	"1 - По умолчанию",
	"2 - Текущий",
	"3 - Ввести вручную"
	};

	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	while (true) {
		int m = m1.show();
		if (m == 1) { SetPath("data.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { SetPath(); break; }
		else if (m == 0) { return; }
	}
	try
	{
		ofstream out;
		out.open(Fpath);
		Elem<T>* buf = Front();
		buf->Shapka(out);
		while (buf != nullptr) {
			*buf << out;
			buf = buf->Next();
		}
		out.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка сохранения таблицы!" << endl;
		return;
	}
	cout << "Данные сохранены в: " << Fpath << endl;
}

template<class T>
inline void Deque<T>::Open()
{
	vector<string>
		str1
	{
	"Выберите путь:",
	"1 - По умолчанию",
	"2 - Текущий",
	"3 - Ввести вручную"
	};

	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++)
		fil[i] = 15;
	MENU m1(str1, fil);
	while (true) {
		int m = m1.show();
		if (m == 1) { SetPath("data.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { SetPath(); break; }
		else if (m == 0) { return; }
	}

	try
	{
		ifstream in;
		Clear();
		in.open(Fpath);
		if (!in.is_open())throw exception{};
		for (int i = 0; i < 3; i++) {
			string buf0;
			getline(in, buf0);
		}
		while (!(in.eof())) {
			*(PushBack()) >> (in);
		}
		in.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка oткрытия таблицы!" << endl;
		Save();
		return;
	}
	cout << "Данные были считаны из файла: " << Fpath << endl;

}

template<class T>
inline bool Deque<T>::SavedCheck()
{
	if (Empty()) {
		cout << "Очередь пуста." << endl;
		return true;
	}
	try
	{
		ifstream in;
		in.open(Fpath);
		if (!in.is_open())throw exception{};
		for (int i = 0; i < 3; i++) {
			string buf0;
			getline(in, buf0);
		}
		Deque<T> New{ false };
		while (!(in.eof())) {
			if (New.Size() > Size()) return false;
			*New.PushBack() >> in;
			if (New.Back()->Info() != Find(New.Back()->Index())->Info()) return false;
		}
		in.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка oткрытия таблицы!\nНевозможно сравнить содержимое!" << endl;
		return false;
	}
	return true;
}

