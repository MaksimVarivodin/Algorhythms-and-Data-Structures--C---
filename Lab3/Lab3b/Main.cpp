#include "RBTree_class.h"
int main() {

	/* ��������� ������ � �������� */
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
	   "����",
	   "1 - ������� ������",
	   "2 - ������ ���� �������",
	   "3 - ����������� �������",
	   "4 - �������",
	   "5 - �������",
	   "6 - ��������",
	   "7 - �������� �������� ����",
	   "8 - ��������� � ���� �������",
	   "9 - ��������� � ���� ������",
	   "10 - �����"
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
		system("mode con cols=78 lines=200");//������� �������� ���� �������
		if (b == 1) {  a.Open(); cout << "1 - ������� ������" << endl; }
		else if (b == 2) { a.TypeIn(); cout << "2 - ������ �������" << endl; }
		else if (b == 3) { a.Show(); cout << "3 - ����������� �������" << endl;  }
		else if (b == 4) { a.Order(); cout << "4 - �������" << endl;  }
		else if (b == 5) { a.Clear(); cout << "5 - �������" << endl;  }
		else if (b == 6) { a.Delete(); cout << "6 - ��������" << endl; }
		else if (b == 7) { a.KeyVarChange().Show(); cout << "7 - �������� �������� ����" << endl; }
		else if (b == 8) { a.Save(); cout << "8 - ��������� � ���� �������" << endl;  }
		else if (b == 9) { a.SaveTree(); cout << "9 - ��������� � ���� ������" << endl; }
		else if (b == 10 || b == 0) { cout << "10 - �����" << endl;break; }
		  		
        system("pause");
        system("mode con cols=78 lines=50");//������� �������� ���� �������

	}

}