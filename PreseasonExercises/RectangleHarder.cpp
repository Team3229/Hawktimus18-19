#include <iostream>
using namespace std;

class Rectangle
{
private:
	double length, width; //2 doubles, only visible to members of the class

public:
	void setValues(double l, double w); //Function to set the length and width values
	double getArea() { return length * width; } //Returns the product of the 2

};

void Rectangle::setValues(double l, double w)
{
	length = l; //Sets the private class variable of length to the user input
	width = w; //Sets width equal to the users input
}

int main()
{
	Rectangle rect1; //Creates an object of class Rectangle

	rect1.setValues(3.4, 5.8); //Passes in values for length and width

	cout << "Area of rectangle: " << rect1.getArea() << endl;

	system("pause");
	return 0;
}
