// pseudo code
// 
// hashmap approach
//		for each element in the array
//			map(element) = Sum - element
//
//		for value in map
//			if the key is present
//				valid pair found, print
//			


// time comparision
// 	input_size	exhaustive	hashmap	
// 	1000		0			0
// 	5000		31			0
// 	10000		156			0
// 	50000		3016		78
// 	100000		11984		157

#include <iostream>
#include <stack>
#include <map>
//#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define INPUT_ARRAY_SIZE 500000

int S = 233;
int *input_array;


bool hashmap(void)
{
	bool result = false;
	std::map<int,int> diff;
	for(int i=0; i < INPUT_ARRAY_SIZE; i++)
	{
		diff[input_array[i]] = S - input_array[i];	// value is the index
	}
	
	for (map<int,int>::iterator it=diff.begin(); it!=diff.end(); ++it)
	{
		int eleToSearch = it->second;
		if (diff.count(eleToSearch) > 0)
		{
			if(it != diff.find(eleToSearch))
			{
				//cout << it->first << ", " << it->second << endl;
				diff.erase(eleToSearch);
				result = true;
			}
		}
	}
	
	return result;
}


bool exhaustive_search(void)
{
	int sum;
	bool result = false;
	for(int i=0; i < INPUT_ARRAY_SIZE; i++)
	{
		for(int j=i+1; j < INPUT_ARRAY_SIZE; j++)
		{
			sum = input_array[i] + input_array[j];
			//cout << "sum of " << input_array[i] << " and " << input_array[j] << " : " << sum << endl;
			if (sum == S)
			{
				//cout << input_array[i] << ", " << input_array[j] << endl;
				result = true;
			}			
		}
	}
	return result;
}

void random_array(int *arr, size_t n)
{
    for (size_t i=0; i<n; i++){
        arr[i] = i;
    }
 
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}


int main()
{
	bool result = false;
	clock_t startTime, endTime;

	input_array = new int[INPUT_ARRAY_SIZE];

	random_array(input_array, INPUT_ARRAY_SIZE);

	
	cout << "input array: ";
	for(int i=0; i < INPUT_ARRAY_SIZE; i++)
	{
		cout << input_array[i] << " ";
	}
	cout << endl;
	
	cout << "S = " << S << endl;	

	cout << endl;
    cout << "exhaustive approach:" << endl;
	startTime = clock();
	result = exhaustive_search();
	endTime = clock();
	cout << "startTime = " << startTime << endl;
	cout << "endTime = " << endTime << endl;
	double exhaustive_search_time = ((double)(endTime - startTime)); // / (CLOCKS_PER_SEC/1000);

	cout << endl;
	if(result)
		cout << "sum exists. " << endl;
	else
		cout << "sum doesnt exist." << endl;

	cout << endl;
    cout << "hashmap approach:" << endl;
	startTime = clock();
	result = hashmap();
	endTime = clock();
	cout << "startTime = " << startTime << endl;
	cout << "endTime = " << endTime << endl;
	double hashmap_time = ((double)(endTime - startTime)); // / (CLOCKS_PER_SEC/1000);

	cout << endl;
	if(result)
		cout << "sum exists. " << endl;
	else
		cout << "sum doesnt exist." << endl;


	cout << endl << "Time comparision:" << endl;

	cout << "exhaustive Search time: " << exhaustive_search_time << " clocks" << endl;
	cout << "hashmap time: " << hashmap_time << " clocks" << endl;
	//getchar();
	return 0;
}
