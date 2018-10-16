#include <iostream>
using namespace std;

int main()
{
	int a, b;
	int sum, diff;
	cout << "Enter two integers: ";
	cin >> a >> b;
	sum = a + b;
	diff = a - b;
	cout << "Square of sum       :" << sum * sum << endl;
	cout << "Square of difference:" << diff * diff << endl;
	system("pause");
	return 0;
}