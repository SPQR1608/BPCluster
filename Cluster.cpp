#include "Cluster.h"
#include <vector>

Cluster::Cluster()
{
}

Cluster::~Cluster()
{
}

void Cluster::setCluster(double x, double y, string name)
{
	Cluster::x.push_back(x);
	Cluster::y.push_back(y);
	Cluster::name.push_back(name);
}

void Cluster::eraseCluster()
{
	Cluster::x.clear();
	Cluster::y.clear();
	Cluster::name.clear();
}