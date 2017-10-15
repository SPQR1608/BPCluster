#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <fstream>
#include <ctype.h>
#include <string>
#include <cmath>
#include "Point.h"
#include "functions.h"

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

void FindLocations(Point* point, int* distance, int n, int m)
{
	int i, j, p = 0;
	point[0].x = rand() % 50 + 1;
	point[0].y = rand() % 50 + 1;

	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			do
			{
				point[j].x = rand() % 300 + 2;
				point[j].y = rand() % 300 + 2;

			} while (distance[p] != CalcDistance(point[i].x, point[i].y, point[j].x, point[j].y));

			p++;		
			cout << point[i].name << ": ";
			cout << point[i].x << "-" << point[i].y << " and " << endl;
			cout << point[j].name << ": ";
			cout << point[j].x << "-" << point[j].y << endl;
			cout << "dist -- " << CalcDistance(point[i].x, point[i].y, point[j].x, point[j].y);
			cout << endl << endl;
		}		
	}
}

int CalcDistance(int x, int y, int x1, int y1)
{
	return (int)sqrt(pow((x - x1), 2) + pow((y - y1), 2));
}

double random(double min, double max)
{
	return (double)(rand()) / RAND_MAX*(max - min) + min;
}
