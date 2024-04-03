#include<iostream>
#include"Polinomial.h"
using namespace std;
int main() {
	Polinomial<int>a,b,c;
	a.Input();
	cout <<a.Size()<<" " << a.Degree() << endl;
	a.Output();
	//b.Input();
	//b.Output();
	c=a%(7);
	c.Output();
	c.Output();
	return 0;
}