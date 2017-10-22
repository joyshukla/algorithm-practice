#include<iostream>
#include<deque>
using namespace std;

bool pelindrome(std::deque<char> myDeque)
{
	while(myDeque.size() > 1)
	{
		cout << myDeque.front() << " <-> " << myDeque.back() << endl;
		if (myDeque.front() != myDeque.back())
			return false;
		myDeque.pop_front();
		myDeque.pop_back();
	}
	return true;
}



int main()
{
	//std::deque<char> myDeque({'r','a','d','a','r'});
	std::deque<char> myDeque({'d'});
	
	cout << pelindrome(myDeque) << endl;
		
	return 1;

}
