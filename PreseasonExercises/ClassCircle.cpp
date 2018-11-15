#include <iostream>
using namespace std;

class Circle
{
private:
	// it's good programming practice to declare mathematical numbers such as PI as constants
	const float PI = 3.14159265358979323846;
	double radius;

public:
	// function prototypes
	void getRadius(); 
	double circum();
	double area();
	double surfaceArea();
};

// declaring the functions down here works the same as if you were to
// declare it inside the class, it just looks nicer when you seperate it
void Circle::getRadius() 
{
	cout << "Enter the radius of the circle: ";
	cin >> radius;
}

double Circle::circum()
{
	return 2 * PI * radius; // uses our PI constant to do the circumference formula
}

double Circle::area()
{
	return PI * radius * radius;
}

double Circle::surfaceArea()
{
	return (4 / 3) * PI * (radius * radius * radius);
}

int main()
{
	Circle myCircle; // creates object of class circle

	myCircle.getRadius();
	cout << "Circumference of circle: " << myCircle.circum() << endl;
	cout << "Area of circle: " << myCircle.area() << endl;
	cout << "Surface area of sphere: " << myCircle.surfaceArea() << endl;

	return 0;
}