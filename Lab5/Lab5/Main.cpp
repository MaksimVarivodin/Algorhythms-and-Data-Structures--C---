#include "Header.h"
vector<double>  filler2(const int & size) {
	vector<double> arr(size, 0);
	for (int i = 0; i < size; i++) {
		arr[i] = (i + 1) / (size* 1.0);
	}
	return arr;
}


double MinMax(vector<double> arr, bool minmax) {
	if (arr.size() == 0) {
		
		return NULL;
	}

	double min = arr[0];
	for (double a : arr) {
		if (minmax ? a< min : a> min) {
			min = a;
		
		}

	}
	return min;
}
int LinearSearch(vector<double> arr, double val, long long& counter) {
	
	counter+=2;
	for (int i = 0; i < arr.size(); i++) {
		counter++;
		if (arr[i] == val) 
			return i;		
		counter += 3;
	}
}
int BarierSearch(vector<double> arr, double val, long long &counter) {

	int k = arr.size();
	arr.resize(arr.size()+1);	
	arr[k] = val;
	counter += 2;
	int i = 0;
	counter+=3;
	while (arr[i] != val)
	{
		i++;
		counter += 3;

	}

	return i < k ? i : -1;
}
int BinarySearch(vector<double> arr, double val,long long &counter) {
	
	int left = 0, right = arr.size() - 1, mid = (right + left) / 2;
	counter += 7;

	while (arr[mid] != val) {
		
		if (arr[left]) { counter++; return left; }
		else if (arr[right]) { 
			counter+= 2;
			return right; }
		else if (val < arr[mid]) {
			counter += 3;
			right = mid - 1;
		}
		else {
			counter += 3;
			left = mid + 1;
		}
		counter += 2;
		mid = (right + left) / 2;
		counter += 4;
	}
	return mid;
}
int ln_seek_substring(string s, string f, long long & counter) {
	int i, j, k, N, M;
	N = s.length();
	M = f.length();
	k = -1;
	counter += 3;

	do {
		k++;
		j = 0;
		counter += 3;
		counter += 1 + 1 + 2;
		while ((j < M) && s[k + j] == f[j]) {
			j++;
			counter += 6;
		}			
		counter++;
		if (j == M)
			return k;
		counter += 2;
	} while (k< N-M);
	return -1;
}
int bm_seek_substring(string source, string find, long long & counter) {

	int sourceLength,
		findLength;

	int res = -1;

	sourceLength = source.length();
	findLength = find.length();
	// проверки на адекватность введенных строк
	if (sourceLength == 0) {
		cout << "Неверно задана строка" << endl;
		return res;
	}
	else if (findLength == 0) {
		cout << "Неверно задана подстрока" << endl;
		return res;
	}
	else {

		int i = 0, pos = 0;
		int bmt[256];
		for (; i < 256; i++)
			bmt[i] = findLength;
		for (i = findLength - 1; i >= 0; i--) {
			if (bmt[(short)(find[i])] == findLength) {
				bmt[(short)(find[i])] = findLength - i - 1;
			}
		}
			
		pos = findLength - 1;
		while (pos < sourceLength) {
			if (find[findLength - 1] != source[pos]) {
				pos = pos + bmt[(short)(source[pos])];
			}
			else {

				for (i = findLength - 2; i >= 0; i--) {
					if (find[i] != source[pos - findLength + i + 1]) {
						pos += bmt[(short)(source[pos - findLength + i + 1])] - 1;
						break;
					}
					else {
						if (i == 0) {
							return pos - findLength + 1;
						}
							
					}
				}
			}
		}
			
    }
}
string::size_type kmp_seek_substring(const string & s, int begin, const string & pattern, long long & counter) {
	vector<int> pf(pattern.length());
	pf[0] = 0;
	counter+=4;
	for (int k = 0, i = 1; i < pattern.length(); ++i) {
		counter += 3;
		while ((k > 0) && (pattern[i] != pattern[k]))
		{
			k = pf[k - 1];
			counter += 2;
		}
		counter++;
		if (pattern[i] == pattern[k]) {
			k++;
			counter++;
		}
			
		pf[i] = k;
		counter++;
		counter += 3;
	}
	counter += 3;
	for (int k = 0, i = begin; i < s.length(); ++i) {
		counter += 3;
		while ((k > 0) && (pattern[k] != s[i]))
		{
			k = pf[k - 1];
			counter += 2;
		}
		counter++;
		if (pattern[k] == s[i])
		{
			k++;
			counter += 2;
		}
		counter++;
		if (k == pattern.length()) {
			counter += 2;
			return (i - pattern.length() + 1);
		}
		counter += 3;
	}
	return (string::npos);
}
int rabin_karp(string &text, string &pattern, int q, long long& counter)
{
	
	/*length of the pattern string*/
	int m = pattern.length();
	/*length of the text string*/
	int n = text.length();
	int p = 0, t = 0, h = 1, d = 26;// here p is the hash value for pattern and t is the hash value of the substring;
	counter += 6;
	/*h=pow(d,M-1) where d is 26 if the text contain only lowe case characters.*/
	counter += 3;
	for (int i = 0; i < m - 1; i++)
	{
		h = (h*d) % q;
		counter += 3;
		counter += 3;
	}
	/*calculate the hash value for the pattern string and the first substring of length m*/
	counter += 2;
	for (int i = 0; i < m; i++)
	{
		p = (d*p + pattern[i]) % q;//pattern string;
		t = (d*t + text[i]) % q;//substring;
		counter += 3;
		counter += 4;
		counter += 4;
	}
	/*for remaining substring of length m*/
	counter += 3;
	for (int i = 0; i <= n - m; i++)
	{
		counter++;
		/*if hash values are same then check charachter by character in substring and pattern string.*/
		if (p == t)
		{
			counter += 3;
			int flag = 0;
			for (int j = 0; j < m; j++)
			{
				counter+=2;
				if (text[i + j] != pattern[j])
				{
					counter++;
					flag = 1;
					break;
				}
				counter += 3;
			}
			/*if all the character are match then print the starting index of substring.*/
			counter++;
			if (flag == 0)
			{
				return i;
			}
		}
		/*find the hash value of the next substring by removinf the first character from previos substring
		 and add next char to the end of the previous string*/
		 /*it take O(1) time to find the hash values*/
		counter+=2;
		if (i < n - m)
		{
			counter += 6;
			t = (d*(t - text[i] * h) + text[i + m]) % q;
			counter++;
			if (t < 0)
			{
				counter += 2;
				t = (t + q);
			}
		}
		counter += 4;
	}
}
int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int c1 = 1, iter = 0, iter2 = 0, count = 36;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	cout <<endl<< endl<<  "\t ЗАДАНИЕ 2:" << endl<< endl;
	vector<string> text = { "Have image second bring waters they're. Light a us. She'd first give stars. Isn't creeping tree above one multiply. Living gathering.",
				  " Meat rule every to that heaven air. Man moveth days cattle beast void, after you'll greater saying.Every also beginning own night fill.",
				  "Wherein.Day all third which.Whales after.Grass to, gathering fly face.Subdue.Creeping Him said shall two bring fly whales grass.Creature ",
				  "fruit land living air waters replenish of darkness stars created seed saw.I him living saw one.Hath give very made moving from called face",
				  " saw.Gathering he two dry own created third deep creepeth, male.Said don't made moving so god land him, above meat.Spirit gathering creepeth",
				  " fly bearing they're Cattle give forth that yielding stars for light a saying. Waters stars female itself which she'd blessed so cattle you're",
				  " were gathered. Man beast i have all signs night let. Light have hath. Dominion days Set won't multiply seed earth heaven Male behold may ",
				  "replenish fowl shall, given.Beast blessed his midst brought fill seasons cattle gathering moving lesser years.Bring subdue, seed without ",
				  "and lesser moved.It brought the moved fly make bring forth called lights it fruit replenish continuation." };
	
	string txt = "";
	for (string a : text) {
		txt += a;
	}
	vector<long long> counter(4, 0);
	for (int i = 0; i < 3; i++) {
		string f = "";
		if (i == 0) f = "Have";
		else if (i == 1)f = "male.S";
		else if (i == 2)f = "uation.";
		ln_seek_substring(txt, f, counter[0]);
		bm_seek_substring(txt, f, counter[1]);
		kmp_seek_substring(txt, 0, f, counter[2]);
		rabin_karp(txt, f, 97, counter[3]);
		for (int j = 0; j < counter.size(); j++)
			cout << counter[j] << endl;
	}
	

}