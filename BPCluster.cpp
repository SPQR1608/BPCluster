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
#include <string.h>

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

void read_file(char** cluster, int* strCount, int n)
{
	int j = 0;
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
		}
	}
	file.close();
}

void sort_cluster(char** cluster, int* strCount, int* sort_strCount, int n)
{
	int k = 0;

	for (int i = 0; i < n; i++)
	{
		k = 0;
		for (int j = 0; j < strCount[i]; j++)
		{
			if (isalpha(cluster[i][j]))
			{
				cluster[i][k] = cluster[i][j];
				k++;
			}	
		}
		sort_strCount[i] = k;
	}
}

void printCL(char* str, int* count)
{
	for (int i = 0; i < count[i]; i++)
		cout << str[i];
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int n = get_line_count() + 1;
	const int m = 255;
	int qwer, lvD = 0;
	char** cluster = new char*[n];
	int* strCount = new int[n];
	int* sort_strCount = new int[n];
	int* cluster_lvDist = new int[m];
	//char* cluster_str2 = new char[m];
	char elem_ofCluster[] = " ";
	char sec_elem_ofCluster[] = " ";
	
	for (int i = 0; i < n; i++)
		cluster[i] = new char[m];

	read_file(cluster, strCount, n);

	sort_cluster(cluster, strCount, sort_strCount, n);

	for (int i = 0; i < n-1; i++){
		for (int j = i + 1; j < n; j++){
			qwer = 0;
			cout << endl << "LV : ";
			for (int z = 0; z < sort_strCount[i]; z++)
				cout << cluster[i][z];
			cout << " and ";
			for (int z = 0; z < sort_strCount[j]; z++)
				cout << cluster[j][z];
			cout << " -- ";

			for (int p = 0; p < sort_strCount[i]; p++){
				*elem_ofCluster = cluster[i][p];
				for (int l = 0; l < sort_strCount[j]; l++)
				{
					*sec_elem_ofCluster = cluster[j][l];
					size_t ld = levenshtein_distance(elem_ofCluster, strlen(elem_ofCluster), sec_elem_ofCluster, strlen(sec_elem_ofCluster));
					/*cout << "The Levenshtein string distance between " << elem_ofCluster << " and ";
					cout << sec_elem_ofCluster;
					cout << ": " << ld << endl;*/
					if (ld == 0)
						qwer++;
				}
			}
			cluster_lvDist[lvD] = qwer;
			cout << cluster_lvDist[lvD] << endl;
			lvD++;
		}
	}
	
	for (int i = 0; i<n; i++)
		delete cluster[i];
	delete cluster;

	system("Pause");
	return 0;
}

