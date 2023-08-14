#include "Stack_reals.h"
int main() {
	/* ��������� ������ � �������� */
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
	   "����",
	   "1 - �������� ������ � ���������",
	   "2 - �������������",
	   "3 - �������� ������ ���������",
	   "4 - ������� ����������� \"*\"",
	   "5 - ����� �������������, ������� \"0\"",
	   "6 - �������� ������������",
	   "7 - �������� c���, �������� ������",
	   "8 - �������� ����, �������� ���������",
	   "9 - �����"
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
		system("mode con cols=78 lines=200");//������� �������� ���� �������
		if (b == 1) {
			a.Show();
			cout << endl << "�������� ������ � ���������" << endl;
			a.Swap(a.Bottom(), a.Top());
			a.Show();
		}
		if (b == 2) {
			a.Show();
			Stack <double> buffer(a.Invert());
			cout << endl << "�������������" << endl;
			buffer.Show();
		}
		if (b == 3) {
			a.Show();
			a.DeleteEven();
			cout << endl << "�������� ������ ���������" << endl;
			a.Show();
		}
		if (b == 4) {
			a.Show();
			cout << endl << "������� ����������� \"*\"" << endl;
			a.Symbol('*');
		}
		if (b == 5) {
			a.Show();
			cout << endl << "����� �������������, ������� \"0\"" << endl;
			a.Zero();
		}
		if (b == 6) {
			a.Show();
			cout << endl << "�������� ������������" << endl;
			a.DeleteMin();
			a.Show();
		}
		if (b == 7) {
			a.Show();
			cout << endl << "�������� ������, �������� ������" << endl;
			a.DeleteFirstLast(true);
			a.Show();
		}
		if (b == 8) {
			a.Show();
			cout << endl << "�������� ������, �������� ���������" << endl;
			a.DeleteFirstLast(false);
			a.Show();
		}		
		a.Renumb();
		if (b == 9 || b == 0) {

			if (!a.SavedCheck()) {
				vector<string> str1{
	            "������ �� ���������, ���������?",
	            "1 - ��",
	            "2 - ���"
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
		system("mode con cols=78 lines=50");//������� �������� ���� �������

	}

}
