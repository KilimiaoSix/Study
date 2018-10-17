#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int main()
{
	const int n(30);
	int i, a[n];
	cout << "Enter" << "integers : \n";
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cout << "\n The same integers ,in reverse order : \n";
	for (i = 0; i < n; ++i)
	{
		cout << setw(6) << a[n - i - 1]
			<< (i % 10 == 9 ? '\n' : ' ');
	}
	system("pause");
	return 0;
}