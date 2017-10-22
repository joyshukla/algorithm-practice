#include<iostream>
#include<algorithm>
#include<array>
using namespace std;

bool sumOf(array<int, 7> data, int num)
{
	// sort the array
	sort(data.begin(),data.end());

	for(const auto &elem: data)
		cout << elem << endl;
	
	int i = 0;
	int j = data.size() - 1;
	int sum;
	bool found = false;

	while(i< j)
	{
		sum = data.at(i) + data.at(j);
		cout << data.at(i) << " + " << data.at(j) << " = " << sum << endl;
		if(sum > num)
			j--;
		else if(sum < num)
			i++;
		else
			found = true;	
	}
	return found;
}


int main()
{	
	array<int, 7> data({8,5,3,4,6,5,7});
	
	bool res = sumOf(data, 20);
	if(res)
		cout << "match found!";
	



	return 1;
}
