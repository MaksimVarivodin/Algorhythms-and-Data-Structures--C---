#include "Header.h"
template <class T>
class Stack {
	//////////////////////////////
	//  переменные класса стек  //
	//////////////////////////////

	/* вершина стека */
	Elem<T>* top;
	/* дно стека */
	Elem<T>* bottom;
	/* размер стека */
	int size;
	/* расположение для сохранения и открытия */
	string Fpath;

	//////////////////////////////

	/* метод проверки пути к таблицы */
	bool CheckFpath() {
		return Fpath == "" || Fpath.find(".txt") == string::npos;
	};

	void SetPath(const string & path = "") {
		Fpath = path;
		bool check = CheckFpath();
		while (check) {
			cout << "Введите путь: ";
			getline(cin, Fpath);
			if (CheckFpath()) {
				check = true;
				cout << "Путь был введен неправильно" << endl;
			}
			else check = false;
		}
	};
	///////////////
	//  сеттеры  //
	///////////////

	/* вершина */
	void Top(Elem<T>* elmnt) { top = elmnt; };
	/* дно */
	void Bottom(Elem <T>* elmnt) { bottom = elmnt; };
	/* размер */
	void Size(const int& s) { size = s; };

	///////////////



	/////////////////////
	//  другие методы  //
	/////////////////////

	/* проверка на пустоту */
	bool Empty() {
		return size == 0 && top == nullptr;
	};
	/* метод печати символа */
	void PrintSymbol(char symb);
	/* метод поиска максимального или минимального элемента стека*/
	Elem <T>* MaxMin(const bool& max);
	/* метод заполнения одного элемента информацией */
	void Fff(Elem<T>* elmnt);

	/////////////////////



	///////////////////////////////////////////////
	//  методы для работы с указателями в стеке  //
	///////////////////////////////////////////////

	/* добавить элемент */
	Elem<T>* Push();
	/* вытащить элемент */
	Elem<T>* Pop();
	/* вставить сверху другой стек */
	void Add(Stack<T> other);
	/* вставить сверху один элемент */
	void Add(Elem<T>* one);
	/* вырезать сверху один элемент */
	Stack<T> Cut(Elem<T>* elmnt);
	/* забрать один элемент из середины */
	Elem<T>* Take(Elem <T>* elmnt);
	/* вставить элемент в середину */
	void Put(Elem <T>* elmnt, Elem<T>* last);
	/* создать стек заданного количества */
	void Create(const int & quantity);
	/* очистить список */
	void Clear();
	/* перегруженный оператор= */
	void operator= (const Stack<T>& other);

	////////////////////////////////////////////////



public:


	//////////////////////////////////
	//  конструкторы и деструкторы  //
	//////////////////////////////////

	/* конструктор по умолчанию */
	Stack<T>() : top(nullptr),bottom(nullptr), size(0), Fpath("") {};
	/* конструктор открыти таблицы */
	Stack(const bool open):Stack<T>{} 
	{
		if (open) {
			Open();
		}
	};
	/* конструктор создания стека по заданному количеству */
	Stack<T>(const int& quantity) : Stack<T>{} {
		Create(quantity);
	};
	/* конструктор копирования */
	Stack<T>(const Stack<T>& other) : Stack<T>{}
	{

		Elem<T>* buffer = other.bottom;
		while (buffer != nullptr) {
			Push();
			Top()->Paste(*buffer);
			buffer = buffer->Next();
		}
	};
	/* деструктор */
	~Stack<T>()
	{
		Clear();
	};

	//////////////////////////////////



	///////////////
	//  геттеры  //
	///////////////

	/* получение вершины */
	Elem<T>* Top() {
		return top;
	};
	/* получение дна */
	Elem<T>* Bottom() {
		return bottom;
	};
	/* получение размера */
	int Size() {
		return size;
	};

	///////////////

	

	/////////////////////////////////////////////////////
	//  операции над стеком в соответствии с заданием  //
	/////////////////////////////////////////////////////

	/* обмен двух элементов */
	void Swap(Elem<T>* one, Elem<T>* two);
	/* инвертирование стека */
	Stack<T> Invert();
	/* удаление каждого второго элемента стека */
	void DeleteEven();
	/* печать символа в середину стека или после среднего с условием */
	void Symbol(const char& symb);
	/* поиск максимального и вставка 0 */
	void Zero();
	/* удаление минимального  */
	void DeleteMin();
	/* удаление первого или послелнего */
	void DeleteFirstLast(const bool& first);	

	/////////////////////////////////////////////////////



	///////////////////////
	//  другие операции  //
	///////////////////////

	/* поиск элемента */
	Elem<T>* Find(const int& val);
	/* показать стек */
	void Show();
	/* проверка номеров элементов стека */
	void Renumb();
	/* сохранение стека */
	void Save();
	/* открытие стека из файла */
	void Open();
	/* проверка на сохранение в выбранном файле */
	bool SavedCheck();

	///////////////////////

};