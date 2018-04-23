/* Name: Seth John
   Pawprint: scjc68
   ECE 3220 Lab 8 
   Date: 04/16/2018 */

// L13_Ex1_ABC.cpp
// By Luis Rivera

#include <iostream>
#include <cmath>
using namespace std;

class BaseConic {
	protected:
		double x;
		double y;

	public:
		// Notice the default values. They don't need to be 0
		BaseConic(double x0 = 0, double y0 = 0){x = x0; y = y0;}
		virtual ~BaseConic(){};
		void Move(double nx, double ny){x = nx; y = ny;}              
		virtual double Area() = 0; // a pure virtual function ==> ABC
		virtual void display() = 0;
};



class Ellipse : public BaseConic {
	private:
		double a; 	// semi-major axis
		double b; 	// semi-minor axis
		double angle; // orientation angle

	public:
		Ellipse(double x0, double y0, double a0, double b0, double an0);
		~Ellipse(){}
		virtual double Area() {return 3.1416*a*b;}
		void Rotate(double nang){angle += nang;}
		virtual void display();
		
		virtual void Move(double nx, double ny, double nAngle);   //added function
		void Resize(double na, double nb){a = na; b = nb;}        //added function
		void Verticies();                                         //added function
		//virtual void Inside_Outside(int a, int b) {};                   //added function
};

// Notice the default values. Those are used if no parameter is given when
// an object is created.
// Notice how the BaseConic constructor can be called. If other constructors where defined,
// those could be used instead.
Ellipse::Ellipse(double x0=1,double y0=0,double a0=0,double b0=0,double an0=0) : BaseConic(x0,y0) {
	// x and y are set in the BaseConic constuctor
	a = a0;
	b = b0;
	angle = an0;
}

void Ellipse::Move(double nx, double ny, double nAngle)
{
	x=nx; //sets new center
	y=ny;
	cout << "The new center is: (" << x << "," << y << ")" << endl;
	this->Rotate(nAngle);                                               //used to change the angle
	this->Verticies();                                                 //used to display new verticies
}

void Ellipse::Verticies()           //used to calculate the verticies based off the center of the ellipse using the major and minor axis
{
	double v1x=x+a*cos(angle);
	double v1y=y+a*sin(angle);
	double v2x=x-a*cos(angle);
	double v2y=y-a*sin(angle);
	double v3x=x+b*sin(angle);
	double v3y=y+b*cos(angle);
	double v4x=x-b*sin(angle);
	double v4y=y-b*cos(angle);
	cout << "Right Vertex: " << "(" << v1x << "," << v1y << ")" << endl;
	cout << "Left Vertex: " << "(" << v2x << "," << v2y << ")" << endl;
	cout << "Top Vertex: " << "(" << v3x << "," << v3y << ")" << endl;
	cout << "Bottom Vertex: " << "(" << v4x << "," << v4y << ")" << endl;
}

void Ellipse::display() {
	cout << "x = " << x << ", y = " << y << ", a = " << a << ", b = " << b
		 << ", angle = " << angle << ", Area = " << this->Area() << endl;
}

class Circle : public BaseConic {
	private:
		double r; 	// radius
		
	public:
		virtual double Area() {return 3.1416*r*r;}
		Circle(double x0=1,double y0=1,double r0=1) : BaseConic(x0,y0){r = r0;}
		virtual void display();
		
		void Resize(double nr){r=nr;}                    //added function
		void Inside_Outside(double xCoor, double yCoor);       //added function
};

void Circle::Inside_Outside(double xCoor, double yCoor)  //used distance formula and compared it to the radius
{
	double temp_xp=pow(xCoor,2);
	double temp_yp=pow(yCoor,2);
	double temp=pow(xCoor+yCoor,0.5);
	if(temp<r)                                          //if the distance to the point is smaller than radius the point is in the circle  
	{
		cout << "the point (" << xCoor << "," << yCoor << ") is inside the circle" << endl;
	}
	else
	{
		cout << "the point (" << xCoor << "," << yCoor << ") is NOT inside the circle" << endl;
	}
}

void Circle::display() {
	cout << "x = " << x << ", y = " << y << ", r = " << r 
		 << ", Area = " << this->Area() << endl;
}

int main(){
	//BaseConic b0;	// not possible to create an object of the ABC
	Ellipse e0, e1(1), e2(2,3), e3(4,5,6), e4(7,8,9,10), e5(0.1,0.2,0.3,0.4,0.5);
	Circle c0, c1(2,-1,5);
	
	e0.display();	e1.display();	e2.display();	
	e3.display();	e4.display();	e5.display();	
	
	cout << "\n------------------------------------------------------------------\n" << endl;
	
	c0.display();	c1.display();	
	
	cout << "\n------------------------------------------------------------------\n" << endl;
	
	// You CAN use ABC pointers and references
	BaseConic *bptr1 = &e4;
	BaseConic *bptr2 = new Ellipse(1,1,2,3,0.5);
	BaseConic &bref1 = e5;
	bptr1->display();
	bptr2->display();
	bref1.display();
	
	cout << "\n------------------------------------------------------------------\n" << endl;	
	BaseConic *bptr3 = &c0;
	BaseConic *bptr4 = new Circle(-3,0,1.5);
	BaseConic &bref2 = c1;
	bptr3->display();
	bptr4->display();
	bref2.display();
	
	delete bptr2;
	delete bptr4;
	
	
	//cout << "\nCreating object of ABC" << endl;
	//BaseConic B1(0,0);
	//Cannot create a object of the ABC class 
	
	//new material added below
	cout << "\n\nNew ellipse created... ellipse(0,0,3,4,0)\n" << endl;
	Ellipse Fro(0,0,3,4,0);
	cout << "\nDisplaying verticies of ellipse" << endl << endl;
	Fro.Verticies();
	cout << "\nRotating the ellipse by (3.14/2) radians" << endl << endl;
	Fro.Rotate(3.14/2);
	Fro.Verticies();
	cout << "\nMoving the ellipse over 3 and up 1 and (-3.14/2) radians..." << endl << endl;
	Fro.Move(3,1,(-3.14/2));
	Fro.display();
	cout << "\nResizing the Ellipse to a = 8 and b = 9" << endl;
	Fro.Resize(8,9);
	Fro.display();
	cout << "\n\nNew circle created... circle(0,0,4)" << endl;
	Circle Yo(0,0,4);
	cout << "\nchecking if point (1,1) is inside the circle..." << endl;
	Yo.Inside_Outside(1,1);
	cout << "\nchecking if point (20,20) is inside the circle..." << endl;
	Yo.Inside_Outside(20,20);
	cout << "\nMoving the circle over 2 and up 2" << endl;
	Yo.Move(2,2);
	Yo.display();
	cout << "\nResizing the Circle to a radius of 8" << endl;
	Yo.Resize(8);
	Yo.display();
	
	cout << "\n\nUsing pointers to the ABC class to point to the derived class objects created before" << endl;
	BaseConic * Noble=&Fro;
	BaseConic * Deeds=&Yo;
	
	Noble->display();
	Deeds->display();

	cout << endl;
	return 0;
}