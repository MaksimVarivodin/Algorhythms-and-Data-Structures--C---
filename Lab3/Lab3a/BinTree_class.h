#pragma once
#include "Header.h"
class RBPassport {

	int index;
	string surname;
	int passnumb;
	int age;
	RBPassport* left;
	RBPassport* right;
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
		this->left = this->left;
		this->right = this->right;
		return *this;
	};

	int Index()       { return index; };
	string Surname()  { return surname; };
	int Passnumb()    { return passnumb; };
	int Age()         { return age; };
	RBPassport* Left()  { return left; };
	RBPassport* Right() { return right; };

	void Index(const int& Index0)        { index = Index0; };
	void Surname(const string& Surname0) { surname = Surname0; };
	void  Passnumb(const int& Passnumb0) { passnumb = Passnumb0; };
	void  Age(const int & Age0)          { age = Age0; };
	void  Left(RBPassport * Left0)         { left = Left0; };
	void  Right(RBPassport * Right0)       { right = Right0; };

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

class Node {
	Node* Parent;
	Node* Left;
	Node* Right;
	int Data;

public:
	Node() :Parent(nullptr), Left(nullptr), Right(nullptr), Data(0), smaller(&Node::operator<), bigger(&Node::operator>) {};
	Node(const int& d) :Node() { Data = d; };
	Node* P() { return Parent; };
	Node* L() { return Left; };
	Node* R() { return Right; };
	int   D() { return Data; };
	void P(Node* p0) { Parent = p0; };
	void L(Node* l0) { Left = l0; };
	void R(Node* r0) { Right = r0; };
	void D(int   d0) { Data = d0; };

	bool operator<(Node* a);
	bool operator>(Node* a);
	bool (Node::* smaller)(Node* a);// a < b
	bool (Node::* bigger)(Node* a);// a > b
	bool S(Node* a) { return (this->*smaller)(a); };
	bool B(Node* a) { return (this->*bigger)(a); };
	bool Leaf() { return L() == nullptr && R() == nullptr; };
	bool NotLeaf() { return L() != nullptr && R() != nullptr; };
	bool HalfLeaf() {
		if (this == nullptr)return false;
		return !Leaf() && !NotLeaf();
	}
	bool Inheritor(Node* elem1) { return this->L() == elem1 || this->R() == elem1; };
	Node* CopyPointers(Node* elem) {
		if (elem != nullptr && this != nullptr) {
			this->P(elem->P());
			this->L(elem->L());
			this->R(elem->R());
		}

		return this;
	};
	Node* ClearPointers() {
		if (this != nullptr) {
			Node a;
			Node* ref = &a;
			CopyPointers(ref);
		}
		return this;
	};
	void Print(int l, int i) {
		TABLE(SHAPKA(vector<int>{l}, i), vector<vector<string>>{
			vector<string>{to_string(D())}
		}, false, false) << cout;
	};
	void PrintEmpty(int l, int i) {
		TABLE(SHAPKA(vector<int>{l}, i),
			vector<vector<string>>{
			vector<string>{"пусто"}
		},
			false, false) << cout;
	};
};
class RBTree {
	RBPassport* root;
	Node* root2;
	int size2;
	int size;
	int power;
	string Fpath;
	string Tpath;
	int keyvar;

	void Root(RBPassport* Root) { root = Root; };
	void Root2(Node* Root) { root2 = Root; };
	bool Empty() { return size == 0 && root == nullptr; };
	bool Empty2() { return size2 == 0 && root2 == nullptr; };
	int Size() { return size; };
	int Size2() { return size2; };

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
	friend void Node::L(Node*);
	friend void Node::R(Node*);
	void (*RLset)(Node*);
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
		size2 = 0;
		root2 = nullptr;
		vector<int> buffer{ 4, 2, 6, 1, 3, 5, 7 };
		for (int x : buffer) {
			Add2(new Node(x));
		}
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
		Clear2();
	};
	RBTree KeyVarChange();
	RBPassport * Root() { return root; };
	Node* Root2() { return root2; };

	void KeyVarSelect();
	RBTree& operator= (const RBTree & other);
	RBTree & FillWithTree(RBPassport * othertree);
	void Add(RBPassport* elem);
	void Add2(Node* elem);
	void TypeIn();
	void Clear();
	void Clear2();
	bool RecursiveDelete(RBPassport* elem);
	bool RecursiveDelete2(Node* elem);

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
	RBPassport* SearchRoot(RBPassport* find, RBPassport* current);
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
	RBPassport* RotateRight(RBPassport* elem);
	RBPassport* RotateLeft(RBPassport* elem);
	template<typename t1, typename t2>
	friend  void Enter_check(t1& a, const t2& max, const t2& min);




	void SetCursorPrint(int x, int y, string info);
	void CursorPrint(int x, int y, int w, int h, string info);
	void GorizontalOut(Node* elem, int x, int y, int w, int h);
	int RecursiveGorizontal(Node* elem, int x, int y, int& maxY, int w, int h);
	void Print();

};