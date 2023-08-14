#include "RBTree_class.h"

SHAPKA RBPassport::shapka = SHAPKA {
		vector<string>{"#", "Фамилия", "Номер", "Возраст"},
		vector<int>{5, 15, 13, 9 }
};

ostream & RBPassport::operator<<(ostream & out)
{
	// TODO: вставьте здесь оператор return
	string txt[]{
	to_string(Index()),
	Surname(),
	to_string(Passnumb()),
	to_string(Age())
	};	
	

	int counter = -1,
		*col = new int[shapka.Sizes().size()];

	for (int i = 0; i< shapka.Sizes().size(); i++)
		col[i] = ColCount(txt[i].length(), shapka.Sizes()[i]);

	for (int x : shapka.Sizes())
		counter += x;

	out << "\n";

	for (int i = 0; i < shapka.Sizes().size(); i++)
		out << "|" << setw(col[i]) << txt[i] << setw(shapka.Sizes()[i] - col[i]);

	out << "|";
	out << "\n ";

	for (int i = 0; i < counter; i++)
		out << "-";

	delete[] col;

	
	return out;
}
istream & operator>>(istream & in, RBPassport & a)
{
	// TODO: вставьте здесь оператор return
	cout << "Введите индекс: "; Enter_check(a.index, 1000000000, 1);
	cout << "Введите фамилию: "; getline(cin, a.surname);
	cout << "Введите номер паспорта: "; Enter_check(a.passnumb, 1000000000, 1);
	cout << "Введите возраст: "; Enter_check(a.age, 1000000000, 1);
	return in;
}
ostream & operator<<(ostream & out, RBPassport & a)
{
	string txt[]{
	to_string(a.Index()),
	a.Surname(),
	to_string(a.Passnumb()),
	to_string(a.Age())
	};



	int counter = -1,
		*col = new int[a.shapka.Sizes().size()];

	for (int i = 0; i < a.shapka.Sizes().size(); i++)
		col[i] = a.ColCount(txt[i].length(), a.shapka.Sizes()[i]);

	for (int x : a.shapka.Sizes())
		counter += x;

	for (int i = 0; i < a.shapka.Sizes().size(); i++)
		out << "|" << setw(col[i]) << txt[i] << setw(a.shapka.Sizes()[i] - col[i]);

	out << "|";
	delete[] col;



	return out;
}
istream & RBPassport::operator>>(istream & in)
{
	string buf1;
	getline(in, buf1);
	int size = Shapka().Sizes().size();
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

	this->Index(stoi(buf0[0]));
	this->Surname(buf0[1]);
	this->Passnumb(stoi(buf0[2]));
	this->Age(stoi(buf0[3]));
	this->color = RED;
	getline(in, buf1);
	return in;
}

int RBPassport::ColCount(const int & a, const int & b)
{
	int c = a + (b - 1 - a) / 2;
	return c;
}

RBTree RBTree::KeyVarChange()
{
	
	RBTree a{};
	a.KeyVarSelect();
	if(!Empty())
		a = *this;
	return a;
}

void RBTree::KeyVarSelect()
{
	
	vector<string> str1 = Root()->Shapka().Cols();
	str1.insert(str1.begin(), "Выберите ключевое поле");
	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	while (true) {
		int m = m1.show();
		if (m == 0) { return; }
		else { keyvar = m; break;}
	}
}

RBTree & RBTree::operator=(const RBTree & other)
{
	// TODO: вставьте здесь оператор return
	if (other.size != 0 && other.root != nullptr)
	{
		FillWithTree(other.root);
	}
	else
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
	return *this;
}

RBTree& RBTree::FillWithTree(RBPassport* othertree) {
	if (othertree != nullptr) {
		RBPassport* buffer = new RBPassport{*othertree};
		Add(buffer);
		FillWithTree(othertree->Left());
		FillWithTree(othertree->Right());
	}
	return *this;
}

void RBTree::Add(RBPassport* elem)
{
	RBPassport
		* buffer = root, 
		* prev = nullptr;
	bool left = false;
	size++;
	if (root == nullptr) { root = elem; 
	root->C(BLACK);
	}
	else {				
		while (buffer != nullptr) {
			if (buffer != elem) {	
				prev = buffer;
				left = SmallerByKey(elem, buffer);
				if (left)
					buffer = buffer->Left();
				else
					buffer = buffer->Right();				
			}
			else {
			cout << "Добавление повторяющихся элементов исключено." << endl;
			return;
			}
		}
		if (left) prev->Left(elem); 
		else prev->Right(elem);
		elem->P(prev);
		if (elem->P()->C() == RED)
			InsertFixUp(elem);
	}
	
}

void RBTree::TypeIn()
{
	RBPassport* buffer = new RBPassport;
	cin >> *buffer;
	Add(buffer);
}

void RBTree::Clear()
{

	if (!RecursiveDelete(Root())) cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
	Root(nullptr);
}

bool RBTree::RecursiveDelete(RBPassport * elem)
{
	if (elem != nullptr) {
		
		if (!RecursiveDelete(elem->Left()))cout << " Левый пуст. " << endl;
		if (!RecursiveDelete(elem->Right()))cout << " Правый пуст. " << endl;
		elem->Left(nullptr);
		elem->Right(nullptr);
		delete elem;
		elem = nullptr;
		size--;
		return true;
	}
	else return false;
}

void RBTree::Show()
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return;
	}
	int counter = 0;	
	system("mode con cols=1000 lines=1000");
	RecursivePrint(Root(), counter, 0);
	cout << endl << endl << "Средний возраст: " << counter / (size * 1.0) << endl;
}

bool RBTree::RecursivePrint(RBPassport * elem, int &var, int l)
{
	int length = RBPassport::Shapka().Length()+ 1;
	if (elem != nullptr) {
		// 1 - фон, 2 - текст
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		BigColor c;
		string buf1 = "", buf2 = "", buf3 = "";
		for (int i = 0; i < l + length; i++) buf1 += " ";
		for (int i = 0; i < length; i++) buf2 += "-";
		for (int i = 0; i < l; i++)buf3 += " ";
		
		
		if (!RecursivePrint(elem->Right(), var, l + length)) {

			cout << buf1;

			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));

			cout << buf2 << endl;

			SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));

			cout << buf1; 

			
		    SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));

			
			cout  << setw((length + 16) / 2 + (length % 2)) << "Правый узел пуст" << setw(length - ((length + 16) / 2 + (length % 2)))<< " ";

			SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));

			cout << endl<< buf1;
			
			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));

			cout << buf2 << endl;

			SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));

			cout << endl;
		}
		
		cout << buf3;
		if (elem->C() == RED)
			SetConsoleTextAttribute(hConsole, (WORD)((c.Red.num << 4) | c.White.num));
		else
			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));
		cout << buf2;
		SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));


		cout<< endl << buf3;
		if (elem->C() == RED)
			SetConsoleTextAttribute(hConsole, (WORD)((c.Red.num << 4) | c.White.num));
		else
			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));
		cout << *elem;
		SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));


		cout << endl << buf3;
		if (elem->C() == RED)
			SetConsoleTextAttribute(hConsole, (WORD)((c.Red.num << 4) | c.White.num));
		else
			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));
		cout << buf2;

		SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));
		cout << endl;
		var += elem->Age();
		
		if (!RecursivePrint(elem->Left(), var, l + length)) {

			cout << buf1;
			 
			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));

			cout << buf2 << endl;

			SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));

			cout << buf1;


			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));


			cout << setw((length + 15) / 2 + (length % 2)) << "Левый узел пуст" << setw(length - ((length + 15) / 2 + (length % 2))) << " ";

			SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));

			cout << endl << buf1;

			SetConsoleTextAttribute(hConsole, (WORD)((c.Black.num << 4) | c.White.num));

			cout << buf2 << endl;

			SetConsoleTextAttribute(hConsole, (WORD)((c.White.num << 4) | c.Black.num));
		}
		
		return true;
	}
	else {
		return false;
	}
}

void RBTree::Order()
{
	
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return;
	}

	vector<string>
		str1
	{
	"Выберите порядок:",
	"1 - Прямой",
	"2 - Обратный",
	"3 - Симметричный"
	};

	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	while (true) {
		int m = m1.show();
		if (m == 0) { return; }
		else if (m == 1) { Root()->Shapka() << cout; RecursivePreOrder(Root()); break; }
		else if (m == 2) { Root()->Shapka() << cout; RecursivePstOrder(Root()); break; }
		else if (m == 3) { Root()->Shapka() << cout; RecursiveSymOrder(Root()); break; }
	}
	cout << endl;
	
}

void RBTree::RecursivePreOrder(RBPassport * elem)
{
	if (elem != nullptr) {
		*elem << cout;
		RecursivePreOrder(elem->Left());
		RecursivePreOrder(elem->Right());
	}
}

void RBTree::RecursivePstOrder(RBPassport * elem)
{
	if (elem != nullptr) {
		RecursivePstOrder(elem->Left());
		RecursivePstOrder(elem->Right());
		*elem << cout;
	}
}

void RBTree::RecursiveSymOrder(RBPassport * elem)
{
	if (elem != nullptr) {
		RecursiveSymOrder(elem->Left());
		*elem << cout;
		RecursiveSymOrder(elem->Right());
	}
}

void RBTree::Delete()
{
	
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return;
	}
	string buffer1 = "";
	int buffer2 = 0;
	RBPassport* buffer3 = nullptr;
	vector<string>
		str1
	{
	"Выберите метод удаления:",
	"1 - Левое поддерево",
	"2 - Правое поддерево",
	"3 - Элемент"
	};

	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	cout << "Введите ключ для удаления искомого элемента: ";
	
	if (keyvar == 2) {
		cout << " (строка) ";
		getline(cin, buffer1);
		buffer3 = Find(buffer1, Root());
	}
	else{
		cout << " (число) ";
		Enter_check(buffer2, 1000000000, -1);
		buffer3 = Find(buffer2, Root());
	}
	while (true) {
		int m = m1.show();
		if (m == 0) { return; }
		else if (m == 1) { DeleteLeft(buffer3); break; }
		else if (m == 2) { DeleteRight(buffer3); break; }
		else if (m == 3) { DeleteElem(buffer3); break; }
	}
	
}

void RBTree::DeleteLeft(RBPassport * elem)
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return;
	}
	if (elem != nullptr) {
		if (!RecursiveDelete(elem->Left()))cout << " Левое звено пустое. " << endl;
		elem->Left(nullptr);
	}
	
}

void RBTree::DeleteRight(RBPassport * elem)
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return;
	}
	if (!RecursiveDelete(elem->Right()))cout << " Правое звено пустое. " << endl;
	elem->Right(nullptr);
}

void RBTree::DeleteElem(RBPassport * elem)
{
	RBPassport* elem1 = nullptr, *elem2 = nullptr, *elem3 = nullptr;
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return;
	}
	if (elem == nullptr) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Пустой указатель. " << endl;
		return;
	}
	if (!Leaf(elem)) {
		// если только слева
		if (elem->Right() == nullptr) {
			elem2 = elem->Left();
		}
		// если только справа
		else if (elem->Left() == nullptr) {
			elem2 = elem->Right();
		}
		// если и слева и справа
		else if (NotLeaf(elem)) {		
			elem1 = FindPreLeft(elem->Right());
			// если в предыдущем это левый
			if (Leaf(elem1->Left())) {
				elem2 = elem1->Left();
				elem1->Left(nullptr);
			}
			// если в предыдущем это правый
			else if (Leaf(elem1->Right())) {
				elem2 = elem1->Right();
				elem1->Right(nullptr);
			}
			if (elem2 != nullptr) {
				elem2->Left(elem->Left());
				elem2->Right(elem->Right());
			}			
		}	
	}
	// удаляемый это корень
	if (elem == Root()) {
		root = elem2;
		elem2->P(nullptr);
	}
	// удаляемый не корень
	else {
		elem1 = RetParent(elem);
		if (elem == elem1->Right())elem1->Right(elem2);
		else if (elem == elem1->Left())elem1->Left(elem2);
		if(elem2!= nullptr)
		elem2->P(elem1);
	}
	
	try {
		if (elem2 == nullptr)
			elem2 = elem1;
		if(elem->C() == BLACK)
		DeleteFixUp(elem2);
		delete elem;
		size--;
		/*if (root->Left() == nullptr || root->Right() == nullptr) {
			Balance();
		}*/
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	

}

bool RBTree::SmallerByKey(RBPassport * a, RBPassport * b)
{
	bool smaller = true;
	if (a != b) {
		switch (keyvar) {
		case 1:
			smaller = a->SmallerI(b);
			break;
		case 2:
			smaller = a->SmallerS(b);
			break;
		case 3:
			smaller = a->SmallerN(b);
			break;
		case 4:
			smaller = a->SmallerA(b);
			break;
		}
	}
	
	return smaller;
}

RBPassport * RBTree::FindPreLeft(RBPassport * elem)
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return nullptr;
	}
	if (!Leaf(elem)){

		if (elem->Left()!= nullptr)FindPreLeft(elem->Left());
		else if (elem->Right() != nullptr)FindPreLeft(elem->Right());
	}
	else return elem->P();
}

RBPassport* RBTree::RetParent( RBPassport* current)

{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return nullptr;
	}
	if (current != nullptr && current != Root()) {
		return current->P();
	}
	else return nullptr;
	
}

void RBTree::Open()
{
	KeyVarSelect();
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
		if (m == 1) { SetFpath("data.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { SetFpath(); break; }
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
			RBPassport* buffer = new RBPassport{};
			*buffer >> (in);
			Add(buffer);
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

void RBTree::Save()
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
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
		if (m == 1) { SetFpath("data.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { SetFpath(); break; }
		else if (m == 0) { return; }
	}
	try
	{
		ofstream out;
		out.open(Fpath);
		Root()->Shapka() << out;
		RecursiveOutPass(out, Root());
	    out.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка сохранения таблицы!" << endl;
		return;
	}
	cout << "Данные сохранены в: " << Fpath << endl;

}

ostream & RBTree::RecursiveOutPass(ostream & out, RBPassport * elem)
{
	// TODO: вставьте здесь оператор return
	if (elem != nullptr) {
		
		RecursiveOutPass(out, elem->Left());
		*elem << out;
		RecursiveOutPass(out, elem->Right());
	}
	return out;
}

void RBTree::SaveTree()
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
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
		if (m == 1) { SetTpath("Tree.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { SetTpath(); break; }
		else if (m == 0) { return; }
	}
	try
	{
		ofstream out;
		out.open(Tpath);
		RecursiveOut(out, Root(), 0);
		out.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка сохранения таблицы!" << endl;
		return;
	}
	cout << "Данные сохранены в: " << Tpath << endl;
}

ostream & RBTree::RecursiveOut(ostream & out, RBPassport * elem, int l)
{
	// TODO: вставьте здесь оператор return
	
	if (elem != nullptr) {
		int length = RBPassport::Shapka().Length() + 1;
		string line1 = "", line2 = "", line3 = "";
		for (int i = 0; i < l; i++) line1 += " ";
		for (int i = 0; i < length; i++) line2 += "-";
		for (int i = 0; i < length; i++) line3 += " ";

		if (elem->Right()== nullptr) {
			out << line1 + line3 + line2 << endl;
			
			out << line1 + line3 << setw((length + 16) / 2 + (length % 2)) << "Правый узел пуст\n";
			
			out << line1 + line3 + line2 << endl;
		}
		else RecursiveOut(out, elem->Right(), l + length);

		out << line1 + line2 << endl;
		out << line1 << *elem << endl;
		out << line1 + line2 << endl;

		if (elem->Left() == nullptr) {
			out << line1 + line3 + line2 << endl;

			out << line1 + line3 << setw((length + 15) / 2 + (length % 2)) << "Левый узел пуст\n";

			out << line1 + line3 + line2 << endl;
		}
		else RecursiveOut(out, elem->Left(), l + length);
	}
	return out;
}

RBPassport * RBTree::Find(const int & val, RBPassport* elem)
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return nullptr;
	}

	if (elem != nullptr) {
		switch (keyvar) {
		case 1:
			if (elem->Index() == val) {
				return elem;
			}
			else if (val < elem->Index())
			{
				if (elem->Left() != nullptr)
					Find(val, elem->Left());
			}

			else if (val > elem->Index())
			{
				if (elem->Right() != nullptr)
					Find(val, elem->Right());
			}
			break;
		case 3:
			if (elem->Passnumb() == val) {
				return elem;
			}
			else if (val < elem->Passnumb())
			{
				if (elem->Left() != nullptr)
					Find(val, elem->Left());
			}

			else if (val > elem->Passnumb())
			{
				if (elem->Right() != nullptr)
					Find(val, elem->Right());
			}
			break;
		case 4:
			if (elem->Age() == val) {
				return elem;
			}
			else if (val < elem->Age())
			{
				if (elem->Left() != nullptr)
					Find(val, elem->Left());
			}

			else if (val > elem->Age())
			{
				if (elem->Right() != nullptr)
					Find(val, elem->Right());
			}
			break;
		}
				
			
	}
}

RBPassport * RBTree::Find(const string & val, RBPassport * elem)
{
	if (Empty()) {
		cout << "Сообщение от " << __FUNCTION__ << " -->  Дерево пустое. " << endl;
		return nullptr;
	}

	if (elem != nullptr) {
		if (elem->Surname() == val) {
			return elem;
		}

		else if (val < elem->Surname())
		{
			if (elem->Left() != nullptr)
				Find(val, elem->Left());
		}

		else if (val > elem->Surname())
		{
			if (elem->Right() != nullptr)
				Find(val, elem->Right());
		}

	}
}


RBPassport * RBTree::Rotate(RBPassport * elem, bool LeftRight)
{
	// left
	
	RBPassport* q = elem, *p = LeftRight ? q->Right() : q->Left();

	
	string buf1 = __FUNCTION__ ,buf = "Ошибка " + buf1 + " .";
	if (elem != nullptr) {
		if (p != nullptr) {
			// работа с предками
			p->P(q->P());
			q->P(p);
			if (p->P() != nullptr) {
				if (p->P()->Left() == q)
					p->P()->Left(p);
				else
					p->P()->Right(p);
			}
			else root = p;
			// работа с детьми
			
			if (LeftRight)
				q->Right(p->Left());
			else
				q->Left(p->Right());

			if (LeftRight && q->Right() != nullptr)
				q->Right()->P(q);
			else if (q->Left() != nullptr)
				q->Left()->P(q);
			
			if (LeftRight)
				p->Left(q);
			else
				p->Right(q);
		}		
	}
	else throw buf;
	return p;
}


void RBTree::InsertFixUp(RBPassport * elem)
{
	string buf1 = __FUNCTION__, buf2 = "Ошибка " + buf1 + " .";
	RBPassport* x = nullptr, *y = nullptr;
	bool LeftRight = false;
	if (elem != nullptr && elem->P()!= nullptr) {
		x = elem;
		while (x!= nullptr && x != Root() && x->P()->C() == RED )
		{ 			    
			LeftRight = (x->P() == x->P()->P()->Left());
			y = LeftRight? x->P()->P()->Right(): y = x->P()->P()->Left();
			if (y->C() == RED) {
				x->P()->C(BLACK);
				y->C(BLACK);
				x->P()->P()->C(RED);
				x = x->P()->P();
			}
			else {
				if (LeftRight? x == x->P()->Right(): x == x->P()->Left()) {
					x = x->P();
					Rotate(x, LeftRight);
				}
				x->P()->C(BLACK);
				x->P()->P()->C(RED);
				Rotate(x->P()->P(), !LeftRight);
			}
			
		}
		Root()->C(BLACK);
	}
	else throw buf2;

}

void RBTree::DeleteFixUp(RBPassport * elem)
{
	RBPassport* n = elem, * b = nullptr;
	bool LeftRight = false;
	while (n != Root() && n->C() == BLACK) {
		LeftRight = n == n->P()->Left();
		b = LeftRight? n->P()->Right(): n->P()->Left();
		if (b->C() == RED) {
			b->C(BLACK);
			n->P()->C(RED);
			Rotate(n->P(), LeftRight );
			b = LeftRight ? b->P()->Right(): b->P()->Left();
		}
		if (b->Left()->C() == BLACK && b->Right()->C() == BLACK) {
			b->C(RED);
			n = n->P();
		}
		else {
			if ((LeftRight ? b->Right()->C(): b->Left()->C()) == BLACK) {
				LeftRight ? b->Left()->C(BLACK): b->Right()->C(BLACK);
				b->C(RED);
				Rotate(b, !LeftRight);
				b = LeftRight ? n->P()->Right(): n->P()->Left();
			}
			b->C(n->P()->C());
			n->P()->C(BLACK);
			LeftRight ? b->Right()->C(BLACK): b->Left()->C(BLACK);
			Rotate(n->P(), LeftRight);
			n = root;
		}	
	
	}
	n->C(BLACK);
}

void RBTree::CopyPointers(RBPassport* elem, vector<RBPassport*>& vec, int& i)
{
	if (elem != nullptr) {
		i++;
		vec[i] = elem;
		
		CopyPointers(elem->Left(), vec, i);
		
		CopyPointers(elem->Right(), vec, i);
		
	}
}

void RBTree::Balance()
{
	vector<RBPassport*> vec(size);
	int i = -1;
	CopyPointers(root, vec, i);
	for (RBPassport*& elem : vec) {
		elem->P(nullptr);
		elem->Left(nullptr);
		elem->Right(nullptr);
		elem->C(RED);
	}
	root = nullptr;
	size = 0;
	for (RBPassport* elem : vec) {
		Add(elem);
	}
}

