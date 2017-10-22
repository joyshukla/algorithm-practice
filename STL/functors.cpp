// functor objects

#include<iostream>
#include<list>
#include<iterator>
using namespace std;

void display(list<int> L)
{
	for(const auto& elem: L )
	{
		cout << elem << " ";
	}
	cout << endl;
}

struct sortDesc
{
	bool operator() (const int left, const int right)
	{
		return left > right;
	}
};

int main()
{
	list<int> list1 = {1,4,5,3};
	cout << "Orig list1 :";
	display(list1);
	list1.sort();
	cout << "Sorted list1 :";
	display(list1);

	list1.sort(sortDesc());
	cout << "Sorted(Descending) list1 :";
	display(list1);

	return 1;
}
