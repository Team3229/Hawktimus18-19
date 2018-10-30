#include <iostream>
using namespace std;

class Rectangle
{
private:
	double length = 5.7;
	double width = 13.2;

public:
	double getArea()
	{
		return length * width;
	}

};

int main()
{
	Rectangle myRect;

	cout << "Area of rectangle: " << myRect.getArea();

	return 0;
}