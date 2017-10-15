// BPCluster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Point.h"
#include "functions.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const int n = get_line_count() + 1;
	const int m = 255;
	int qwer, lvD = 0;
	char** cluster = new char*[n];
	int* strCount = new int[n];
	int* sort_strCount = new int[n];
	int* cluster_lvDist = new int[n*m];
	char elem_ofCluster[] = " ";
	char sec_elem_ofCluster[] = " ";
	string nameCL;

	Point *point = new Point[n];
	
	for (int i = 0; i < n; i++)
		cluster[i] = new char[m];

	read_file(cluster, strCount, n);

	sort_cluster(cluster, strCount, sort_strCount, n);

	for (int i = 0; i < n-1; i++){
		for (int j = i + 1; j < n; j++){
			qwer = 0;
			for (int p = 0; p < sort_strCount[i]; p++){
				*elem_ofCluster = cluster[i][p];
				for (int l = 0; l < sort_strCount[j]; l++)
				{
					*sec_elem_ofCluster = cluster[j][l];
					size_t ld = levenshtein_distance(elem_ofCluster, strlen(elem_ofCluster), sec_elem_ofCluster, strlen(sec_elem_ofCluster));
					if (ld == 0)
						qwer++;
				}
			}
			cluster_lvDist[lvD] = qwer;
			lvD++;
		}
	}
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		nameCL = string(cluster[i], sizeof(char)*sort_strCount[i]);
		point[i].SetPoints(nameCL, 0, 0);
	}

	FindLocations(point, cluster_lvDist, n, lvD);

	for (int i = 0; i<n; i++)
		delete cluster[i];
	delete cluster;
	delete strCount;
	delete sort_strCount;
	delete cluster_lvDist;

	system("Pause");
	return 0;
}

