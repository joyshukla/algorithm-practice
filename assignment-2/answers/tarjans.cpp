#include <iostream>
#include <stack>
#include "time.h"
using namespace std;


#define NUM_VERTICES 9

int numVertices = NUM_VERTICES;
int *finishingTime; // time when a vertex has been explored fully
int *discoveryTime; // time when a vertex is discovered (i.e. visited first)

int c_index = 0;

struct TarjansNode
{
	int index;
	int lowlink;
	bool onstack;

};

TarjansNode *TarjansList;
stack<int> ts; 




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
		for (int i = 1; i < numVertices; i++)
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
		for (int j = 1; j < numberOfVertices; j++) {
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


// performs a depth first search of myGraph starting with given vertex id (s_id)
// visited stores whether a vertex has been discovered
// time when a vertex is discovered (c_time) is recorded in array discoveryTime
// time when  vertex has been fully explored is recorded in array finishingTime
void depthFirstSearch(int s_id, Graph myGraph, int *visited, int *c_time) {

	stack<int> s1;  // this stack is used to store the vertices for the dfs of vertex s_id

	visited[s_id] = 1; // set starting vertex s to visited and push into stack
	s1.push(s_id);
	discoveryTime[s_id] = ++(*c_time); // set discovery time of starting vertex to 0

	TarjansList[s_id].index = ++c_index;
	TarjansList[s_id].lowlink = c_index;
	TarjansList[s_id].onstack = true;
	ts.push(s_id);



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
					s1.push(v_id);
					discoveryTime[v_id] = ++(*c_time);

					TarjansList[v_id].index = ++c_index;
					TarjansList[v_id].lowlink = c_index;
					TarjansList[v_id].onstack = true;
					ts.push(v_id);


					unVisitedNodeFound = 1;
				}
				else
					ptr = ptr->next;
			}
		} while ((ptr != NULL) && (unVisitedNodeFound == 0));



		// there is no unvisited vertex adjacent to s, pop s
		if (unVisitedNodeFound == 0) {
			int temp_id = s1.top(); // or use s_id instead of temp_id
			finishingTime[temp_id] = ++(*c_time);
			cout << "pop node with id " << temp_id << " finishing time " << finishingTime[temp_id] << endl;


			s1.pop();

			
			if (TarjansList[temp_id].index == TarjansList[temp_id].lowlink)
			{
				cout << "new SCC : ";
				while (ts.top() != temp_id)
				{
					cout << ts.top();
					TarjansList[ts.top()].onstack = false;
					ts.pop();
				}

				// one more time 
				cout << ts.top();
				TarjansList[ts.top()].onstack = false;
				ts.pop();

				cout << endl;

			}
		}

	}

}


int main()
{

	int *visited = new int[numVertices];
	finishingTime = new int[numVertices];
	discoveryTime = new int[numVertices];
	TarjansList = new TarjansNode[numVertices];
	
	for (int i = 1; i < numVertices; i++) {
		visited[i] = 0;
	}

	for (int i = 1; i < numVertices; i++) {
		TarjansList[i].index = 0;
		TarjansList[i].lowlink = 0;
		TarjansList[i].onstack = false;
	}

	Graph myGraph(numVertices, "directed");

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


	myGraph.print();


	int s_id = 1;
	int c_time = -1;
	depthFirstSearch(s_id, myGraph, visited, &c_time);

	// Visiting unexplored vertex
	for (int i = 1; i < numVertices; i++) {
		if (visited[i] == 0) {
			cout << "Visiting unexplored vertex " << i << endl;
			depthFirstSearch(i, myGraph, visited, &c_time);
		}
	}



	cout << "n |\td\tf" << endl;
	cout << "--------------------" << endl;
	// print discover and finish time here
	for (int j = 1; j < numVertices; j++) {
		cout << j << " |\t" << discoveryTime[j] << "\t" << finishingTime[j];
		cout << endl;
	}
	cout << endl;
	cout << endl;

	cout << "n |\tindex\tlowlink\tonstack" << endl;
	cout << "------------------------------------" << endl;
	// print discover and finish time here
	for (int j = 1; j < numVertices; j++) {
		cout << j << " |\t" << TarjansList[j].index << "\t" << TarjansList[j].lowlink << "\t" << TarjansList[j].onstack;
		cout << endl;
	}

	char tmp = getchar();
	return 0;
}