#pragma once
#include <string>
#include <vector>

using namespace std;

class Cluster
{
public:
	
	vector<double> x;
	vector<double> y;
	vector<string> name;

	Cluster();
	~Cluster();

	void Cluster::setCluster(double x, double y, string name);
	void Cluster::eraseCluster();
private:

};

