#include<iostream>
#include<algorithm>
#include<array>
using namespace std;


int main()
{
	array<int, 7> data({20,5,20,4,20,5,7});

	// sort in ascending order
	sort(data.begin(),data.end());
	// sort in descending order
	sort(data.begin(),data.end(),greater<int>());
	// other functors like greater
	// less, greater, less_equal, negate, 


	for(const auto &elem: data)
		cout << elem << endl;
	
	return 1;
}
