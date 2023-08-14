#include "Header.h"
template <class T>
class Stack {
	//////////////////////////////
	//  ���������� ������ ����  //
	//////////////////////////////

	/* ������� ����� */
	Elem<T>* top;
	/* ��� ����� */
	Elem<T>* bottom;
	/* ������ ����� */
	int size;
	/* ������������ ��� ���������� � �������� */
	string Fpath;

	//////////////////////////////

	/* ����� �������� ���� � ������� */
	bool CheckFpath() {
		return Fpath == "" || Fpath.find(".txt") == string::npos;
	};

	void SetPath(const string & path = "") {
		Fpath = path;
		bool check = CheckFpath();
		while (check) {
			cout << "������� ����: ";
			getline(cin, Fpath);
			if (CheckFpath()) {
				check = true;
				cout << "���� ��� ������ �����������" << endl;
			}
			else check = false;
		}
	};
	///////////////
	//  �������  //
	///////////////

	/* ������� */
	void Top(Elem<T>* elmnt) { top = elmnt; };
	/* ��� */
	void Bottom(Elem <T>* elmnt) { bottom = elmnt; };
	/* ������ */
	void Size(const int& s) { size = s; };

	///////////////



	/////////////////////
	//  ������ ������  //
	/////////////////////

	/* �������� �� ������� */
	bool Empty() {
		return size == 0 && top == nullptr;
	};
	/* ����� ������ ������� */
	void PrintSymbol(char symb);
	/* ����� ������ ������������� ��� ������������ �������� �����*/
	Elem <T>* MaxMin(const bool& max);
	/* ����� ���������� ������ �������� ����������� */
	void Fff(Elem<T>* elmnt);

	/////////////////////



	///////////////////////////////////////////////
	//  ������ ��� ������ � ����������� � �����  //
	///////////////////////////////////////////////

	/* �������� ������� */
	Elem<T>* Push();
	/* �������� ������� */
	Elem<T>* Pop();
	/* �������� ������ ������ ���� */
	void Add(Stack<T> other);
	/* �������� ������ ���� ������� */
	void Add(Elem<T>* one);
	/* �������� ������ ���� ������� */
	Stack<T> Cut(Elem<T>* elmnt);
	/* ������� ���� ������� �� �������� */
	Elem<T>* Take(Elem <T>* elmnt);
	/* �������� ������� � �������� */
	void Put(Elem <T>* elmnt, Elem<T>* last);
	/* ������� ���� ��������� ���������� */
	void Create(const int & quantity);
	/* �������� ������ */
	void Clear();
	/* ������������� ��������= */
	void operator= (const Stack<T>& other);

	////////////////////////////////////////////////



public:


	//////////////////////////////////
	//  ������������ � �����������  //
	//////////////////////////////////

	/* ����������� �� ��������� */
	Stack<T>() : top(nullptr),bottom(nullptr), size(0), Fpath("") {};
	/* ����������� ������� ������� */
	Stack(const bool open):Stack<T>{} 
	{
		if (open) {
			Open();
		}
	};
	/* ����������� �������� ����� �� ��������� ���������� */
	Stack<T>(const int& quantity) : Stack<T>{} {
		Create(quantity);
	};
	/* ����������� ����������� */
	Stack<T>(const Stack<T>& other) : Stack<T>{}
	{

		Elem<T>* buffer = other.bottom;
		while (buffer != nullptr) {
			Push();
			Top()->Paste(*buffer);
			buffer = buffer->Next();
		}
	};
	/* ���������� */
	~Stack<T>()
	{
		Clear();
	};

	//////////////////////////////////



	///////////////
	//  �������  //
	///////////////

	/* ��������� ������� */
	Elem<T>* Top() {
		return top;
	};
	/* ��������� ��� */
	Elem<T>* Bottom() {
		return bottom;
	};
	/* ��������� ������� */
	int Size() {
		return size;
	};

	///////////////

	

	/////////////////////////////////////////////////////
	//  �������� ��� ������ � ������������ � ��������  //
	/////////////////////////////////////////////////////

	/* ����� ���� ��������� */
	void Swap(Elem<T>* one, Elem<T>* two);
	/* �������������� ����� */
	Stack<T> Invert();
	/* �������� ������� ������� �������� ����� */
	void DeleteEven();
	/* ������ ������� � �������� ����� ��� ����� �������� � �������� */
	void Symbol(const char& symb);
	/* ����� ������������� � ������� 0 */
	void Zero();
	/* �������� ������������  */
	void DeleteMin();
	/* �������� ������� ��� ���������� */
	void DeleteFirstLast(const bool& first);	

	/////////////////////////////////////////////////////



	///////////////////////
	//  ������ ��������  //
	///////////////////////

	/* ����� �������� */
	Elem<T>* Find(const int& val);
	/* �������� ���� */
	void Show();
	/* �������� ������� ��������� ����� */
	void Renumb();
	/* ���������� ����� */
	void Save();
	/* �������� ����� �� ����� */
	void Open();
	/* �������� �� ���������� � ��������� ����� */
	bool SavedCheck();

	///////////////////////

};