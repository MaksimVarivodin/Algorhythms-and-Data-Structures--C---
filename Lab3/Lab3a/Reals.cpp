#include "Header.h"

#pragma once

int MENU::show()
{
	// ��������� ������� ��������
	if (fillers.size() != lines.size())
		return -1;

	// ������ � ��������
	// _________________
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);
	// _________________

	// ���������� ����������
	int choice;
	int pos = 1;

	// ��������� ������ ������ �������
	string back_txt = "color " + Back.symb + Text.symb;

	// ����������� ����
	for (;;)
	{
		// ������� ���������� ���� � ������ �������
		system(back_txt.c_str());
		// ���� ������ ������� ����
		for (int iter = 0; iter < fillers.size(); iter++) {
			if (iter != pos) {
				cout << setw(fillers[iter] + lines[iter].length()) << lines[iter] << endl;
			}
			else punkt(lines[pos], fillers[iter]);
		}
		// ��������� ��������� �������
		choice = _getch();
		choice = choice == 224 ? _getch() : choice;// down , up
		system("cls");
		// ��������� ������
		if (choice == 13)return pos; // enter
		else if (choice == 27)return 0; // esc
		else if (choice == 72) pos = pos == 1 ? lines.size() - 1 : pos - 1;// up
		else if (choice == 80) pos = pos == lines.size() - 1 ? 1 : pos + 1;// down
	}
}
// ������� ������������ ����������� ������ � �����
void MENU::color(const string& a) {
	// 1 - ���, 2 - �����
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	BigColor col;
	SetConsoleTextAttribute(hConsole, (WORD)((col.Black.num << 4) | col.White.num));
	cout << a;
	SetConsoleTextAttribute(hConsole, (WORD)((Back.num << 4) | Text.num));
}
// ������� ������� ���������� ����� ������ �������
void MENU::punkt(const string& a, const int& b) {
	cout << setw(b) << "--> ";
	color(a);
	cout << endl;
}
int TABLE::menuMode()
{
	if (!this->menuSH || !ColumnsEqual() || t.size() == 0)
	{
		cout << "MenuMode not on." << endl;
		return -1;
	}
	// ������ � ��������
	// _________________
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);
	// _________________

	// ���������� ����������
	int choice;
	int pos = 0;

	// ��������� ������ ������ �������
	string back_txt = "color " + sh.B().symb + sh.T().symb;

	// ����������� ����
	for (;;)
	{
		// ������� ���������� ���� � ������ �������
		system(back_txt.c_str());
		if (showSH)
		{
			sh << cout;
			cout << string(sh.I() + 1, ' ') + string(sh.L(), '-') << endl;
		}
		// ���� ������ ������� ����
		for (int iter = 0; iter < t.size(); iter++) {
			if (iter != pos) {
				cout << Line(t[iter]);
			}
			else ColourLine(cout, t[iter]);
		}
		// ��������� ��������� �������
		choice = _getch();
		choice = choice == 224 ? _getch() : choice;// down , up
		system("cls");
		// ��������� ������
		if (choice == 13)return pos; // enter
		else if (choice == 27)return -1; // esc
		else if (choice == 72) pos = pos == 0 ? t.size() - 1 : pos - 1;// up
		else if (choice == 80) pos = pos == t.size() - 1 ? 0 : pos + 1;// down
	}
}