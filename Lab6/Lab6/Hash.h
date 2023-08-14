
#include "Header.h"
struct HashLine {
	int key = 0;
	int data = 0;
	bool changed = false;
	static int hash(int, int);
	static void CreateTable(vector<HashLine>& table, vector<int> keys);
	static void Add(vector<HashLine>& table, int x, int y);
	static void DeleteTable(vector<HashLine>& table);
	static void DeleteLine(vector<HashLine>& table, int ixDelete);
	static bool CheckNextKey(vector<int>keys, int k);
	static bool Empty(HashLine l) { return !l.changed; };
	static void Print(vector<HashLine> table);
	static bool Search(vector<HashLine>, int k, int& f);
};
struct ChainLine {
	int key = 0;
	int data = 0;
	ChainLine *n = nullptr;
	static int hash(int, int);
	static ChainLine* Dat(int d, int y) {
		ChainLine* da = new ChainLine;
		da->key = d;
		da->data = y;
		return  da;
	}
	static void Add(vector<ChainLine*>& chTable,int x, int y);
	static void DisplayChain(ChainLine* ch, int& i);
	static void DisplayTable(vector<ChainLine*> chTable);
	static void TraceChain(ChainLine* ch);
	static void TraceTable(vector<ChainLine*> chTable);
	static void DeleteChain(ChainLine*& ch);
	static void DeleteElem(vector<ChainLine*>& chTable,int k);
	static void DeleteTable(vector<ChainLine*>&chTable);
	static bool Search(vector<ChainLine*>, int k, int& f);
};
struct LinOpLine {
	int key = 0;
	int data = 0;
	bool changed = false;
	static int hash(int, int, int);
	static bool Empty(LinOpLine l) { return !l.changed; };
	static void Add(vector<LinOpLine>&lotable, int k, int d);
	static void DeleteLine(vector<LinOpLine>& lotable, int k);
	static void Print(vector<LinOpLine> lotable);
	static bool Search(vector<LinOpLine>, int k, int & f);
};
struct KvOpLine {
	int key = 0;
	int data = 0;
	bool changed = false;
	static int hash(int, int, int);
	static bool Empty(KvOpLine l) { return !l.changed; };
	static void Add(vector<KvOpLine>&lotable, int k, int d);
	static void DeleteLine(vector<KvOpLine>& lotable, int k);
	static void Print(vector<KvOpLine> lotable);
	static bool Search(vector<KvOpLine>, int k, int& f);
};
struct DvHshLine {
	int key = 0;
	int data = 0;
	bool changed = false;
	static int hash(int, int, int);
	static bool Empty(DvHshLine l) { return !l.changed; };
	static void Add(vector<DvHshLine>&lotable, int k, int d);
	static void DeleteLine(vector<DvHshLine>& lotable, int k);
	static void Print(vector<DvHshLine> lotable);
	static bool Search(vector<DvHshLine>, int k, int& f);
};

