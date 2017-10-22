#include<iostream>
#include<array>
using namespace std;


int main()
{
	array<int, 6> array1{{1,2,3,4,5,6}};

	for( const auto& elem: array1 )
	{
		cout << "the element is " << elem << endl ;
	}

	return 1;
}

