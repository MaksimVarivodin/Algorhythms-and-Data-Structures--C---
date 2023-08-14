#pragma once
#include <iostream>
#include <iomanip>
#include <ctime> 
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;
template<typename t1, typename t2>
void Enter_check(t1& a, const t2& max, const t2 & min) {
	bool ready = false;
	t1 var1 = max;
	t1 var2 = min;
	string er = "Число не входит в диапазон значений!\n Введите число еще раз: ";
	while (!ready) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		string b;

		// функция для ввода строки с пробелами

		getline(cin, b);
		try
		{
			try
			{
				// если дробное
				a = stod(b);
			}
			catch (const std::exception&)
			{
				// в других случаях
				a = stoll(b);
			}
			if (a < var2 || a > var1)  throw er;
			ready = true;
		}
		catch (const string& er)
		{
			cout << er;
		}
		catch (const std::exception&)
		{
			cout << "Замечены сторонние символы!\n Введите число еще раз: ";
		}
	}
}
struct BC {
	string symb;
	int num;
	BC(string symb0, int num0){
		symb = symb0;
		num = num0;
	};
	BC(){
		symb = "";
		num = 0;
	};
};
struct BigColor {
	BC Black;
	BC Blue;
	BC Green;
	BC Cyan;
	BC Red;
	BC Magenta;
	BC Brown;
	BC LightGray;
	BC DarkGray;
	BC LightBlue;
	BC LightGreen;
	BC LightCyan;
	BC LightRed;
	BC LightMagenta;
	BC Yellow;
	BC White;
	BigColor(){
		Black = BC{ "0", 0 };
		Blue = BC{ "1", 1 };
		Green = BC{ "2", 2 };
		Cyan = BC{ "3", 3 };
		Red = BC{ "4", 4 };
		Magenta = BC{ "5", 5 };
		Brown = BC{ "6", 6 };
		LightGray = BC{ "7", 7 };
		DarkGray = BC{ "8", 8 };
		LightBlue = BC{ "9", 9 };
		LightGreen = BC{ "A", 10 };
		LightCyan = BC{ "B", 11 };
		LightRed = BC{ "C", 12 };
		LightMagenta = BC{ "D", 13 };
		Yellow = BC{ "E", 14 };
		White = BC{ "F", 15 };
	};
};
struct MENU {
	BC Back;
	BC Text;
	vector <string> lines;
	vector<int> fillers;
	MENU()
	{
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		lines.resize(0);
		fillers.resize(0);
	}
	MENU(vector<string>b1, vector<int>b2)
	{
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		lines = b1;
		fillers = b2;
	}
	MENU(vector<string>b1, vector<int>b2, const BC&Text1, const BC& Back1)
	{
		Back = Back1;
		Text = Text1;
		lines = b1;
		fillers = b2;
	}
	~MENU()
	{
		lines.clear();
		fillers.clear();
	}
	int show();
	void color(const string & a);
	void punkt(const string & a, const int & b);

};

template <class T>
class Elem {
	int index;
	Elem* next;
	Elem* prev;
	T info;

public:
	Elem<T>() : index(0), next(nullptr), prev(nullptr) {};
	Elem<T>(const Elem<T>& other) :Elem{} {
		index = other.index;
		info = other.info;
		//next = other.next;
		//prev = other.next;
	};
	Elem(const int index0) :Elem{} {
		index = index0;
	};
	Elem<T>* Prev() { return prev; };
	void Prev(Elem<T>* other) { prev = other; };

	Elem<T>* Next() { return next; };
	void Next(Elem<T>* other) { next = other; };

	int Index() { return index; };
	void Index(int ind) { index = ind; };

	T Info() { return info; };
	void Info(T other) { info = other; };

	void Paste(const Elem<T>& other) {
		index = other.index;
		info = other.info;
	};
	void operator= (const Elem<T>& other) {
		index = other.index;
		info = other.info;
		next = other.next;
		prev = other.next;
	};
	/* операторы сравнения */
	bool operator >(Elem<T>* other) { return Info() > other->Info(); };
	bool operator <(Elem<T>* other) { return Info() < other->Info(); };
	bool operator >=(Elem<T>* other) { return Info() >= other->Info(); };
	bool operator <=(Elem<T>* other) { return Info() <= other->Info(); };
	bool operator ==(Elem<T>* other) {
		if (index == other->index && Info() == other->Info())
			return true;
		else return false;
	};
	bool operator !=(Elem<T>* other) { return index != other->index || Info() != other->Info(); };
	int ColCount(const int& a, const int& b);
	ostream& operator << (ostream& out);
	ostream& Shapka(ostream& out);
	/* операторы вывода из файла */
	istream& operator>> (istream& in);

	template<typename t1, typename t2>
	friend  void Enter_check(t1& a, const t2& max, const t2& min);

	template<typename V>
	friend istream& operator>> (istream& in, Elem<V>* a);
	~Elem()
	{
		next = nullptr;
		prev = nullptr;
	};
};

template<class T>
inline int Elem<T>::ColCount(const int& a, const int& b)
{
	int c = a + (b - 1 - a) / 2;
	return c;
}

template<class T>
inline ostream& Elem<T>::operator<<(ostream& out)
{

	int i = 0,
		text[2]{
		to_string(index).length(),
		to_string(info).length()
	},
		COL[2]{ 4, 15 },
		col[2]{};

	string txt[]{
	to_string(index),
	to_string(info)
	};

	for (int& var : col)
	{
		var = ColCount(text[i], COL[i]);
		i++;
	}
	i = 0;
	out << "\n";
	for (int var : col) {
		out << "|" << setw(col[i]) << txt[i] << setw(COL[i] - col[i]);
		i++;
	}
	out << "|\n"; out << " -----------------";
	return out;
}

template<class T>
inline istream& Elem<T>::operator>>(istream& in)
{
	// TODO: вставьте здесь оператор return
	string buf1;
	getline(in, buf1);
	int size = 2;
	vector<string> buf0(size);
	int length = 1;
	int counter = 0;
	while (length < buf1.length()) {
		if (buf1[length] != ' ' && (buf1[length] != '|' && length != 1))
			buf0[counter] += buf1[length];
		else if (buf1[length] == '|' && length != 1)
			counter++;
		length++;
	}
	try
	{
		// если дробное
		this->Info(stod(buf0[1]));
	}
	catch (const std::exception&)
	{
		// в других случаях
		this->Info(stoll(buf0[1]));
	}
	getline(in, buf1);
	return in;
}

template <class T>
ostream& Elem<T>::Shapka(ostream& out)
{
	// TODO: вставьте здесь оператор return
	out << " _________________";
	out << "\n/ # |    Число    \\";
	out << "\n -----------------";
	return out;
}

template<typename V>
inline istream& operator>>(istream& in, Elem<V>* a)
{
	cout << "Enter info to element " << a->Index() << ": ";
	V buffer = 0;
	Enter_check(buffer, 1000.0, -1000.0);
	a->Info(buffer);
	return in;
}