#include<iostream>
#include<vector>
using namespace std;

void display(vector<int> V)
{
	for(const auto& elem: V)
	{
		cout << elem << " ";
	}
	cout << endl;
}


int main()
{
	vector<int> empty_vector ({});

	// <vector>.front() does not check for empty vector so use caution when 
	// using front method. check for empty 
	if (!empty_vector.empty())
		cout << empty_vector.front() << endl;

	vector<int> vector1 ({100,101,102,103,104});

	display(vector1);
	vector1.push_back(500);
	vector1.resize(10);
	vector1.at(9) = 100;
	cout << "after push_back(50)" << endl;
	display(vector1);

	cout << "print using at" << endl;
	for(int i=0; i< vector1.size(); i++)
	{	
		//cout << vector1[i] << " ";  
		// at is preferred here since it will not go out of bound silently
		cout << vector1.at(i) << " ";
	}

	return 1;
}
