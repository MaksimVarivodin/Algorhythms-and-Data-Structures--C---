#include "Hash.h"

int HashLine::hash(int m, int k)
{
	double A = (pow(5.0, 0.5) - 1) / 2.0;
	double buf = (((k*1.0)* A) / 1);
	int buf2 = (((k*1.0)* A) / 1);
	return  m * (buf - buf2);
}

void HashLine::CreateTable(vector<HashLine>& table, vector<int>keys)
{
	int lines = 0;
	int k = -1;
	
	
	
	while (CheckNextKey(keys,k)) {
		try {
			if (table.size()==0)
				throw string("Error");
			table[lines];
		}
		catch (const string & a) {
			vector<HashLine> new_arr(20, HashLine());
			table = new_arr;			
		}
		k++;
		int iterator = 1;
		vector<int> info(table.size(), 0);
		for (int &x : info)
		{
			x = iterator;
			iterator++;
		}
		int hashcode = hash(table.size(), keys[k]);
		while (!Empty(table[hashcode])) {
			hashcode = (hashcode + 1) % table.size();
		}
		table[hashcode].key = keys[k];
		table[hashcode].data = info[hashcode];
		table[hashcode].changed = true;
		lines++;
	}
}

void HashLine::Add(vector<HashLine>& table, int x, int y)
{
	int h = hash(table.size(), x);
	while (h < table.size() && !Empty(table[h])) {
		h++;
	}
	if (h >= table.size())table.resize(h+1);
	table[h].key = x;
	table[h].data = y;
	table[h].changed = true;
}

void HashLine::DeleteTable(vector<HashLine>& table)
{
	int ind = 0;
	while (true) {
		int ind2 = ind;
		while (ind < table.size() && Empty(table[ind]))
			ind++;			
		
		if (ind >= table.size()) break;
		DeleteLine(table, ind);
	}
	cout << "Clean hash-table" << endl;
	Print(table);
	while (ind < table.size() && Empty(table[ind]) ) {
		ind++;
	}
	if (ind != (table.size()))
		DeleteTable(table);
	else
		table.resize(0);
}

void HashLine::DeleteLine(vector<HashLine>& table, int ixDelete)
{
	int h = hash(table.size(), ixDelete);
	while (h < table.size() && table[h].key!=ixDelete) {
		h++;
	}
	table[h].changed = false;
}

bool HashLine::CheckNextKey(vector<int>keys, int k)
{
	if(k+ 1< keys.size())
		return true;
	return false;
}

void HashLine::Print(vector<HashLine> table)
{
	cout << "#\tkey\tdata\tN\\E"<< endl;
	for (int i = 0; i < table.size(); i++)
		cout << i << "\t" << table[i].key << "\t" << table[i].data << "\t" << table[i].changed << endl;
	cout << endl;
}

bool HashLine::Search(vector<HashLine>table, int k, int & f)
{
	int h = hash(table.size(),k);
	while (h < table.size() && !Empty(table[h])) {
		if (table[h].key = k) {
			f = h;
			return true;
		}
		h = (h + 1) % table.size();
	}
	f = -1;
	return false;
}

int ChainLine::hash(int m, int k)
{
	return k % m;
}

void ChainLine::Add(vector<ChainLine*>& chTable, int x, int y)
{
	int h = hash(chTable.size(), x);
	if (chTable[h] == nullptr)
		chTable[h] = Dat(x, y);
	else {
		ChainLine* temp = chTable[h];
		while (temp->n != nullptr)
			temp = temp->n;
		temp->n = Dat(x, y);
	}
}

void ChainLine::DisplayChain(ChainLine * ch, int& i)
{
	ChainLine* temp = ch;
	while (temp != nullptr)
	{
		cout << i << "\t" << temp->key << "\t" << temp->data << endl;
		temp = temp->n;
		i++;
	}
}

void ChainLine::DisplayTable(vector<ChainLine*> chTable)
{
	int iter = 0;
	cout <<"#\tKey\tdata"<< endl;
	for (int i = 0; i < chTable.size(); i++) {
		DisplayChain(chTable[i], iter);
	}
	cout << endl;
}

void ChainLine::TraceChain(ChainLine * ch)
{
	ChainLine* temp = ch;
	while (temp != nullptr)
	{
		cout << " -> " << temp->key << "{" << temp->data<< "}";
		temp = temp->n;	
	}
}

void ChainLine::TraceTable(vector<ChainLine*> chTable)
{
	cout << "#\tPointers" << endl;
	for (int i = 0; i < chTable.size(); i++) {
		cout << i<< "\t";
		if (chTable[i] == nullptr) cout << " -> nullptr";
		TraceChain(chTable[i]);
		cout << endl;
	}
	cout << endl;
}

void ChainLine::DeleteChain(ChainLine *& ch)
{
	ChainLine* buf = ch,* buf2 = nullptr;
	while (buf2 != nullptr) {
		buf2 = buf->n;
		delete buf;
		buf = buf2;
	}
	ch = nullptr;
}

void ChainLine::DeleteElem(vector<ChainLine*>& chTable, int k)
{
	ChainLine* buf = nullptr, *buf2 = nullptr;
	int i = 0;
	for (; i < chTable.size(); i++) {
		buf = chTable[i];
		if(buf!= nullptr)
		buf2 = buf->n;
		else continue;
		while (buf2 != nullptr){			
			if (buf->key == k)break;			
			buf = buf2;
			buf2 = buf->n;
	    }
		if (buf->key == k)break;
	}
	ChainLine* buf3 = chTable[i];
	while (buf3->key!= k && buf3->n != buf) {
		buf3 = buf3->n;
	}
	buf3->n = buf2;
	if (buf3 == buf)chTable[i] = nullptr;
	delete buf;

}

void ChainLine::DeleteTable(vector<ChainLine*>& chTable)
{
	for (int i = 0; i < chTable.size(); i++)
		DeleteChain(chTable[i]);
	TraceTable(chTable);
	chTable.resize(0);
}

bool ChainLine::Search(vector<ChainLine*> chTable, int k, int & f)
{
	ChainLine* buf = nullptr, *buf2 = nullptr;
	int i = 0;
	for (; i < chTable.size(); i++) {
		buf = chTable[i];
		while (buf2 != nullptr) {
			buf2 = buf->n;
			if (buf->key == k)break;
			buf = buf2;
		}
		if (buf2 != nullptr)break;
	}
	if (buf2 == nullptr)return false;
	else { 
		TraceChain(buf);
		return true;
	}
}

int LinOpLine::hash(int s, int k, int i)
{
	return ((k%s)+ i)%s;
}

void LinOpLine::Add(vector<LinOpLine>& lotable, int k, int d)
{
	int i =0,  h = hash(lotable.size(), k, i);
	while (h< lotable.size()&& !Empty(lotable[h])) {
		i++;
		h = hash(lotable.size(), k, i);
	}
	if (h == lotable.size())lotable.resize(lotable.size()+ 1);
	lotable[h].changed = true;
	lotable[h].key = k;
	lotable[h].data = d;

}

void LinOpLine::DeleteLine(vector<LinOpLine>& lotable, int k)
{
	int i = 0, h = hash(lotable.size(), k, i);
	while (h < lotable.size() && lotable[h].key != k) {
		i++;
		h = hash(lotable.size(), k, i);
	}
	lotable[h].changed = false;
	
}

void LinOpLine::Print(vector<LinOpLine> lotable)
{
	cout << "#\tkey\tdata\tN\\E" << endl;
	for (int i = 0; i < lotable.size(); i++)
		cout << i << "\t" << lotable[i].key << "\t" << lotable[i].data << "\t" << lotable[i].changed << endl;
	cout << endl;
}

bool LinOpLine::Search(vector<LinOpLine> table, int k, int & f)
{
	int i = 0;
	int h = hash(table.size(), k, i);
	while (h < table.size() && !Empty(table[h])) {
		if (table[h].key == k) {
			f = h;
			return true;
		}
		h = (h + 1) % table.size();
	}
	f = -1;
	return false;
}

int KvOpLine::hash(int s, int k, int i)
{
	return ((k%s) + i+ 3* i*i) % s;
}

void KvOpLine::Add(vector<KvOpLine>& lotable, int k, int d)
{
	int i = 0, h = hash(lotable.size(), k, i);
	while (h < lotable.size() && !Empty(lotable[h])) {
		i++;
		h = hash(lotable.size(), k, i);
	}
	if (h >= lotable.size())lotable.resize(h + 1);
	lotable[h].changed = true;
	lotable[h].key = k;
	lotable[h].data = d;
}

void KvOpLine::DeleteLine(vector<KvOpLine>& lotable, int k)
{
	int i = 0, h = hash(lotable.size(), k, i);
	while (h < lotable.size() && lotable[h].key != k) {
		i++;
		h = hash(lotable.size(), k, i);
	}
	lotable[h].changed = false;
}

void KvOpLine::Print(vector<KvOpLine> lotable)
{
	cout << "#\tkey\tdata\tN\\E" << endl;
	for (int i = 0; i < lotable.size(); i++)
		cout << i << "\t" << lotable[i].key << "\t" << lotable[i].data << "\t" << lotable[i].changed << endl;
	cout << endl;
}

bool KvOpLine::Search(vector<KvOpLine> lotable, int k, int & f)
{
	
	int i = 0, h = hash(lotable.size(), k, i);	
	while (h < lotable.size()) {
		if (lotable[h].key == k) {
			f = h;
			return true;
		}
		i++;
		h = hash(lotable.size(), k, i);
	}
	f = -1;
	return false;
}

int DvHshLine::hash(int s, int k, int i)
{
	return ((k%s) + i*(1+ (k% (s -1)))) % s;
}

void DvHshLine::Add(vector<DvHshLine>& lotable, int k, int d)
{
	int i = 0, h = hash(lotable.size(), k, i);
	while (h < lotable.size() && !Empty(lotable[h])) {
		i++;
		h = hash(lotable.size(), k, i);
	}
	if (h >= lotable.size())lotable.resize(h + 1);
	lotable[h].changed = true;
	lotable[h].key = k;
	lotable[h].data = d;
}

void DvHshLine::DeleteLine(vector<DvHshLine>& lotable, int k)
{
	int i = 0, h = hash(lotable.size(), k, i);
	while (h < lotable.size() && lotable[h].key != k) {
		i++;
		h = hash(lotable.size(), k, i);
	}
	lotable[h].changed = false;
}

void DvHshLine::Print(vector<DvHshLine> lotable)
{
	cout << "#\tkey\tdata\tN\\E" << endl;
	for (int i = 0; i < lotable.size(); i++)
		cout << i << "\t" << lotable[i].key << "\t" << lotable[i].data << "\t" << lotable[i].changed << endl;
	cout << endl;
}

bool DvHshLine::Search(vector<DvHshLine> lotable, int k, int & f)
{
	int i = 0, h = hash(lotable.size(), k, i);
	while (h < lotable.size()) {
		if (lotable[h].key == k) {
			f = h;
			return true;
		}
		i++;
		h = hash(lotable.size(), k, i);
	}
	f = -1;
	return false;
}
