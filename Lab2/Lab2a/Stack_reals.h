#include "Stack_class.h"


template<class T>
inline void Stack<T>::DeleteEven()
{
	int Size = size;
	Elem<T>* buffer = Bottom();
	for (int i = 0; i < Size; i++) {
		int count = buffer->Index()+ 1;
		if ((i + 1) % 2 == 0) {
			buffer = Take(buffer); 
			delete buffer;
		}
		if(count <= Size)
		buffer = Find(count);
	}
}

template<class T>
inline void Stack<T>::Symbol(const char& symb)
{
	Elem<T>* buffer = Bottom();
	while (buffer != nullptr) {
		buffer->operator<<(cout);	
		if (size % 2 == 0)
		{		
			if (buffer->Index() == size / 2)
				PrintSymbol(symb);
		}
		else
		{
			if (buffer->Index() == size / 2 + 1)
				PrintSymbol(symb);
		}
		buffer = buffer->Next();
	}
}


template<class T>
inline void Stack<T>::PrintSymbol(char symb)
{
	string symb0 = "";
	symb0 += symb;
	string txt[]{
    "N/A",
    symb0
	};
	int i = 0,
		text[2]{
		txt[0].length(),
		txt[1].length()
	},
		COL[2]{ 4, 15 },
		col[2]{};

	Elem<T>* buffer = nullptr;

	for (int& var : col)
	{
		var = buffer ->ColCount(text[i], COL[i]);
		i++;
	}
	i = 0;
	cout << "\n";
	for (int var : col) {
		cout << "|" << setw(col[i]) << txt[i] << setw(COL[i] - col[i]);
		i++;
	}
	cout << "|\n"; cout << " -----------------";
}

template<class T>
inline Elem<T>* Stack<T>::MaxMin(const bool& max)
{
	Elem<T>* buffer = Bottom(), *to_ret = buffer;
	while (buffer != nullptr) {
		to_ret = max ? (to_ret->Info() < buffer->Info() ? buffer:to_ret) : (to_ret->Info() > buffer->Info() ? buffer : to_ret);
		buffer = buffer->Next();
	}
	return to_ret;
}

template<class T>
inline void Stack<T>::Zero()
{
	Elem <T>* buffer1 = MaxMin(true), 
		*buffer2 = Bottom();
	while (buffer2 != nullptr) {
		*(buffer2) << cout;
		if (buffer2 == buffer1)
			PrintSymbol('0');
			
		buffer2 = buffer2->Next();
	}
}

template<class T>
inline void Stack<T>::DeleteMin()
{
	Elem <T>* buffer = Take(MaxMin(false));
	delete buffer;
}

template<class T>
inline void Stack<T>::DeleteFirstLast(const bool& first)
{
	Elem<T>* buffer = Take(first? Bottom(): Top());
	Clear();
	Add(buffer);
}

template<class T>
inline Elem<T>* Stack<T>::Push()
{
	Elem<T>* elmnt = new Elem<T>();

	if (Top() != nullptr) {
		Top()->Next(elmnt);
		Top()->Next()->Prev(Top());
	}
	else Bottom(elmnt);
	Top(elmnt);
	size++;
	Top()->Index(size);
	return top;
}

template<class T>
inline Elem<T>* Stack<T>::Pop()
{
	Elem<T>* buf = nullptr;
	if (Top() == nullptr && Size() == 0 && Bottom () == nullptr) return nullptr;
	else if (Top()->Prev()!= nullptr) {
		top = top->Prev();
		buf = top->Next();
		top->Next(nullptr);
	}
	else {
		buf = top;
		Top(nullptr);
		Bottom(nullptr);
	}
	delete buf;
	size--;
	return top;
}


template<class T>
inline void Stack<T>::Show()
{

	Elem<T>* buffer = Bottom();
	buffer->Shapka(cout);
	while (buffer != nullptr) {
		*(buffer)<< cout;
		buffer = buffer->Next();
	}
	cout << endl;
}


template<class T>
inline Stack<T> Stack<T>::Invert()
{
	Stack New;
	Elem<T>* buffer = Top();
	while (buffer != nullptr) {
		New.Push();
		New.Top()->Paste(*buffer);
		buffer = buffer->Prev();
	}
	return New;
}

template<class T>
inline void Stack<T>::Add(Stack<T> other)
{
	while (other.Size() > 0) {
		Push();
		Top()->Paste(*(other.Top()));
		other.Pop();
	}
}

template<class T>
inline void Stack<T>::Add(Elem<T>* one)
{
	Push()->Paste(*(one));

}

template<class T>
inline Stack<T> Stack<T>::Cut(Elem<T>* elmnt)
{
	Stack<T> New;
	Elem<T>* buffer = Top();
	if(Top() != nullptr)
	while (buffer != elmnt) {
		New.Push();// создаем новый элемент
		New.Top()->Paste(*buffer); // вставляем в него информацию
		Pop();
		buffer = Top();
	}
	return New;
}

template<class T>
inline Elem<T>* Stack<T>::Find(const int& val)
{
	Elem <T>* buffer = Bottom();
	while (buffer->Index() != val && buffer != nullptr)
		buffer = buffer->Next();
	if (buffer == nullptr)return nullptr;
	return buffer;
}

template<class T>
inline void Stack<T>::Swap(Elem<T>* one, Elem<T>* two)
{
	if (one == two || one == nullptr || two == nullptr) return;
	int index1 = one->Index(),
		index2 = two->Index();
	if (index1 > index2) {
		int buffer = index1;
		index1 = index2;
		index2 = buffer;
	}
	Stack<T> st1;
	if (Find(index1) != Bottom())
		st1 = Cut(Find(index1 - 1)).Invert();
	else st1 = Cut(nullptr).Invert();
	Elem<T>* buffer1 = st1.Take(st1.Find(index1));
	Stack<T> st2;
	if(st1.Find(index2) != st1.Bottom())
	st2 = st1.Cut(st1.Find(index2 - 1)).Invert();
	else st2 = st1.Cut(nullptr).Invert();
	Elem<T>* buffer2 = st2.Take(st2.Find(index2));
	Add(buffer2);
	Add(st1.Invert());
	Add(buffer1);
	Add(st2.Invert());
}

template<class T>
inline Elem<T>* Stack<T>::Take(Elem<T>* elmnt)
{
	Stack<double> New{ elmnt == Top() ? Stack{} : Cut(elmnt) };// стек под верхнюю часть
	Elem <double>* buffer = new Elem<double>{*(Top())};
	Pop();// удаляем вырезанный элемент
	Add(New);// вставляем верхнюю часть
	return buffer;// возвращаем вырезанную инфу
}

template<class T>
inline void Stack<T>::Put(Elem<T>* elmnt, Elem<T>* last)
{
	Stack<T> New{ Cut(last) };
	Push()->Paste(*elmnt);
	Add(New);
}

template<class T>
inline void Stack<T>::Create(const int& quantity)
{
	for (int i = 0; i < quantity; i++) 
		Fff(Push());
}

template<class T>
inline void Stack<T>::Clear()
{
	while (size > 0)
		this->Pop();
}

template<class T>
inline void Stack<T>::Renumb()
{
	Elem<T>* buffer = Bottom();
	int i = 1;
	while (buffer != nullptr) {
		buffer->Index(i);
		buffer = buffer->Next();
		i++;
	}
}

template<class T>
inline void Stack<T>::Save()
{
	if (Empty()) {
		cout << "Стек пуст." << endl;
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
		Elem<T>* buf = Bottom();
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
inline void Stack<T>::Open()
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
		*Push() >> (in);
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
inline bool Stack<T>::SavedCheck()
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
		Stack<T> New{ false };
		while (!(in.eof())) {
			if (New.Size() > Size()) return false;
			*New.Push() >> in;
			if (New.Top()->Info() != Find(New.Top()->Index())->Info()) return false;
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




template<class T>
inline void Stack<T>::operator=(const Stack<T>& other)
{
	try
	{
		Elem<T>* buffer = other.bottom;
		while (buffer != nullptr) {
			Push();
			Top()->Paste(*buffer);
			buffer = buffer->Next();
		}
		
	}
	catch (const std::exception&)
	{
		return;
	}
}


template<class T>
inline void Stack<T>::Fff(Elem<T>* elmnt)
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
