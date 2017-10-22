// pseudo code
//
// for each element in array
// 		map[value] += 1
//
// for each key in the map
// 		multimap.insert(map.value,map.key)
// 
// this creates the output


#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
using namespace std;

// P.S. these are clocks not seconds
//	inputSize	time(clocks)
//	100			0
//	500			0
//	1000		0
//	5000		0
//	10000		15
//	50000		31
//	100000		62
//	500000		281
//	1000000		500	

#define INPUT_ARRAY_SIZE 10000
#define MAX_VAL 100

//int input[] = {4,5,2,3,3,4,5,4,4,5,6,1,7};

int *input;

std::multimap<int,int> huffmanMap;

void random_array(void)
{
	input = new int[INPUT_ARRAY_SIZE];

	srand((unsigned)time(0));

	for (int i = 0; i<INPUT_ARRAY_SIZE; i++)
	{
		input[i] = (rand() % MAX_VAL) + 1;

		//cout << input[i] << endl;
	}
}

void huffman(void)
{
	std::map<int,int> myMap;

	for(int i=0; i < INPUT_ARRAY_SIZE; i++)
	{
		if(myMap.count(input[i]) == 0)
			myMap[input[i]] = 1;
		else
			myMap[input[i]] += 1;
	}

	cout << endl;
	cout << "val\tfreq" << endl;
	for (map<int,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it)
	{
		//cout << it->first << "\t" << it->second << endl;	
		huffmanMap.insert(pair<int, int>(it->second, it->first));
	}
}

int main()
{
	clock_t startTime, endTime;
	random_array();
	cout << "created random input (" << INPUT_ARRAY_SIZE << "): " << endl;
	for(int i=0; i < INPUT_ARRAY_SIZE; i++)
	{
		cout << input[i] << " ";
	}
	cout << endl;

	startTime = clock();
	huffman();
	endTime = clock();

	cout << endl;
	cout << "huffman codes: sorted by freq" << endl;
	//cout << "freq\tval" << endl;
	for (map<int,int>::iterator it = huffmanMap.begin(); it != huffmanMap.end(); ++it)
	{
		cout << it->second << endl;
	}

	cout << endl;

	cout << "startTime = " << startTime << endl;
	cout << "endTime = " << endTime << endl;
	double huffman_time = ((double)(endTime - startTime)); // / (CLOCKS_PER_SEC/1000);

	cout << "huffman time: " << huffman_time << " clocks" << endl;
	//getchar();

	return 0;
}
