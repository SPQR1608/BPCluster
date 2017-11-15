#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <fstream>
#include <ctype.h>
#include <string>
#include <cmath>
#include <time.h>
#include "Point.h"
#include "Kernel.h"
#include "Cluster.h"
#include "functions.h"
#include "MyForm.h"
//#include <glut.h>

using namespace std;
using namespace P;

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
		return 0;
		//cout << "Error!" << endl;
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
		return;
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
	int k = 0, s = 0;
	char temp[] = " ";

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

	/*
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < sort_strCount[i]; j++)
		{
			*temp = cluster[i][j];
			s = 0;
			k = 0;
			for (int p = 0; p < sort_strCount[i]; p++)
			{
				if (*temp == cluster[i][p])
				{
					s++;
					if (s == 1)
					{
						cluster[i][k] = cluster[i][p];
						k++;
					}				
				}				
				else
				{					
					cluster[i][k] = cluster[i][p];
					k++;
				}
			}
			sort_strCount[i] = k;
		}
	} */
}

void FindLocations(P::Point* point, int* distance, int n, int m)
{
	//srand((unsigned int)time(NULL));
	int i, j, p = 0;
	point[0].x = rand() % 50 + 1;
	point[0].y = rand() % 50 + 1;

	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			do
			{
				point[j].x = rand() % 800 + 10;
				point[j].y = rand() % 800 + 10;

			} while ((distance[p]*2) != CalcDistance(point[i].x, point[i].y, point[j].x, point[j].y));

			p++;		
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

/*void KMeans1(P::Point* point, Kernel* kernel, int clusterNumb, int n)
{
	bool flag = true;
	double distance = 0, minDist = 0;
	int** arrIndex = new int*[2];
	int minIndex = 0, Index = 0;
	int l = 0, p = 0;
	for (int i = 0; i < 2; i++)
		arrIndex[i] = new int[n];

	while (flag)
	{
		if (l % 2 == 0)
			Index = 0;
		else
			Index = 1;

		for (int i = 0; i < n; i++)
		{
			minDist = 0;
			minIndex = 0;
			for (int j = 0; j < clusterNumb; j++)
			{
				distance = sqrt(pow((point[i].x - kernel[j].x), 2) + pow((point[i].y - kernel[j].y), 2));
				if (j == 0)
				{
					minDist = distance;
				}
				else if (distance < minDist)
				{
					minDist = distance;
					minIndex = j;
				}
			}
			kernel[minIndex].x = abs((point[i].x - kernel[minIndex].x) / 2);
			kernel[minIndex].y = abs((point[i].y - kernel[minIndex].y) / 2);
		}
		for (int i = 0; i < n; i++)
		{
			minDist = 0;
			minIndex = 0;
			for (int j = 0; j < clusterNumb; j++)
			{
				distance = sqrt(pow((point[i].x - kernel[j].x), 2) + pow((point[i].y - kernel[j].y), 2));
				if (j == 0)
				{
					minDist = distance;
				}
				else if (distance < minDist)
				{
					minDist = distance;
					minIndex = j;
				}
			}
			arrIndex[Index][i] = minIndex;
		}

		p = 0;
		if (l != 0)
		{
			for (int i = 0; i < n; i++)
			{
				if (arrIndex[0][i] == arrIndex[1][i])
					p++;

				if (p == n || l == 20)
					flag = false;
			}
		}
		l++;
	}
	for (int i = 0; i<2; i++)
		delete arrIndex[i];
	delete arrIndex;
}*/

int KMeans(P::Point* point, Kernel* kernel, int clusterNumb, int n, int* Connects)
{
	bool flag = true;
	double distance = 0, minDist = 0;
	int** arrIndex = new int*[2];
	int* fArrIndex = new int[n];
	int* arrMinIndex = new int[n];
	int* distArr = new int[n];
	int minIndex = 0, Index = 0;
	int l = 0, p = 0;
	for (int i = 0; i < 2; i++)
		arrIndex[i] = new int[n];

	while (flag)
	{
		if (l % 2 == 0)
			Index = 0;
		else
			Index = 1;
		for (int i = 0; i < n; i++)
		{
			minDist = 0;
			minIndex = 0;
			for (int j = 0; j < clusterNumb; j++)
			{
				distance = sqrt(pow((point[i].x - kernel[j].x), 2) + pow((point[i].y - kernel[j].y), 2));
				if (j == 0)
				{
					minDist = distance;
				}
				else if (distance < minDist)
				{
					minDist = distance;
					minIndex = j;
				}
			}
			arrMinIndex[i] = minIndex;
			/*kernel[minIndex].x = abs((point[i].x - kernel[minIndex].x) / 2);
			kernel[minIndex].y = abs((point[i].y - kernel[minIndex].y) / 2);*/
		}
		int z = 0;
		int aver = 0;
		for (int i = 0; i < clusterNumb; i++)
		{
			z = 0;
			aver = 0;
			for (int s = 0; s < n; s++)
			{
				if (arrMinIndex[s] == i)
				{
					fArrIndex[z] = s;
					z++;
				}
			}
			if (z == 0)
				continue;
			for (int s = 0; s < z; s++)
			{
				aver += CalcDistance(point[fArrIndex[s]].x, point[fArrIndex[s]].y, kernel[i].x, kernel[i].y);
			}
			aver = aver / z;
			for (int s = 0; s < z; s++)
			{
				/*kernel[i].x = abs((point[fArrIndex[s]].x - kernel[i].x) / 2);
				kernel[i].y = abs((point[fArrIndex[s]].y - kernel[i].y) / 2);*/
				do
				{
					kernel[i].x = rand() % 800 + 1;
					kernel[i].y = rand() % 800 + 1;
				} while ((aver != CalcDistance(point[fArrIndex[s]].x, point[fArrIndex[s]].y, kernel[i].x, kernel[i].y)));
			}	
		}

		for (int i = 0; i < n; i++)
		{
			minDist = 0;
			minIndex = 0;
			for (int j = 0; j < clusterNumb; j++)
			{
				distance = sqrt(pow((point[i].x - kernel[j].x), 2) + pow((point[i].y - kernel[j].y), 2));
				if (j == 0)
				{
					minDist = distance;
				}
				else if (distance < minDist)
				{
					minDist = distance;
					minIndex = j;
				}
			}
			arrIndex[Index][i] = minIndex;
		}

		p = 0;
		if (l != 0)
		{
			for (int i = 0; i < n; i++)
			{
				if (arrIndex[0][i] == arrIndex[1][i])
					p++;

				if (p == n || l == 100)
					flag = false;
			}
		}
		l++;
	}

	for (int i = 0; i < n; i++)
	{
		Connects[i] = arrIndex[0][i];
	}
	for (int i = 0; i<2; i++)
		delete arrIndex[i];
	delete arrIndex;

	return l;
}