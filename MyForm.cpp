#include <iostream>
#include <string>
#include "Point.h"
#include "Kernel.h"
#include "functions.h"
#include "Cluster.h"
#include <time.h>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace BPCF;

[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	BPCF::MyForm form;
	Application::Run(%form);
}

void MyForm::Draw(P::Point* point, int n)
{
	Graphics^ g = pictureBox1->CreateGraphics();
	Pen^ bluePen = gcnew Pen(Color::Blue, 10.0f);
	for (int i = 0; i < n; i++)
	{	
		g->DrawRectangle(bluePen, point[i].x / 2, point[i].y / 2, 10, 10);
	}
}

void MyForm::DrawKernel(Kernel* kernel, int kernelNumb)
{
	Graphics^ g = pictureBox1->CreateGraphics();
	Pen^ bluePen = gcnew Pen(Color::Red, 5.0f);
	for (int i = 0; i < kernelNumb; i++)
	{
		g->DrawRectangle(bluePen, kernel[i].x / 2, kernel[i].y / 2, 5, 5);
	}
}

void MyForm::DrawKernelK(Kernel* kernel, int kernelNumb)
{
	Graphics^ g = pictureBox1->CreateGraphics();
	Pen^ bluePen = gcnew Pen(Color::Black, 5.0f);
	for (int i = 0; i < kernelNumb; i++)
	{
		g->DrawRectangle(bluePen, kernel[i].x / 2, kernel[i].y / 2, 5, 5);
	}
}

void MyForm::DrawConnects(P::Point* point, Kernel* kernel, int* Connects, int n)
{
	Graphics^ g = pictureBox1->CreateGraphics();
	Pen^ bluePen = gcnew Pen(Color::Green, 2.0f);
	g->Clear(Color::White);
	for (int i = 0; i < n; i++)
	{
		g->DrawLine(bluePen, point[i].x / 2, point[i].y / 2, kernel[Connects[i]].x / 2, kernel[Connects[i]].y / 2);
	}
	
}

int MyForm::BPCL(int kernelNumb)
{
		const int n = get_line_count() + 1;
		const int m = 255;
		int qwer, lvD = 0;
		char** cluster = new char*[n];
		int* strCount = new int[n];
		int* sort_strCount = new int[n];
		int* cluster_lvDist = new int[n*m];
		int* Connects = new int[n];
		char elem_ofCluster[] = " ";
		char sec_elem_ofCluster[] = " ";
		string nameCL;
		int half = n/2;
		int s = 0, v = 0;

		P::Point* point = new P::Point[n];

		Kernel* kernel = new Kernel[kernelNumb];

		Cluster* clArray = new Cluster[kernelNumb];

		srand((unsigned int)time(NULL));

		for (int i = 0; i < n; i++)
			cluster[i] = new char[m];

		read_file(cluster, strCount, n);

		sort_cluster(cluster, strCount, sort_strCount, n);

		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				qwer = 0;
				for (int p = 0; p < sort_strCount[i]; p++) {
					*elem_ofCluster = cluster[i][p];
					for (int l = 0; l < sort_strCount[j]; l++)
					{
						*sec_elem_ofCluster = cluster[j][l];
						size_t ld = levenshtein_distance(elem_ofCluster, strlen(elem_ofCluster), sec_elem_ofCluster, strlen(sec_elem_ofCluster));
						if (ld == 1)
							qwer++;
					}
				}
				cluster_lvDist[lvD] = qwer;
				lvD++;
			}
		}
		
		for (int i = 0; i < n; i++)
		{
			nameCL = string(cluster[i], sizeof(char)*sort_strCount[i]);
			point[i].SetPoints(nameCL, 0, 0);
		}

		FindLocations(point, cluster_lvDist, n, lvD);	

		for (int i = 0; i < kernelNumb; i++)
		{
			if (i % 2 == 0) 
			{
				if (s == half)
				{
					s = 0;
				}
				kernel[i].SetKernel(point[s].x + 50, point[s].y + 50);
				s++;
			}
			else
			{
				if (v == half)
				{
					v = 0;
				}
				kernel[i].SetKernel(point[n - (v + 1)].x + 50, point[n - (v + 1)].y + 50);
				v++;
			}

		}
		for (int i = 0; i < kernelNumb; i++)
		{
			listBox1->Items->Add(kernel[i].x + " - " + kernel[i].y);
		}
		listBox1->Items->Add("/////////////////");
		label3->Text = Convert::ToString(KMeans(point, kernel, kernelNumb, n, Connects));
		
		MyForm::DrawConnects(point, kernel, Connects, n);
		MyForm::Draw(point, n);
		MyForm::DrawKernelK(kernel, kernelNumb);
	
		//MessageBox::Show("OK", "Ошибка");
		for (int i = 0; i < kernelNumb; i++)
		{
			listBox1->Items->Add(kernel[i].x + " - " + kernel[i].y);
		}
		
		for (int i = 0; i<n; i++)
			delete cluster[i];
		delete cluster;
		delete strCount;
		delete sort_strCount;
		delete cluster_lvDist;

	return n;
}