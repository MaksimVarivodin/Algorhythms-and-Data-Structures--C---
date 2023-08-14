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
#include <cassert>
#include <stdlib.h>
#include <cmath>
#include <sstream>
using namespace std;


/*  метод проверки ввода  */
template<typename t1, typename t2>
void Enter_check(t1& a, const t2& max, const t2& min) {
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


/*  структура одного цвета  */
struct BC {
	string symb;
	int num;
	BC(string symb0, int num0) {
		symb = symb0;
		num = num0;
	};
	BC() {
		symb = "";
		num = 0;
	};
	BC(const BC& other) {
		symb = other.symb;
		num = other.num;
	};

};


/* структура содержащая весь массив цветов  */
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
	BigColor() {
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


/*  структура меню  */
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
	MENU(vector<string>b1, vector<int>b2, const BC& Text1, const BC& Back1)
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
	void color(const string& a);
	void punkt(const string& a, const int& b);

};


/*  класс шапка  */
class SHAPKA {

	/*  вектор колонок  */
	vector<string> cols;

	/*  вектор размеров  */
	vector<int> sizes;

	/*  отступы  */
	int indent;

	/*  размеры  */
	int length;

	/*  цвет меню  */
	BC Back;
	BC Text;


	/*  пересчет длины  */
	void L_Recalc() {
		length = 0;
		for (int x : sizes)
			length += x - 1;
		length += sizes.size() - 1;
	}

public:


	/*  конструктор по переданным строкам  */
	SHAPKA(vector<string> columns) :indent(1) {
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		cols = columns;
		int i = 0;
		sizes.resize(cols.size());
		for (int& x : sizes) {
			x = columns[i].length() + 3;
			i++;
		}
		L_Recalc();
	};


	/*  конструктор со строками и заданными размерами полей  */
	SHAPKA(vector<string>columns, vector<int> sizes0) :indent(1)
	{
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		cols = columns;
		for (int& x : sizes0) {
			x++;
		}
		sizes = sizes0;
		L_Recalc();
	};


	/*  конструктор по умолчанию  */
	SHAPKA() :SHAPKA{ vector<string>{""} } {};


	/*  конструктор по умолчанию + отступы  */
	SHAPKA(const int& a) : SHAPKA()
	{
		indent = a;
	};


	/*  конструктор отступы + колонки  */
	SHAPKA(const int& a, vector<string> columns) :SHAPKA{ columns } {
		indent = a;
	};


	/*  конструктор отступы + колонки  */
	SHAPKA(const int& a, vector<string> columns, const BC& Back1, const BC& Text1) :SHAPKA{ columns } {
		indent = a;
		Back = Back1;
		Text = Text1;
	};


	/*  конструктор отступы + колонки + размеры  */
	SHAPKA(const int& a, vector<string>columns, vector<int> sizes0) : SHAPKA(columns, sizes0)
	{
		indent = a;
	};


	/*  конструктор отступы + колонки + размеры  */
	SHAPKA(const int& a, vector<string>columns, vector<int> sizes0, const BC& Back1, const BC& Text1) : SHAPKA(columns, sizes0)
	{
		indent = a;
		Back = Back1;
		Text = Text1;
	};


	/*  конструктор отступы + размеры  */
	SHAPKA(vector<int> sizes0, const BC& Back1, const BC& Text1, const int& a = 0) {
		indent = a;
		cols = vector<string>(sizes0.size(), "");
		sizes = sizes0;
		L_Recalc();
		Back = Back1;
		Text = Text1;
	};


	/*  конструктор отступы + размеры  */
	SHAPKA(vector<int> sizes0, const int& a = 0) {
		indent = a;
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		cols = vector<string>(sizes0.size(), "");
		sizes = sizes0;
		L_Recalc();
	};





	/*  конструктор копирования  */
	SHAPKA(const SHAPKA& other) { operator=(other); };


	/*  деструктор  */
	~SHAPKA()
	{
	};

	/*  геттеры  */
	vector<int> S() const { return sizes; };
	vector<string>  C() const { return cols; };
	int I() const { return indent; };
	int L() { return length; };
	BC B() { return Back; };
	BC T() { return Text; };


	/*  рассчет размера отступов  */
	int ColCount(const int& a, const int& b)
	{
		int c = a + (b - 1 - a) / 2;
		return c;
	};


	/*   перегруженный оператор равно */
	SHAPKA& operator=(const SHAPKA& other) {
		this->cols = other.cols;
		this->sizes = other.sizes;
		this->indent = other.indent;
		this->Back = other.Back;
		this->Text = other.Text;
		L_Recalc();
		return *this;
	}


	/*  перегруженный оператор вывода  */
	ostream& operator<<(ostream& out) {
		string a = string(indent + 5, ' ') + string(L(), '_');
		out << a << "\n" << string(indent + 4, ' ') << "|";
		vector<int> CC(cols.size(), 0);
		for (int i = 0; i < cols.size(); i++) {
			CC[i] = ColCount(cols[i].length(), sizes[i]);
			out << setw(CC[i]) << cols[i] << setw(sizes[i] - CC[i]);
			if (i + 1 < cols.size())
				out << "|";
		}
		out << "|" << "\n";
		return out;
	};

};


/*  класс таблица  */
class TABLE {
	bool showSH;
	bool menuSH;
	SHAPKA sh;
	vector<vector<string>> t;

public:
	string Line(vector<string> col) {
		string b = string(sh.I() + 5, ' ') + string(sh.L(), '-');
		vector<int> CC(sh.C().size(), 0);
		string buffer = b + "\n" + string(sh.I() + 4, ' ') + "|";
		for (int i = 0; i < sh.C().size(); i++) {
			CC[i] = sh.ColCount(col[i].length(), sh.S()[i]);
			short x = CC[i] - col[i].length();
			if (x > 0)
				buffer += string(CC[i] - col[i].length(), ' ');
			buffer += col[i];
			x = (sh.S()[i] - CC[i] - 1);
			if (x > 0)
				buffer += string(sh.S()[i] - CC[i] - 1, ' ');
			buffer += "|";
		}
		buffer += "\n" + b + "\n";
		return buffer;
	};
	ostream& ColourString(ostream& out, string l) {
		// 1 - фон, 2 - текст
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((sh.T().num) << 4) | sh.B().num);
		out << l;
		SetConsoleTextAttribute(hConsole, (WORD)((sh.B().num) << 4) | sh.T().num);
		return out;
	}
	ostream& ColourLine(ostream& out, vector <string> col) {

		string buffer = "|";
		vector<int> CC(sh.C().size(), 0);
		for (int i = 0; i < sh.C().size(); i++) {
			CC[i] = sh.ColCount(col[i].length(), sh.S()[i]);
			short x = CC[i] - col[i].length();
			if (x > 0)
				buffer += string(CC[i] - col[i].length(), ' ');
			buffer += col[i];
			x = (sh.S()[i] - CC[i] - 1);
			if (x > 0)
				buffer += string(sh.S()[i] - CC[i] - 1, ' ');
			buffer += "|";
		}


		out << string(sh.I() + 4, ' ');
		ColourString(out, " " + string(sh.L(), '-') + " ");
		out << "\n";

		out << string(sh.I(), ' ');
		out << "--> ";
		ColourString(out, buffer);
		out << "\n";
		out << string(sh.I() + 4, ' ');
		ColourString(out, " " + string(sh.L(), '-') + " ");
		out << "\n";
		return out;
	}
	ostream& operator<<(ostream& out) {
		if (showSH)
		{
			sh << out;
			out << string(sh.I() + 5, ' ') + string(sh.L(), '-') << endl;
		}
		if (t.size() == 0)
			out << string(sh.I(), ' ') << "Empty table" << endl;
		for (vector<string>x : t)
			out << Line(x);
		return out;
	};
	TABLE() {
		sh = SHAPKA{};
		showSH = true;
	};
	TABLE(SHAPKA sh0, const bool& show) :TABLE() {
		sh = sh0;
		showSH = show;
	};
	TABLE(SHAPKA sh0, const bool& show, const bool& menu) :TABLE() {
		sh = sh0;
		showSH = show;
		menuSH = menu;
	};
	TABLE(SHAPKA sh0, vector<vector<string>> t0) :TABLE() {
		if (sh0.S().size() == t0[0].size())
		{
			sh = sh0;
			t = t0;
		}
		else
			cout << "Error creating a table" << endl;
	};
	TABLE(SHAPKA sh0, vector<vector<string>> t0, const bool& show) :TABLE(sh0, t0) {
		if (sh0.S().size() == t0[0].size())
			showSH = show;
	};
	TABLE(SHAPKA sh0, vector<vector<string>> t0, const bool& show, const bool& menu) :TABLE(sh0, t0) {
		if (sh0.S().size() == t0[0].size())
			showSH = show;
		menuSH = menu;
	};
	TABLE(const bool& show) :TABLE() { showSH = show; };
	vector<vector<string>> T() { return t; };
	void T(vector<vector<string>> a) { t = a; };
	void S(SHAPKA a) { sh = a; };

	int menuMode();
	bool ColumnsEqual() {
		int max = 1;
		for (vector<string>a : t)
			if (a.size() > max || a.size() < max)
				return false;
		return true;
	}
};


template <typename T>
vector<vector<T>> VM_creator(vector<int>& s, const int& size, const T& c) {
	int S = sqrt(size);
	s = vector<int>(S);
	vector<vector<T>> arr1(S, vector<T>(0));
	for (int i = 0; i < S; i++)
	{
		s[i] = S;
		if (i == (S - 1))
			s[i] += size - (S * S);
		arr1[i] = vector<T>(s[i]);
		for (int j = 0; j < s[i]; j++) {

			arr1[i][j] = (i * S + j + 1) * c;
		}
	}
	return arr1;
}
template <typename T>
vector<T> Vfiller(const int& size, const T& c = 1) {
	int S = sqrt(size);
	vector<int> s;
	vector<T> arr(size);
	vector<vector<T>> buf = VM_creator(s, size, c);
	for (int i = 0; i < size; i++) {
		int a = rand() % S;
		int b = rand() % s[a];
		s[a]--;
		arr[i] = buf[a][b];
		buf[a].erase(buf[a].begin() + b);
		if (s[a] == 0) {
			buf.erase(buf.begin() + a);
			s.erase(s.begin() + a);
			S--;
		}
	}
	return arr;
}
