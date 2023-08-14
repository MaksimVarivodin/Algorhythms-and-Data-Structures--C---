#include "Queue_reals.h"
int main() {
	/* ��������� ������ � �������� */
	BigColor Color;
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title ������� ��������� ����-��������� �� �������");
	system("mode con cols=78 lines=50");

	string back_txt = "color " + Color.White.symb + Color.Black.symb;
	system(back_txt.c_str());
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);

	Queue<double> a(true);

	vector<string> str{
	   "���� ",
	   "1 - �������� ���������� �������",
	   "2 - ��������� ������� ������ ������",
	   "3 - �������� ����� � �������� ����� ������",
	   "4 - �������� ������ ����� ������",
	   "5 - ����� �� ������� ��������"
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
		system("mode con cols=78 lines=500");//������� �������� ���� �������
		if (b == 1) {
			a.Show();
			cout << endl << "�������� ���������� ���������" << endl;
			cout << a.Size() << endl;
		}
		if (b == 2) {
			a.Show();
			cout << endl << " ��������� ������� ��������������" << endl;
			cout << a.Average() << endl;
		}
		if (b == 3) {
			a.Show();
			cout << endl << "�������� ����������� � ������������ ��������" << endl;
			a.PrintMinMax();
			cout << endl;
		}
		if (b == 4) {
			a.Show();
			cout << endl << "�������� ������� �� ������������" << endl;
			a.PrintMinPrev();
			cout << endl;
		}
		if (b == 5 || b == 0) {

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
	system("cls");
	cout << "����� �����! ��� ���! ������� ������� ����� �*�!" << endl;
}