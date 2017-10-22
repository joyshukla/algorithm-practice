//
// pseudo code
// create a vector of numbers from 1 to n^2, 
// 	i.e. all possible values in a magic square
//
// traverse through the magic square and remove all non-zero values 
//  from the vector
// this will result in a vector of values which were not there in the input square 
//
// generate permutations of all the possible values
// 
// for all permutations
// 		insert them in the magic square
// 		validate magic square
// 		stop when valid magic square is found
//
// with exhaustive search, this is solvable but as input size increase
// i.e. for matrix 5x5 and 6x6 it will take long time so non polynomial time
//
// there are possible improvements by ignoring some obvious permutations which wont work
// 
// But the verdict is the conjucture is incorrect as per exhaustive search algorithm


// pseudo code for validate magic square
// 
// 		get first raw sum
// 		check all raw's sum against first raw sum
// 		check all column's sum against first raw sum
// 		check both diagonal's sum agaist first raw sum
//
// 		if any of the check fails, return invalid

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

#define SIZE 4

/*
// a input that will run n^2 permutations
int input[SIZE][SIZE] = { {0,4,10,0},
						  {0,6,3,0},
						  {5,2,1,0},
						  {0,0,0,7} };
*/

// a good input which will find a valid magic square
int input[SIZE][SIZE] = { {15,10,0,0},
						  {4,0,16,9},
						  {0,11,0,0},
						  {1,8,0,0} };

// for testing
int magic_square[SIZE][SIZE] = { {15,10,3,6},
								 {4,5,16,9},
								 {14,11,2,7},
								 {1,8,13,12} };


void display(int matrix[][SIZE])
{
	for(int i=0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
			cout << matrix[i][j] << "\t";
   		cout << endl;	
	}
}

bool validate(int matrix[][SIZE])
{

	// check both diagonals total
	int check = 0;

	// check all rows total 
	for(int i=0; i < SIZE; i++)
	{
		int sum = 0;
		for(int j=0; j < SIZE; j++) 
		{
			sum += matrix[i][j];
		}
		if (check == 0)
		{
			check = sum;
			cout << "check_sum = " << check << endl;
		}
		else
		{
			if(sum != check)
			{
				cout << "raw check FAILED. raw(" << i << ").sum = " << sum << endl;
				return false;
			}
		}
	}

	cout << "raw check PASSED. check_sum = " << check << endl;
	
	// check all columns total
	for(int j=0; j < SIZE; j++)
	{
		int sum = 0;
		for(int i=0; i < SIZE; i++) 
		{
			sum += matrix[i][j];
		}
		if (sum != check)
		{
			cout << "column check FAILED. column(" << j << ").sum = " << sum << endl;
			return false;
		}
	}

	cout << "column check PASSED. check_sum = " << check << endl;

	// left diag
	int sum = 0;
	for(int i=0; i < SIZE; i++)
	{
		sum += matrix[i][i];
	}
	if(sum != check)
	{
		cout << "left diag check FAILED. left Diag Sum = " << sum << endl;
		return false;
	}

	// right diag
	sum = 0;
	for(int i=0; i < SIZE; i++)
	{
		sum += matrix[i][SIZE - 1 - i];
	}
	if(sum != check)
	{
		cout << "right diag check FAILED. right Diag Sum = " << sum << endl;
		return false;
	}
	cout << "Diagonal check PASSED. check_sum = " << check << endl;

	return true;
}

int main()
{
	cout << "input magic square:" << endl;
	display(input);

	int blanks[SIZE*SIZE];
	for(int i=0; i <= SIZE*SIZE; i++)
		blanks[i] = i+1;

	std::vector<int> possible_values (blanks, blanks + SIZE*SIZE);  

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			possible_values.erase(std::remove(possible_values.begin(), possible_values.end(), input[i][j]), possible_values.end());
		}
	}
	//possible_values.shrink_to_fit(); // doesnt work in g++
	std::vector<int>(possible_values).swap(possible_values);

	// print possible values
	cout << "possible values : ";
	for(int i=0; i < possible_values.capacity(); i++)
		cout << possible_values[i] << " ";
	cout << endl;
	
	cout << endl;

	// find all permutations
	// just 3 for now
	int iter = 0; 
	do{
		cout << endl << "trying permutation <" << iter << "> : " << endl;
		for(int i=0; i < possible_values.capacity(); i++)
			cout << possible_values[i] << " ";
		cout << endl;

		int candidate[SIZE][SIZE];

		for(int i=0,k=0; i < SIZE; i++)
		{
			for(int j=0; j < SIZE; j++)
			{
				if(input[i][j] != 0)
					candidate[i][j] = input[i][j];
				else
					candidate[i][j] = possible_values[k++];
			}
		}
		
		cout << "matrix after plugging in values : " << endl;	
		display(candidate);

		bool result = validate(candidate);	

		if(result)
			cout << "Valid Magic Square" << endl;
		else
			cout << "Not a valid Magic Square" << endl;
		iter++;
		//if ( result || ( iter > 50) )
		if ( result )
			break;
	}while(std::next_permutation(&possible_values[0],&possible_values[0] + possible_values.capacity()));

/*
	// check valid magic square
	cout << "testing validate function using valid magic square." << endl;	
	display(magic_square);
	bool result = validate(magic_square);

	if(result)
		cout << "Valid Magic Square" << endl;
	else
		cout << "Not a valid Magic Square" << endl;
*/
	return 0;
}
