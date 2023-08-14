#pragma once
#include "Queue_class.h"

template<class T>
inline Elem <T>* Queue<T>::Enque()
{
	size++;
	Elem <T>* buffer = new Elem<T>;
	if (beginning == nullptr)Beginning(buffer);
	if (end!= nullptr) {
		End()->Next(buffer);
		buffer->Prev(End());
	}
	End(buffer);
	End()->Index(size);
	return End();
}

template<class T>
inline void Queue<T>::Ffe(Elem<T>* elmnt)
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
inline void Queue<T>::Deque()
{
	size--;
	Elem <T>* buffer = Beginning()->Next();
	if(buffer!= nullptr)
		buffer->Prev(nullptr);
	else End(nullptr);
	delete beginning;
	Beginning(buffer);
}

template<class T>
inline void Queue<T>::Create(const int& size0)
{
	for (int i = 0; i < size0; i++)
		Ffe(Enque());
}

template<class T>
inline Elem<T>* Queue<T>::MaxMin(const bool& max)
{
	if (Empty()) {
		cout << "Очередь пуста, поиск невозможен." << endl;
		return nullptr;
	}
	Elem<T>* buffer = Beginning(), * to_ret = buffer;
	while (buffer != nullptr) {
		to_ret = max ? (to_ret->Info() < buffer->Info() ? buffer : to_ret) : (to_ret->Info() > buffer->Info() ? buffer : to_ret);
		buffer = buffer->Next();
	}
	return to_ret;
}

template<class T>
inline void Queue<T>::Clear()
{
	while (size > 0)
		Deque();
}

template<class T>
inline Elem<T>* Queue<T>::Find(const int & val)
{
	Elem <T>* buffer = Beginning();
	while (buffer->Index() != val && buffer != nullptr)
		buffer = buffer->Next();
	if (buffer == nullptr)return nullptr;
	return buffer;
}

template<class T>
inline void Queue<T>::Show()
{
	if (Empty()) {
		cout << "Пустая очередь." << endl;
		return;
	}
	Elem<T>* buffer = Beginning();
	cout << "Очередь за сахаром и количество долларов у покупателя" << endl;
	buffer->Shapka(cout);
	while (buffer != nullptr) {
		*(buffer) << cout;
		buffer = buffer->Next();
	}
	cout << endl;
}

template<class T>
inline T Queue<T>::Average()
{
	if (Empty())return 0;
	Elem<T>* buffer = Beginning();

	T average = 0;

	while (buffer != nullptr) {

		average += buffer->Info();

		buffer = buffer->Next();

	}

	average /= (1.0 * size);

	return average;

}

template<class T>
inline void Queue<T>::PrintMinMax()
{
	if (Empty())return;
	*(MaxMin(false)) << cout;
	*(MaxMin(true)) << cout;
}

template<class T>
inline void Queue<T>::PrintMinPrev()
{
	Elem<T>* buffer = MaxMin(false)->Prev();
	if(buffer!= nullptr)
	*(buffer) << cout;
	else { cout << endl << "Элемент перед минимальным не существует" << endl; }
}

template<class T>
inline void Queue<T>::Save()
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
		Elem<T>* buf = Beginning();
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
inline void Queue<T>::Open()
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
			*Enque() >> (in);
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
inline bool Queue<T>::SavedCheck()
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
		Queue<T> New{ false };
		while (!(in.eof())) {
			if (New.Size() > Size()) return false;
			*New.Enque() >> in;
			if (New.End()->Info() != Find(New.End()->Index())->Info()) return false;
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
