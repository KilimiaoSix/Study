#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
	cout << "Enter two integers: ";
	int a, b;
	cin >> a >> b;
	int sum = a + b;
	int diff = a - b;
	cout << "Square of sum    :" << sum * sum << endl;
	cout << "Square of of difference :" << diff * diff << endl;
	system("pause");
	return 0;


}