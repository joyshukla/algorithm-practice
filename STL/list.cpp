// by default list is doubly linked list

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

int main()
{
	list<int> list1({1,10,5,15});
	list<int> list2({100,101,501,150});

	//list1.push_front(100);
	//list1.push_back(50);

	cout << "List1 : ";
	display(list1);

	cout << "List2 : ";
	display(list2);

	list1.splice(--list1.end(), list2, ++list2.begin(), --list2.end());

	cout << endl << "** After splice **" << endl;

	cout << "List1 : ";
	display(list1);

	cout << "List2 : ";	
	display(list2);

	return 1;
}
