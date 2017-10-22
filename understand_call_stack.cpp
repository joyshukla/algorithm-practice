#include<iostream>
using namespace std;

void displaySquare(int i)
{
	cout << i*i << endl;
	if (i > 0)
		displaySquare(i - 1);
}

int main()
{
	int i = 10;
	displaySquare(i);

	return 1;
}