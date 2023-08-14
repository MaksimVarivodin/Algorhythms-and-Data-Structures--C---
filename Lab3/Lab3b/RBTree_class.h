#pragma once
#include "Header.h"
enum Color {
	RED,
	BLACK
};
class RBPassport {

	int index;
	string surname;
	int passnumb;
	int age;
	Color color;
	RBPassport* left;
	RBPassport* right;
	RBPassport* parent;
	
	static SHAPKA shapka;
public:
	RBPassport()	
	{
		index = 0;
		surname = "";
		passnumb = 0;
		age = 0;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = RED;
	};
	RBPassport(const RBPassport & other) :RBPassport{}
	{
		operator=(other);
	};

	RBPassport& operator= (const RBPassport & other) {
		this->index = other.index;
		this->surname = other.surname;
		this->passnumb = other.passnumb;
		this->age = other.age;
		this->left = other.left;
		this->right = other.right;
		this->parent = other.parent;
		this->color = other.color;
		return *this;
	};

	int Index()       { return index; };
	string Surname()  { return surname; };
	int Passnumb()    { return passnumb; };
	int Age()         { return age; };
	RBPassport* Left()  { 
		if (this == nullptr)
			return nullptr;
		return left; };
	RBPassport* Right() { 
		if (this == nullptr)
			return nullptr;
		return right; };
	RBPassport* P() { 
		if (this == nullptr)
			return nullptr;
		return parent; };
	Color C() { 
		if (this == nullptr)
			return BLACK;
		return color; };

	void Index(const int& Index0)         { index = Index0; };
	void Surname(const string& Surname0)  { surname = Surname0; };
	void Passnumb(const int& Passnumb0)   { passnumb = Passnumb0; };
	void Age(const int & Age0)            { age = Age0; };
	void Left(RBPassport * Left0)         { left = Left0; };
	void Right(RBPassport * Right0)       { right = Right0; };
	void P(RBPassport * par0)        { parent = par0; };
	void C(Color a)                  { color = a; };
	template<typename t1, typename t2>
	friend  void Enter_check(t1& a, const t2& max, const t2& min);

	bool operator== (RBPassport* other) {
		return this->index == other->index && this->surname == other->surname && this->passnumb == other->passnumb && this->age == other->age ;
	};

	bool LargerI(RBPassport* other) { return this->index > other->index; };
	bool LargerS(RBPassport* other) { return this->surname > other->surname; };
	bool LargerN(RBPassport* other) { return this->passnumb > other->passnumb; };
	bool LargerA(RBPassport* other) { return this->age > other->age; };

	bool SmallerI(RBPassport* other) { return this->index < other->index; };
	bool SmallerS(RBPassport* other) { return this->surname < other->surname; };
	bool SmallerN(RBPassport* other) { return this->passnumb < other->passnumb; };
	bool SmallerA(RBPassport* other) { return this->age < other->age; };

	friend istream& operator>> (istream& in, RBPassport& a);
	ostream& operator << (ostream& out);

	friend ostream& operator << (ostream& out, RBPassport & a);
	istream& operator >> (istream& in);

	int ColCount(const int& a, const int& b);

	static SHAPKA Shapka() { return shapka; };
};


class RBTree {
	RBPassport* root;
	int size;
	int power;
	string Fpath;
	string Tpath;
	int keyvar;

	void Root(RBPassport* Root) { root = Root; };
	bool Empty() { return size == 0 && root == nullptr; };
	int Size() { return size; };
	int Power() { return power; };

	/* метод проверки пути к таблицы */
	bool CheckPath(const string & a) {
		return a == "" || a.find(".txt") == string::npos;
	};

	void SetFpath(const string & path = "") {
		Fpath = path;
		bool check = CheckPath(Fpath);
		while (check) {
			cout << "Введите путь: ";
			getline(cin, Fpath);
			if (CheckPath(Fpath)) {
				check = true;
				cout << "Путь был введен неправильно" << endl;
			}
			else check = false;
		}
	};
	void SetTpath(const string & path = "") {
		Tpath = path;
		bool check = CheckPath(Tpath);
		while (check) {
			cout << "Введите путь: ";
			getline(cin, Tpath);
			if (CheckPath(Tpath)) {
				check = true;
				cout << "Путь был введен неправильно" << endl;
			}
			else check = false;
		}
	};
public:
	RBTree()
	{
		cout << "Сработал конструктор " << __FUNCTION__ << " --> По умолчанию. " << endl;
		system("pause");
		root = nullptr;
		size = 0;
		power = 0;
		Fpath = "";
		keyvar = 0;
	};
	RBTree(const bool open) : RBTree{} {
		cout << "Сработал конструктор " << __FUNCTION__ << " --> Открытия таблицы. " << endl;
		system("pause");
		KeyVarSelect();
		if (open) {
			Open();
		}
	};
	RBTree(const RBTree& other) :RBTree{} {
		cout << "Сработал конструктор " << __FUNCTION__ << " --> Копирования. " << endl;
		system("pause");

		keyvar = other.keyvar;
		operator=(other);
	};
	~RBTree()
	{
		Clear();
	};
	RBTree KeyVarChange();
	RBPassport * Root() { return root; };
	void KeyVarSelect();
	RBTree& operator= (const RBTree & other);
	RBTree & FillWithTree(RBPassport * othertree);
	void Add(RBPassport* elem);
	void TypeIn();
	void Clear();
	bool RecursiveDelete(RBPassport* elem);
	void Show();
	bool RecursivePrint(RBPassport* elem, int &var, int l);
	void Order();
	void RecursivePreOrder(RBPassport* elem);
	void RecursivePstOrder(RBPassport* elem);
	void RecursiveSymOrder(RBPassport* elem);
	void Delete();
	void DeleteLeft(RBPassport* elem);
	void DeleteRight(RBPassport* elem);
	void DeleteElem(RBPassport* elem);
	bool SmallerByKey(RBPassport* a, RBPassport* b);
	RBPassport* FindPreLeft(RBPassport* elem);
	RBPassport* RetParent(RBPassport* current);
	void Open();
	void Save();
	ostream& RecursiveOutPass(ostream& out, RBPassport* elem);
	void SaveTree();
	ostream& RecursiveOut(ostream& out, RBPassport* elem, int l);
	bool Leaf(RBPassport* elem) { return elem->Right() == nullptr && elem->Left()== nullptr; };
	bool NotLeaf(RBPassport* elem) { return elem->Right() != nullptr && elem->Left() != nullptr; };
	bool Inheritor(RBPassport* elem1, RBPassport* elem2) { return elem1->Left() == elem2 || elem1->Right() == elem2; };
	RBPassport* Find(const int & val, RBPassport* elem);
	RBPassport* Find(const string & val, RBPassport* elem);
	RBPassport * Rotate(RBPassport * elem, bool LeftRight);

	void InsertFixUp(RBPassport* elem);
	void DeleteFixUp(RBPassport* elem);
	template<typename t1, typename t2>
	friend  void Enter_check(t1& a, const t2& max, const t2& min);
	void CopyPointers(RBPassport* elem, vector<RBPassport*>& vec, int& i);
	void Balance();

};