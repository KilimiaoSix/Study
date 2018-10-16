#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	char ch = 'A';
	double ff = 5.0 / 3;
	float f = ff;
	bool b = (f > 1);
	int i, j;
	j = 2 * (i = 5.0 / 3); //Боi=5.0 / 3 j = 2 * i
	cout << "ch = " << ch
		<< "   ASCII value :" << (int)ch << endl;
	cout << fixed << setprecision(10);
	cout << " f = " << f << "ff = " << ff << endl;
	cout << " i = " << i << " j = " << j  << endl;
	if (b)
		cout << "The variable b is equal to true .\n";
	cout << "Number of bytes for type 'bool':   " << sizeof(bool) << endl;
	cout << "Number of bytes for type 'char':   " << sizeof(char) << endl;
	cout << "Number of bytes for type 'int':   " << sizeof(int) << endl;
	cout << "Number of bytes for type 'float':   " << sizeof(float) << endl;
	cout << "Number of bytes for type 'double':   " << sizeof(double) << endl; 
		system("pause");
	return 0;
}
