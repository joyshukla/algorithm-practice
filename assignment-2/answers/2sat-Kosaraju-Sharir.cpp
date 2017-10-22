/* psudo code
find SCC using Kosaraju-Sharir
for each SCC
	create a copy of SATcheck bitmap with size of numOfVars
	for every node in SCC
	if abs(nodeValue) = 1	
		notSatisfiable
	else
		SATcheck[abs(nodeValue)] = 1
	// essentially check if we are trying to set the SATcheck bitmap 2nd time
*/

// similarly I have also implemented 2-SAT using Kosaraju-Sharir to find SCC.
// it works the same way, just uses Kosaraju-Sharir to find SCC instead of Tarjans.
// was not able to compare execution times due to lack of enough inputs and clock() function not working

// although, it is clear that Kosaraju-Sharir implementation will take much longer than Tarjans
// for Kosaraju-Sharir, we need to do DFS for 2 times (1 + until we find SCC which has element and its complement)
// on the other hand for Tarjans, we just need to do DFS until we find SCC which has element and its complement in the first run itself 

#include <iostream>
#include <stack>
#include "time.h"
#include <algorithm>
using namespace std;

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

int *arrayMap;
//bool containsDuplicates = false;
bool notSatisfiable = false;
int *SCC_Elements;
int *SATcheck;

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


// performs a depth first search of myGraph starting with given vertex id (s_id)
// visited stores whether a vertex has been discovered
// time when a vertex is discovered (discovery_time) is recorded in array discoveryTime
// time when  vertex has been fully explored is recorded in array finishingTime
void depthFirstSearch(int s_id, Graph myGraph, int *visited, int discovery_time, bool findingSCC) {

	stack<int> s1;  // this stack is used to store the vertices for the dfs of vertex s_id

	visited[s_id] = 1; // set starting vertex s to visited and push into stack
	s1.push(s_id);
	discoveryTime[s_id] = 0; // set discovery time of starting vertex to 0
	int SCCCount = 0;
	if (findingSCC)
	{
		SCC_Elements[SCCCount++] = s_id;
		int nodeValue = arrayMap[s_id];
		if (SATcheck[abs(nodeValue)] == 1)
		{
			notSatisfiable = true;
		}
		else
		{
			SATcheck[abs(nodeValue)] = 1;
		}
	}
	while (!s1.empty()) {
		// check the id of first vertex s on stack
		int s_id = s1.top();

		cout << "DFS of Node with id " << s_id << endl;

		// find first unvisited vertex v adjacent to s in adjacency list
		ListNode *ptr = myGraph.getAdjListHead(s_id);
		int unVisitedNodeFound = 0; //  set this to 1 if an unvisited vertex v is found

		do {

			if (ptr != NULL) {
				int v_id = ptr->value;
				if (visited[v_id] == 0) {
					cout << "Adjacent vertex v of node with id " << s_id << " is " << v_id << " visited " << visited[v_id] << endl;


					visited[v_id] = 1;
					if (findingSCC)
					{
						SCC_Elements[SCCCount++] = v_id;
						int nodeValue = arrayMap[v_id];
						if (SATcheck[abs(nodeValue)] == 1)
						{
							notSatisfiable = true;
						}
						else
						{
							SATcheck[abs(nodeValue)] = 1;
						}
					}
					s1.push(v_id);
					discoveryTime[v_id] = ++discovery_time;

					unVisitedNodeFound = 1;
				}
				else
					ptr = ptr->next;
			}
		} while ((ptr != NULL) && (unVisitedNodeFound == 0));



		// there is no unvisited vertex adjacent to s, pop s
		if (unVisitedNodeFound == 0) {
			int temp_id = s1.top(); // or use s_id instead of temp_id
			finishingTime[temp_id] = ++discovery_time;
			cout << "pop node with id " << temp_id << " finishing time " << finishingTime[temp_id] << endl;


			s1.pop();
			s2.push(temp_id);
		}

	}

}

//returns the transpose of the Graph G
Graph* transpose(Graph* G, int numVertices) {
	// create the transpose of graph G
	Graph* GT = new Graph(numVertices, "directed");

	// iterate over the array
	for (int i = 0; i < numVertices; i++) {
		ListNode *start = G->getAdjListHead(i);

		cout << "| " << i << " |";
		while (start != NULL) {
			cout << start->value << ",";
			GT->addNewEdge(start->value, i);
			start = start->next;
		}
	}
	cout << endl << "Transpose:" << endl;
	GT->print();
	return GT;
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
	//int inputArray[] = { 3,3,2,1,-1,3,-2,3 };  // 3 inputs, 3 clauses

	int numOfvars = inputArray[0];
	int numOfclauses = inputArray[1];

	int numVertices = numOfvars * 2;
	int *visited = new int[numVertices];
	finishingTime = new int[numVertices];
	discoveryTime = new int[numVertices];

	for (int i = 0; i < numVertices; i++) {
		visited[i] = 0;
	}


	arrayMap = new int[numVertices];

	for (int i = 0; i < numOfvars; i++)
	{
		arrayMap[i] = i + 1;
	}
	int j = 1;
	for (int i = numOfvars; i < 2 * numOfvars; i++)
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

	for (int i = 2; i < sizeof(inputArray) / sizeof(int); i = i + 2)
	{
		// (X ^ Y) = (-X -> Y) ^ (-Y -> X)
		int a = map(inputArray[i], numOfvars);
		int b = map(inputArray[i + 1], numOfvars);
		int na = map(-inputArray[i], numOfvars);
		int nb = map(-inputArray[i + 1], numOfvars);


		myGraph.addNewEdge(na, b);
		myGraph.addNewEdge(nb, a);
	}

	myGraph.print();

	// start dfs now
	int s_id = 1;
	depthFirstSearch(s_id, myGraph, visited, 0, false);


	for (int i = 0; i < numVertices; i++) {
		if (visited[i] == 0) {
			cout << "Visiting unexplored vertex " << i << endl;
			depthFirstSearch(i, myGraph, visited, 0, false);
		}
	}


	Graph* gt = transpose(&myGraph, numVertices);


	for (int i = 0; i < numVertices; i++) {
		visited[i] = 0;
	}

	while (!s2.empty()) {
		// if SCC which has element and its complement is found, break this while loop
		if (notSatisfiable)
			break;

		s_id = s2.top();


		discoveryTime[s_id] = 0;
		s2.pop();
		if (!visited[s_id]) {
			cout << "Finding a SCC for id " << s_id << endl;
			cout << "----------------------- " << endl;
			SCC_Elements = new int[10];
			for (int i = 0; i < 10; i++)
				SCC_Elements[i] = -1;
			SATcheck = new int[numOfvars];

			// every dfs finds an SCC here
			depthFirstSearch(s_id, *gt, visited, 0, true);
			cout << endl;
			cout << "new SCC : ";
			int i;
			for (i = 0; i < 10; i++)
			{
				if (SCC_Elements[i] == -1)
					break;
				cout << SCC_Elements[i] << "(" << arrayMap[SCC_Elements[i]] << ") ";
				// apply mapping and take absolute value of it
				//SCC_Elements[i] = abs(arrayMap[SCC_Elements[i]]);
			}
			cout << endl;

			// i will have the last uninitialized(not -1) element
			//int *end = SCC_Elements + i;
			//std::sort(SCC_Elements, end);
			//containsDuplicates = (std::unique(SCC_Elements, end) != end);
		}
	}

	cout << endl;

	if (notSatisfiable)
		cout << "2 - SAT not satisfiable!!!" << endl;
	else
		cout << "2 - SAT satisfiable!!!" << endl;

	getchar();
	return 0;
}