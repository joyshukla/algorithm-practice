/* psudo code
find SCC using Tarjans
for each SCC
	create a copy of SATcheck bitmap with size of numOfVars
	for every node in SCC
		if abs(nodeValue) = 1
			notSatisfiable
		else
			SATcheck[abs(nodeValue)] = 1
	// essentially check if we are trying to set the SATcheck bitmap 2nd time
*/

#include <iostream>
#include <stack>
#include "time.h"
#include <algorithm>
using namespace std;

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

struct TarjansNode
{
	int index;
	int lowlink;
	bool onstack;
};

TarjansNode *TarjansList;
stack<int> ts;
int c_index;

int *arrayMap;
//bool containsDuplicates = false;
bool notSatisfiable = false;
int *SATcheck;
int numOfvars;

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
	}


	// adding an edge (u, v) between vertices u and v   
	void addNewEdge(int u, int v) {
		// insert a new node with value v at index u of array
		ListNode* newNode1 = new ListNode();
		newNode1->value = v;
		newNode1->next = array[u].head;
		array[u].head = newNode1;

		if (type == "undirected") {
			// insert a new node with value u at index v of array
			ListNode* newNode2 = new ListNode();
			newNode2->value = u;
			newNode2->next = array[v].head;
			array[v].head = newNode2;
		}
	}

	// retrieve ListNode head at given index from adjacency list
	ListNode* getAdjListHead(int index) {
		return array[index].head;
	}

	// print out the graph
	void print()
	{
		cout << "Displaying adjacency list of graph(index) " << endl;
		for (int j = 0; j < numberOfVertices; j++) {
			ListNode* start = array[j].head;
			cout << "| " << j << " |";
			while (start != NULL) {
				cout << start->value << ",";
				start = start->next;
			}
			cout << endl;
		}
		cout << "Displaying adjacency list of graph(node value) " << endl;
		for (int j = 0; j < numberOfVertices; j++) {
			ListNode* start = array[j].head;
			cout << "| " << arrayMap[j] << " |";
			while (start != NULL) {
				cout << arrayMap[start->value] << ",";
				start = start->next;
			}
			cout << endl;
		}

	}
};

int min(int a, int b)
{
	return (a > b) ? b : a;
}

void StrongConnect(int v, Graph myGraph)
{
	// Set the depth index for v to the smallest unused index
	TarjansList[v].index = c_index;
	TarjansList[v].lowlink = c_index;
	c_index++;
	ts.push(v);
	TarjansList[v].onstack = true;

	ListNode *ptr = myGraph.getAdjListHead(v);
	// Consider successors of v

	while (ptr != NULL)
	{
		int w = ptr->value;
		if (TarjansList[w].index == 0)
		{
			// Successor w has not yet been visited; recurse on it
			StrongConnect(w, myGraph);
			TarjansList[v].lowlink = min(TarjansList[v].lowlink, TarjansList[w].lowlink);
		}
		else if (TarjansList[w].onstack)
		{
			// Successor w is in stack S and hence in the current SCC
			TarjansList[v].lowlink = min(TarjansList[v].lowlink, TarjansList[w].index);
		}
		ptr = ptr->next;
	}

	// If v is a root node, pop the stack and generate an SCC
	if (TarjansList[v].lowlink == TarjansList[v].index)
	{
		cout << "new SCC : ";
		int SCC_Elements[10];
		SATcheck = new int[numOfvars];
		int rn;
		int i = 0;
		do
		{
			rn = ts.top();
			TarjansList[rn].onstack = false;
			ts.pop();
			cout << rn << "(" << arrayMap[rn] << ") ";
			SCC_Elements[i++] = abs(arrayMap[rn]);
			int nodeValue = arrayMap[rn];
			if (SATcheck[abs(nodeValue)] == 1)
			{
				notSatisfiable = true;
			}
			else
			{
				SATcheck[abs(nodeValue)] = 1;
			}

		} while (rn != v);
		cout << endl;


		//int *end = SCC_Elements + i;
		//std::sort(SCC_Elements, end);
		//containsDuplicates = (std::unique(SCC_Elements, end) != end);

	}
}

int map(int x, int numOfvars)
{
	if (x < 0)
	{
		return (-x) + numOfvars - 1;
	}
	else
	{
		return x - 1;
	}
}

int main()
{

	//int inputArray[] = { 3, 2, 1, 2, -2, 3 };
	//int inputArray[] = { 3, 4, -1, 2, -2, 3, 1, -3, 3, 2 };
	int inputArray[] = { 2, 4, 1, 2, -1, 2, 1, -2, -1, -2 };


	numOfvars = inputArray[0];
	int numOfclauses = inputArray[1];

	int numVertices = numOfvars * 2; 

	int *visited = new int[numVertices];
	TarjansList = new TarjansNode[numVertices];

	for (int i = 0; i < numVertices; i++) {
		visited[i] = 0;
	}

	for (int i = 0; i < numVertices; i++) {
		TarjansList[i].index = 0;
		TarjansList[i].lowlink = 0;
		TarjansList[i].onstack = false;
	}

	arrayMap = new int[numVertices];

	for (int i = 0; i < numOfvars; i++)
	{
		arrayMap[i] = i + 1;
	}
	int j = 1;
	for (int i = numOfvars; i < 2*numOfvars; i++)
	{
		arrayMap[i] = -j++;
	}
	cout << "array map" << endl;
	for (int i = 0; i < numVertices; i++)
	{
		cout << i << " -> " << arrayMap[i] << endl;
	}

	// in AdjList* array, maping will be as below
	// any positive value node will be indexed as
	// index = value - 1

	// any negative value node will be indexed as
	// index = numOfvars + value - 1

	Graph myGraph(numVertices, "directed");

	for (int i = 2; i < sizeof(inputArray)/sizeof(int); i=i+2)
	{
		// (X ^ Y) = (-X -> Y) ^ (-Y -> X)
		int a = map(inputArray[i], numOfvars);
		int b = map(inputArray[i+1], numOfvars);
		int na = map(-inputArray[i], numOfvars);
		int nb = map(-inputArray[i+1], numOfvars);


		myGraph.addNewEdge(na, b);
		myGraph.addNewEdge(nb, a);
	}

	myGraph.print();

	c_index = 1;

	for (int v = 0; v < numVertices; v++)
	{
		if (TarjansList[v].index == 0)
		{
			if (!notSatisfiable)
				StrongConnect(v, myGraph);
		}
	}

	if (notSatisfiable)
		cout << "2 - SAT not satisfiable!!!" << endl;
	else
		cout << "2 - SAT satisfiable!!!" << endl;

	getchar();
	return 0;
}
