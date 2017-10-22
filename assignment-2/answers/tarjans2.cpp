#include <iostream>
#include <stack>
#include "time.h"
using namespace std;


#define NUM_VERTICES 9

int numVertices = NUM_VERTICES;
int *finishingTime; // time when a vertex has been explored fully
int *discoveryTime; // time when a vertex is discovered (i.e. visited first)

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

	}
};

int min(int a, int b)
{
	return ( a > b ) ? b : a;
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
		int rn;
		do
		{
			rn = ts.top();
			TarjansList[rn].onstack = false;
			ts.pop();
			cout << rn << " ";
		} while (rn!=v);
		cout << endl;
	}
}


int main()
{

	int *visited = new int[numVertices];
	finishingTime = new int[numVertices];
	discoveryTime = new int[numVertices];
	TarjansList = new TarjansNode[numVertices];

	for (int i = 0; i < numVertices; i++) {
		visited[i] = 0;
	}

	for (int i = 0; i < numVertices; i++) {
		TarjansList[i].index = 0;
		TarjansList[i].lowlink = 0;
		TarjansList[i].onstack = false;
	}

	Graph myGraph(numVertices, "directed");
	
	/*
	myGraph.addNewEdge(1, 2);
	myGraph.addNewEdge(2, 5);
	myGraph.addNewEdge(2, 6);
	myGraph.addNewEdge(2, 7);
	myGraph.addNewEdge(2, 3);
	myGraph.addNewEdge(4, 7);
	myGraph.addNewEdge(5, 1);
	myGraph.addNewEdge(6, 2);
	myGraph.addNewEdge(6, 7);
	myGraph.addNewEdge(7, 3);
	myGraph.addNewEdge(7, 4);
	myGraph.addNewEdge(8, 4);
	*/
	
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

	c_index = 1;

	for (int v = 0; v < numVertices; v++)
	{
		if (TarjansList[v].index == 0)
		{
			StrongConnect(v, myGraph);
		}
	}

	char tmp = getchar();
	return 0;
}