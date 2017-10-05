// BPCluster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <fstream>
#include <ctype.h>

using namespace std;

size_t levenshtein_distance(const char* s, size_t n, const char* t, size_t m)
{
	++n; ++m;
	size_t* d = new size_t[n * m];

	memset(d, 0, sizeof(size_t)* n * m);

	for (size_t i = 1, im = 0; i < m; ++i, ++im)
	{
		for (size_t j = 1, jn = 0; j < n; ++j, ++jn)
		{
			if (s[jn] == t[im])
			{
				d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
			}
			else
			{
				d[(i * n) + j] = min(d[(i - 1) * n + j] + 1, 
					min(d[i * n + (j - 1)] + 1,
					d[(i - 1) * n + (j - 1)] + 1));
			}
		}
	}

/*#ifdef DEBUG_PRINT
	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			cout << d[(i * n) + j] << " ";
		}
		cout << endl;
	}
#endif*/

	size_t r = d[n * m - 1];

	delete[] d;

	return r;
}

int get_line_count()
{
	int count;
	ifstream inp("BPList.txt");
	if (!inp)
		cout << "Error!" << endl;
	else
	{
		count = 0;
		while (inp.ignore(numeric_limits<streamsize>::max(), '\n'))
		{
			if (!inp.eof())
				count++;
		}
	}
	inp.close();
	return count;
}

int read_file(char** cluster, int* strCount, int n)
{
	int j = 0;
	char symbol;
	char arr[255];

	ifstream file;
	file.open("BPList.txt");
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла." << endl;
		cout << "Работа программы завершена." << endl;
		system("pause");
	}

	for (int i = 0; i < n; i++)
	{
		file.getline(arr, 255);
		strCount[i] = strlen(arr);
		for (int k = 0; k<strCount[i]; k++)
		{
			cluster[i][k] = arr[k];
			/*file >> symbol;
			if (symbol == '\n')
				break;
			else if (symbol == ',' || isdigit(symbol))
				continue;
			else
			{
				cluster[i][k] = symbol;
				j++;
			}*/
		}
	}
	file.close();

	return strlen(arr);
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*char* str1[] = { "Helo", "Welcome", "Home", "Dog"};
	char* str2[] = {"Back", "Park", "Yellow", "Helo"};

	vector <int> vecFirst;
	for (int i = 0; i<10; ++i)
	{
		vecFirst.push_back(i); 
	}
	cout << "vecFirst contains: ";
	for (int i = 0; i<vecFirst.size(); ++i)
		cout << vecFirst[i] << ends;*/

	char** cluster;
	int* strCount;
	const int n = get_line_count()+1;
	const int m = 255;

	strCount = new int[n];
	cluster = new char*[n];
	
	for (int i = 0; i < n; i++)
		cluster[i] = new char[m];

	int fg = read_file(cluster, strCount, n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < strCount[i]; j++)
		{
			cout << cluster[i][j];
		}
		cout << endl;
	}
	cout << fg << endl;
	/*
	for (int i = 0; i < 4; i++){
		for (int j = i; j < 4; j++){
			size_t ld = levenshtein_distance(str1[i], strlen(str1[i]), str2[j], strlen(str2[j]));
			cout << "The Levenshtein string distance between " << str1[i] << " and " << str2[j] << ": " << ld << endl;
		}
	}*/
	system("Pause");
	return 0;
}

