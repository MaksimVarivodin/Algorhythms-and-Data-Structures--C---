#include "Header.h"
vector<double>  filler1(const int & size) {
	vector<double> arr(size, 0);
	for (int i = 0; i < size; i++) {
		arr[i] = (i + 1)/(size* 1.0);
	}
	for (int i = 0; i < size; i++) {
		int j = rand() % size;
		double buf = arr[i];
		arr[i] = arr[j];
		arr[j] = buf;
	}
	return arr;
}

vector<double>  filler2(const int & size) {
	vector<double> arr(size, 0);
	for (int i = 0; i < size; i++) {
		arr[i] = (i + 1) /(size* 1.0);
	}
	return arr;
}

vector<double>  filler3(const int & size) {
	vector<double> arr(size, 0);
	for (int i = size - 1; i >= 0; i--) {
		arr[i] = (size - i) / (size* 1.0);
	}
	return arr;
}

void bubbleSort(vector<double>&arr, long long & counter) {
	
	int i = 1;
	counter++;//i = 1
	for (; i < arr.size(); i++) {
		int j = arr.size() - 1;
		counter += 2;// j = arr.size() - 1
		for (; j >= i; j--)
		{
			if (arr[j] < arr[j - 1]) {
				double b = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = b;
				counter += 5;// swap(arr[j], arr[j -1])
			}
			counter += 2 + 3 ;// (arr[j] < arr[j - 1]) + (j >= i; j--)
			
		}
		counter += 3;// i < arr.size(); i++
	}
	return;
}
void shakerSort(vector<double>& arr, long long & counter) {
	int left = 0, right = arr.size() - 1;
	bool flag = true;
	counter += 4;/*
				 left = 0
				  arr.size() - 1
				  right = arr.size() - 1
				  flag = true
				 */
	
	while (left < right && flag) {
		flag = false;
		int i = left;
		counter += 2;
		for (; i < right; i++) {
			if (arr[i] > arr[i + 1]) {
				double buf = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = buf;
				flag = true;
				counter += 6;
			}	
			counter += 3;
		}
		right--;
		i = right;
		counter += 3;
		for (; i > left; i--) {
			if (arr[i - 1]> arr[i]) {
				double buf = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = buf;
				flag = true;
				counter += 6;
			}
			counter += 3;
		}
		left++;
		counter += 2;
		counter += 3;//left < right + flag + left < right && flag
	}
	counter += 3;//left < right + flag + left < right && flag
}

double MinMax(vector<double> arr, bool minmax, long long & counter) {
	if (arr.size() == 0) {
		counter++;
		return NULL;
	}

	double min = arr[0];
	counter+=2;

	for (double a : arr) {
		if (minmax ? a< min : a> min) {
			min = a;
			counter += 2;
		}			
		counter += 2;
	}
	return min;
}
void bucketSort(vector<double> &arr, long long  & counter) {
	int n = arr.size();
	vector < vector < double >> b(n);
	counter++;
	for (int i = 0; i < n; i++)
	{
		int bi = (n - 1) * arr[i];
		counter += 3;
		b[bi].push_back(arr[i]);
		counter++;
		counter += 2;
	}
	counter++;
	for (int i = 0; i < n; i++) {
		sort(b[i].begin(), b[i].end());
		counter += b[i].size();
		counter += 2;
	}
	counter += 2;
	int index = 0;
	for (int i = 0; i < n; i++) {
		counter++;
		for (int j = 0; j < b[i].size(); j++) {
			arr[index++] = b[i][j];
			counter += 2;
			counter += 2;
		}
		counter += 2;
	}
}
int main() {
	int c1 = 1, iter = 0, iter2 = 0, count = 36;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	
	int k = 0;
	vector<long long > average = vector<long long >(count, 0.0);
	vector<int> sizes = { 10, 100, 1000, 10000 };
	for (int iterator = 0; iterator < 20; iterator++) {
		vector<long long>counters(count, 0);
		
		vector<vector<double>> arr(count, vector<double>());
		vector<double>(*fues[])(const int&) = { filler1, filler2, filler3 };
		for (int i = 0; i < sizes.size(); i++) {
			for (int j = 0; j < 3; j++) {
				vector<double>buf = fues[j](sizes[i]);
				for (k = i * 9 + j * 3; k < i * 9 + j * 3 + 3; k++)
					arr[k] = vector<double>(buf);
			}
		}
		iter2 = 0; k = 0;
		for (int i = 0; i < sizes.size(); i++) {
			for (int j = 0; j < 3; j++){
				bubbleSort(arr[k], counters[k]);
				shakerSort(arr[k + 1], counters[k + 1]);
				bucketSort(arr[k + 2], counters[k + 2]);
				average[k]    += counters[k];
				average[k+ 1] += counters[k+ 1];
				average[k+ 2] += counters[k+ 2];
				k += 3;
			}
		}
		if(iterator== 0)
		for (int i = 0; i < 3; i++) {
			print(arr[i]);
		}
	}

	k = 0;
	for (int i = 0; i < sizes.size(); i++) {
		for (int j = 0; j < 3; j++) {
			string s = "";
			cout<< endl << "Размер:" << sizes[i] << endl;
			if (j == 0) { s = "случайно"; }
			else if (j==1) { s = "прямо"; }
			else if (j==2) { s = "обратно"; }
			cout << "Заполнение:" << s << endl<< endl;
			cout << "Бабл:" << average[k] / 20 << endl;
			cout << "Шейк:" << average[k+ 1] / 20 << endl;
			cout << "Блок:" << average[k+ 2] / 20 << endl<< endl;
			k += 3;
		}
	}
	

}