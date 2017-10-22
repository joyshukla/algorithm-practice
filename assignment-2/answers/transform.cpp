/*
to transpose a graph in adjacency list,
	go through every edge and add new edge in the new graph
to transpose a graph in adjacency matrix,
	apply the matrix transpose operation
*/

#include <iostream>
#include <stack>
#include "time.h"
using namespace std;

#define NUM_VERTICES 9

int numVertices = NUM_VERTICES;
int *finishingTime; // time when a vertex has been explored fully
int *discoveryTime; // time when a vertex is discovered (i.e. visited first)
stack<int> s2; // stores the vertices in descending order of finishing times



			   // adjacency list node
struct ListNode
{
	int value;
	struct ListNode* next;
};

// adjacency list
struct AdjList
{
	struct ListNode *head;
};

int** AdjMatrix;

// graph 
class Graph {

private:
	int numberOfVertices;
	struct AdjList* array;
	string type; // may be directed or undirected

public:
	Graph(int numVertices, string graph_type) {
		numberOfVertices = numVertices;
		type = graph_type;
		array = new AdjList[numVertices];
		for (int i = 0; i < numVertices; i++)
			array[i].head = NULL;

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
		ListNode* newNode1 = new ListNode();
		newNode1->value = v;
		newNode1->next = array[u].head;
		array[u].head = newNode1;
		AdjMatrix[u][v] = 1;

		if (type == "undirected") {
			// insert a new node with value u at index v of array
			ListNode* newNode2 = new ListNode();
			newNode2->value = u;
			newNode2->next = array[v].head;
			array[v].head = newNode2;

			AdjMatrix[u][v] = 1;
			AdjMatrix[v][u] = 1;
		}
	}

	// retrieve ListNode head at given index from adjacency list
	ListNode* getAdjListHead(int index) {
		return array[index].head;
	}

	// print out the graph
	void print()
	{
		cout << "Displaying adjacency list of graph " << endl;
		for (int j = 0; j < numberOfVertices; j++) {
			ListNode* start = array[j].head;
			cout << "| " << j << " |";
			while (start != NULL) {
				cout << start->value << ",";
				start = start->next;
			}
			cout << endl;
		}

		cout << "Displaying Adjacancy Matrix of graph" << endl;
		cout << "    ";
		for (int ii = 0; ii < numberOfVertices; ii++) {
			cout << ii;
			cout << "  ";
		}
		cout << endl;
		cout << "--------------------------";
		cout << endl;
		for (int ii = 0; ii < numberOfVertices; ii++) {
			cout << ii;
			cout << " | ";
			for (int jj = 0; jj < numberOfVertices; jj++) {
				cout << AdjMatrix[ii][jj];
				cout << "  ";
			}
			cout << endl;
		}


	}
};


//returns the transpose of the Graph G
Graph* transpose(Graph* G) {
	// create the transpose of graph G
	Graph* GT = new Graph(numVertices, "directed");

	// iterate over the array
	for (int i = 0; i < numVertices; i++) {
		ListNode *start = G->getAdjListHead(i);

		while (start != NULL) {
			GT->addNewEdge(start->value, i);
			start = start->next;
		}
	}
	cout << endl << "Transpose:" << endl;
	GT->print();
	return GT;
}


void matrixTranspose(int **src, int **dst, const int N, const int M) {
	for (int ii = 0; ii < N; ii++)
	{
		for (int jj = 0; jj < M; jj++)
		{
			dst[ii][jj] = src[jj][ii];
		}
	}
}




int main()
{

	int *visited = new int[numVertices];
	finishingTime = new int[numVertices];
	discoveryTime = new int[numVertices];

	for (int i = 0; i < numVertices; i++) {
		visited[i] = 0;
	}

	Graph myGraph(numVertices, "directed");

	myGraph.addNewEdge(0, 4);
	myGraph.addNewEdge(0, 1);
	myGraph.addNewEdge(1, 2);
	myGraph.addNewEdge(1, 4);
	myGraph.addNewEdge(2, 5);
	myGraph.addNewEdge(2, 2);
	myGraph.addNewEdge(3, 6);
	myGraph.addNewEdge(3, 1);
	myGraph.addNewEdge(4, 3);
	myGraph.addNewEdge(5, 7);
	myGraph.addNewEdge(6, 4);
	myGraph.addNewEdge(7, 8);
	myGraph.addNewEdge(8, 5);

	myGraph.print();

	Graph* gt = transpose(&myGraph);

	int** AdjMatrixTr;
	AdjMatrixTr = new int *[numVertices];
	for (int kk = 0; kk < numVertices; kk++)
		AdjMatrixTr[kk] = new int[numVertices];

	for (int ii = 0; ii < numVertices; ii++)
		for (int jj = 0; jj < numVertices; jj++)
			AdjMatrixTr[ii][jj] = 0;

	matrixTranspose(AdjMatrix, AdjMatrixTr, 9, 9);
	AdjMatrix = AdjMatrixTr;



	getchar();
	return 0;
}