#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
	cout << "Enter two lines of test:\n";
	string s, t;
	getline(cin, s);  //���ַ�������ö�
	getline(cin, t);
	cout << "Output in alphabetic order:\n";
	if (s <= t)
	{
		cout << s << endl << t << endl;
	}
	else
		cout << t << endl << s << endl;
	system("pause");
	return 0;
}