#include "Kernel.h"

using namespace std;

Kernel::Kernel()
{
}

Kernel::~Kernel()
{
}

void Kernel::SetKernel(double x, double y)
{
	Kernel::x = x;
	Kernel::y = y;
}