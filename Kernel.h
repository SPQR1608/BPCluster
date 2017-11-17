#pragma once

using namespace std;

/// <summary>
/// This class contains cluster kernels
/// </summary>
class Kernel
{
public:
	double x;
	double y;

	Kernel();
	~Kernel();
	void Kernel::SetKernel(double x, double y);
private:

};