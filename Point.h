#pragma once
#include <string>

using namespace std;
namespace P {
	class Point
	{
	public:
		string name;
		int x;
		int y;

		Point();

		void Point::SetPoints(string name, int x, int y);

		~Point();

	private:

	};
}
