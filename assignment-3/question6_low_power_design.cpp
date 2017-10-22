// pseudo code
// 
// get num_ffs from test_array[0]
//
// for each pair of num_ffs elements from test_array
// 		compare every element to every other elements
// 			add the edge in graph if it is different
//
//
// permutate ffs based on num_ffs
// 	
// for each permutations
// 		calculate cost and print that out
// 		keep track of minimum cost


#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int** AdjMatrix;

// graph 
class Graph {
    
    private:
        int numberOfVertices;
        string type; // may be directed or undirected
    
    public:
        Graph(int numVertices, string graph_type) {
            numberOfVertices = numVertices;
            type = graph_type;

			AdjMatrix = new int *[numVertices];		
			for (int kk = 0; kk < numVertices; kk++)
				AdjMatrix[kk] = new int[numVertices];

			for (int ii = 0; ii < numVertices; ii++)
				for (int jj = 0; jj < numVertices; jj++)
					AdjMatrix[ii][jj] = 0;

        }
    
    
        // adding an edge (u, v) between vertices u and v   
		void addNewEdge(int u, int v) {
			// insert a new node with value v at index u of array

			AdjMatrix[u][v] += 1;
			AdjMatrix[v][u] += 1;
		}
      
        // print out the graph
        void print()
        {
     		cout << "Displaying Adjacancy Matrix of graph"	<< endl;
			cout << "      ";
			for (int ii =0; ii < numberOfVertices; ii++) {
				cout << "FF"<< ii;
				cout << "  ";
			}
			cout << endl;
			cout << "-------------------------";
			cout << endl;
			for (int ii = 0; ii < numberOfVertices; ii++) {
				cout << "FF" << ii;
				cout << " |  ";
				for (int jj = 0; jj < numberOfVertices; jj++) {
					cout << AdjMatrix[ii][jj];
					cout << "    ";
             	}
				cout << endl;
			}
                
        }
};
 
int main()
{
	
	int test_array[] = {3, 1,0,1,
							1,1,0,
							0,1,1,
							0,1,1,
							1,0,1,
							1,1,1
						};
	/*
	int test_array[] = {4, 1,0,1,0,
							1,1,0,1,
							0,1,1,0,
							0,1,1,1,
							1,0,1,1,
							1,1,1,0
						};
	*/
	/*	
	int test_array[] = {5, 1,0,1,0,1,
							1,1,0,1,0,
							0,1,1,0,0,
							0,1,1,1,1,
							1,0,1,1,0,
							1,1,1,0,1
						};
	*/

	// get the number of ffs from test array, position 0
	int num_ffs = test_array[0];

    Graph myGraph(num_ffs, "undirected");
	
	// get the vectors from the array
	for(int i=1; i < sizeof(test_array)/sizeof(int); i+=num_ffs)
	{
		cout << "Processing vector : ";
		for(int p=0; p < num_ffs; p++)
			cout << test_array[i+p] << " ";
		cout << endl;
		//cout << test_array[i] << " " << test_array[i + 1] << " " << test_array[i + 2] << endl;
		for(int j = i ; j < i + num_ffs; j++)
		{
			for (int k = j + 1; k < i + num_ffs; k++)
			{
				cout << "\t(" << j << ")" << test_array[j] << "<>(" << k << ")"<< test_array[k] << endl;
				if (test_array[j] != test_array[k])
					myGraph.addNewEdge((j - 1) % num_ffs, (k - 1) % num_ffs);
			}
		}
	}
	
	cout << endl;
	myGraph.print();

	// initialize ffs array	
	int ffs[num_ffs];
	for(int i=0; i < num_ffs; i++)
		ffs[i] = i;

	cout << endl;	

	int min_cost = 0;	
	cout << "Calculating cost for all permutations:" << endl;
	do
	{
		int cost = 0;
		for(int i=0; i < num_ffs; i++)
			cout << "FF" << ffs[i] << " ";
		cout << " : ";
		for(int i=0; i < num_ffs; i++)
		{
			if(i>0)
			{
				cost += AdjMatrix[ffs[i-1]][ffs[i]];
				cout << AdjMatrix[ffs[i-1]][ffs[i]] << " + " ;
			}
		}
		cout << " = " << cost << endl;
		if((min_cost == 0) || (cost < min_cost))
			min_cost = cost;
	}while(std::next_permutation(ffs,ffs + num_ffs));

	cout << endl;
	cout << "min_cost = " << min_cost << endl;

	return 0;
}
