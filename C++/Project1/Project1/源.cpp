#include <iostream>
#include <stdlib.h>
#define ADD(X,Y) ((X)+(Y))
using namespace std;
int main()
{
	const int abb (10);
	const int add = 10;
	printf("%d\n", ADD(1, 2) * 2);
	printf("%d\n", abb + add);
	system("pause");
	return 0;
}