#include "List_class.h"



template<class T>
inline bool List<T>::SavedCheck()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
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
		int count = 0;


		buf = head;
		List<T> New{false};
		Elem<T>* buffer = nullptr;
		while (!(in.eof())) {
			if (buf == nullptr) return false;
			buffer = New.AddElement(buffer);
		    *buffer >> in;
			if ((buffer ->operator!= (buf))) return false;
			buf = buf->Next();			
		}
		if (buf->Next() != head) return false;
		in.close();	
	}
	catch (const std::exception&)
	{
		cout << "Ошибка oткрытия таблицы!\nНевозможно сравнить содержимое!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline bool List<T>::FrontAdd()
{
	string middle = "2 - В середину ";
	middle += size > 2 ? ("от 1 до " + to_string(size - 1)) : "(недоступно!)";
	vector<string>
		str1
	{
	"Выберите куда вставить: ",
	"1 - В начало",
	middle,
	"3 - В конец"
	},
		str2
	{
	"Выберите количество элементов: ",
	"1 - По умолчанию",
	"2 - Ввести вручную"
	},
		str3
	{
	"Выберите способ заполнения: ",
	"1 - Автоматически из файла",
	"2 - Вручную"
	};
	vector<int> fil1(str1.size()), fil2(str2.size()), fil3(str3.size());
	fil1[0] = 25;
	fil2[0] = 25;
	fil3[0] = 25;
	for (int i = 1; i < fil1.size(); i++)
		fil1[i] = 15;
	for (int i = 1; i < fil2.size(); i++)
		fil2[i] = 15;
	for (int i = 1; i < fil3.size(); i++)
		fil3[i] = 15;
	MENU m1(str1, fil1), m2(str2, fil2), m3(str3, fil3);

	int pos = 0, kol = 0, meth = 0;
	while (true) {
		pos = m1.show();
		if (pos == 1 || (size > 2 ? pos == 2 : false) || pos == 3)  break;
		if (pos == 0) return true;
	}
	while (true) {
		kol = m2.show();
		if (kol == 1 || kol == 2) break;
		if (kol == 0) return true;
	}
	while (true) {
		meth = m3.show();
		if (meth == 1 || meth == 2) break;
		if (meth == 0) return false;
	}
	try
	{
		if (!InnerAdd(pos, kol, meth)) throw exception{};
	}
	catch (const std::exception&)
	{
		cout << "Ошибка вставки!!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline bool List<T>::FrontDel()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
		return true;
	}
	string middle = "2 - Из середины ";
	middle += size > 2 ? ("от 1 до " + to_string(size - 1)) : "(недоступно!)";
	vector<string>
		str1
	{
	"Выберите откуда удалить: ",
	"1 - Из начала",
	middle,
	"3 - Из конца"
	},
		str2
	{
	"Выберите количество удаляемых элементов: ",
	"1 - По умолчанию",
	"2 - Ввести вручную"
	};
	vector<int> fil1(str1.size()), fil2(str2.size());
	fil1[0] = 25;
	fil2[0] = 25;

	for (int i = 1; i < fil1.size(); i++)
		fil1[i] = 15;
	for (int i = 1; i < fil2.size(); i++)
		fil2[i] = 15;

	MENU m1(str1, fil1), m2(str2, fil2);

	int pos = 0, kol = 0;
	while (true) {
		pos = m1.show();
		if (pos == 1 || (size > 2 ? pos == 2 : false) || pos == 3)  break;
		if (pos == 0) return true;
	}
	while (true) {
		kol = m2.show();
		if (kol == 1) { Clear(); return true; }
		if (kol == 2) break;
		if (kol == 0) return true;
	}

	try
	{
		// 	static void add(const int& pos, const int &kol, const int & meth);
		if (!InnerDel(pos, kol)) throw exception{};
	}
	catch (const std::exception&)
	{
		cout << "Ошибка удаления!!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline bool List<T>::InnerAdd(const int& pos, const int& kol, const int& meth)
{

	int pos1 = 1, kol1 = 20, meth1 = 0;
	string req1 = "Введите позицию после которой добавлять: ",
		req2 = "Введите количество добавляемых элементов: ";
	if (size > 0) {
		switch (pos) {
		case 2: cout << req1; Enter_check(pos1, size - 1, 1); break;
		case 3: pos1 = size; break;
		}
		buf = ((pos != 1) ? operator[](pos1) : nullptr);
	}
	else {
		buf = nullptr;
	}
	if (kol == 2) {
		cout << req2; Enter_check(kol1, 1000, 1);
	}
	try
	{
		for (int i = 0; i < kol1; i++)
		{
			buf = AddElement(buf);
			// в цикле
			switch (meth) {
			case 1: Fff(buf);// из файла
				break;
			case 2: 
				cin >> buf; // вручную
				break;
			}
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
inline bool List<T>::InnerDel(const int& pos, const int& kol)
{
	int pos1 = 1, kol1 = 20;
	string req1 = "Введите позицию c которой удалять(этот номер тоже удалится): ",
		req2 = "Введите количество удаляемых элементов: ";
	

	if (kol == 2) {
		switch (pos) {
		case 1: cout << req2; Enter_check(kol1, size, 1); break;
		case 2: cout << req2; Enter_check(kol1, size - pos1, 1); break;
		case 3: cout << req2; Enter_check(kol1, size, 1); break;
		}

	}
	if (size > 0) {
		switch (pos) {
		case 2: if (size <= 2)return true; cout << req1; Enter_check(pos1, size - 1, 1); break;
		case 3: pos1 = size - kol1; break;
		}
		buf = operator[](pos1);
	}
	else { return true; }
	try
	{
		for (int i = 0; i < kol1; i++)
		{
			buf = DelElement(buf);
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;

}




template<class T>
Elem<T>* List<T>::operator[](const int& number) {
	if (Empty()) {
		cout << "Список пуст." << endl;
		return nullptr;
	}
	if (number < 1)
		return head;
	else if (number > size)
		return head->Prev();
	Elem<T>* buffer = head;
	do
    buffer = buffer->Next();
	while (buffer->Index() != number && buffer != nullptr);
	return buffer;
}

template<class T>
inline bool List<T>::Swap()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
		return true;
	}
	string var1 = "Введите номер 1-го элемента: ",
		var2 = "Введите номер 2-го элемента: ";
	int num1 = 0, num2 = 0;
	cout << var1; Enter_check(num1, size, 1);
	cout << var2; Enter_check(num2, size, 1);
	try
	{
		
		Elem<T>* buf1 = operator[](num1), * buf2 = operator[](num2);
		system("pause");
		system("cls");
		SwapPointers(buf1, buf2);
	}
	catch (const std::exception&)
	{
		cout << "Ошибка свапа!!" << endl;
		return false;
	}
	return true;
	
}



template<class T>
inline bool List<T>::Save()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
		return true;
	}

	vector<string>
		str1
	{
	"Выберите путь:",
	"1 - По умолчанию",
	"2 - Текущий",
	"3 - Ввести вручную"
	};

	T search_val = 0;
	bool bigger = false;
	int counter = 0;
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
		else if (m == 0) { return true; }
	}
	try
	{
		ofstream out;
		out.open(Fpath);
		buf = head;
		buf->Shapka(out);
		do {
			*buf << out;
			buf = buf->Next();
		} while (buf != head);
		out.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка сохранения таблицы!" << endl;
		return false;
	}
	cout << "Данные сохранены в: " << Fpath << endl;
	return true;
}


template<class T>
inline bool List<T>::Open()

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
		else if (m == 0) { return true; }
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
		buf = head;
		while (!(in.eof())) {
			buf = AddElement(buf);
			*buf >> (in);
		}
		in.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка oткрытия таблицы!" << endl;
		Save();
		return false;
	}
	cout << "Данные были считаны из файла: " << Fpath << endl;
	return true;
}


template<class T>
inline void List<T>::Info()
{
	cout << "Фамилия: Вариводин\nИмя: Максим\nГруппа: КН-320Б\n" <<
		"Рабочая почта: maksym.varivodin@gmail.com\n"<<
		"Специальность: 122 - Компьютерные науки\n";
}



template<class T>
inline void List<T>::SwapPointers(Elem<T>* a, Elem<T>* b)
{
	if (a == nullptr || b == nullptr || head == nullptr || head->Prev() == nullptr || a == b) return;
	Elem <T>* buffer = nullptr;
	if (a == head->Prev() || b == head || b->Next() == a) {
	/*  swapPointers(a, b)  */
		buffer = b;
		b= a;
		a= buffer;
	}

	/*  swapPointers(a->prev, b->prev)  */

	buffer = b->Prev();
	b->Prev(a->Prev());
	a->Prev(buffer);
	
	/*  swapPointers(a->next, b->next)  */

	buffer = b->Next();
	b->Next(a->Next());
	a->Next(buffer);


	if (a->Prev() != a) {
		a->Prev()->Next(a);
		b->Next()->Prev(b);
	}
	else if (a->Prev() == a) {
		
		/*  swapPointers(a->prev, b->next)  */ 

		b->Next(a->Prev());
		a->Prev(buffer);   /* buffer from swapPointers(a->next, b->next) */
	
	}
	if (!(a->Prev() == a && a == head && b == head->Prev())) {
		if (b != head->Prev())a->Next()->Prev(a);
		if (a != head)b->Prev()->Next(b);
	}
	head = a == head ? b : head;
}



template<class T>
inline void List<T>::Renumb()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
		return;
	}
	int ind = 0;
	buf = head;
	do {
		ind++;
		buf->Index(buf->Index() == ind ? buf->Index() : ind);
		buf = buf->Next();
	} while (buf != head);
}







template <class T>
Elem <T>* List<T>::AddElement(Elem <T>* current)
{
	size++;
	buf = new Elem<T>{ size }; // выделение памяти под следующий элемент 
	/* если переданная голова пуста, то присваиваем */
	if (head == nullptr) head = buf;
	/* если элемент для вставки это ноль,
	   то значит нужно создать новый корень */
	else if (head->Next() == nullptr)
	{
		head->Prev(head);
		head->Next(buf);
	}
	if (current == nullptr) {
		buf->Next(head);
		head->Prev(buf);
		head = buf;
	}
	else {
		buf->Next(current->Next());
		buf->Prev(current);
		current->Next(buf);
		buf->Next()->Prev(buf);
	}
	return buf;
}




template <class T>
Elem <T>* List<T>::DelElement(Elem <T>* current)
{
	size--;
	if (head == nullptr || current == nullptr) { buf = nullptr; size++; }
	/* один элемент */
	if (current->Next() == current->Prev() && current->Next() == nullptr) {
		buf = nullptr;
	}
	/* два элемента */
	else if (current->Next() == current->Prev()) {
		buf = current->Next();
		head->Next(nullptr);
		head->Prev(nullptr);
	}
	else {
		buf = current->Next();
		current->Next()->Prev(current->Prev());
		current->Prev()->Next(current->Next());
	}
	if (current == head)
		head = buf;
	if(current!= nullptr)
	delete current;
	return buf;
}




template<class T>
inline bool List<T>::Clear()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
		return true;
	}
	buf = head;
	try
	{
		while (size > 0) {
			buf = DelElement(buf);		
		}
		head = nullptr;
		size = 0;
	}
	catch (const std::exception&)
	{
		cout << "Ошибка очистки списка!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline void List<T>::SetPath(const string& path)
{
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
}

template<class T>
inline void List<T>::Fff(Elem<T>* ToFill)
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
			ToFill->Info(a[b]);
		}
		catch (const string& err)
		{
			cout << err << endl;
		}

	}
	CIN.close();
}

template<class T>
inline void List<T>::Show()
{
	if (Empty()) {
		cout << "Список пуст." << endl;
		return;
	}
	buf = head;
	buf->Shapka(cout);
	int counter = 0;
	do{
		*buf << cout;
		buf = buf->Next();
		counter++;
	} while (buf != head);
	cout << endl << "Количество выведенных элементов: " << counter << endl;
	cout << "Текущее количество элементов в списке: " << size << endl;

}


