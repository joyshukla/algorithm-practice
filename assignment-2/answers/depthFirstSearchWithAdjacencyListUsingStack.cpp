// Copyright 2017 SPEL Technologies, Inc.
// Depth first search of a graph using a stack. The graph is stored using an adjacency list.
// MIT License

#include <iostream>
#include <stack>
using namespace std;
#define NUM_VERTICES 8

// define Data according to requirements
typedef struct data {
    int id;
} Data;

// a node in the queue.
struct Node {
    Data* value;
    struct Node *next;
};

static int c_time = 0;

// C++ program to implement adjacency list for directed and undirected graphs

#include <iostream>
#include <cstring>
using namespace std;
 
// adjacency list node
struct ListNode
{
    int value;
    struct ListNode* next;
    int visited; // used in BFS
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
            array = new AdjList [numVertices];
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
            
            for (int j = 0; j < numberOfVertices; j++) {
                ListNode* start = array[j].head;
                cout << "| " << j << " |" ;
                while (start != NULL) {
                    cout << start->value << ",";
                    start = start->next;
                }
                cout << endl;
            }
                 
        }
};
 

void depthFirstSearch(int id, Graph myGraph, int *visited, int *discoveryTime, int *finishTime) {    
        stack<int> s1;
        visited[id] = 1; // set vertex s to visited
        s1.push(id);
		discoveryTime[id] = c_time++;

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
                       cout << "Adjacent vertex v of node with id " << s_id << " is " << v_id << " visited " << visited[v_id] <<  endl;


                       visited[v_id] = 1;
                       s1.push(v_id);
                       unVisitedNodeFound = 1;  
					   // JS record discover time here
					   cout << "d(" << v_id << ") = " << c_time << endl; 
					   discoveryTime[v_id] = c_time++;


                   }
                   else {
                       ptr = ptr->next;
				   }
               }
              } while ((ptr != NULL) && (unVisitedNodeFound == 0));


              
           
                if (unVisitedNodeFound == 0) // vertex at top of stack has no unvisited neighbors, pop this vertex
				{
					// JS record finish time here

					cout << "f(" << s_id << ") = " << c_time << endl; 
					finishTime[s_id] = c_time++;

				  	s1.pop();
           		}

       }
}


int main()
{
   
    int numVertices = NUM_VERTICES;
    int *visited = new int[numVertices];
	int *discoveryTime = new int[numVertices];
    int *finishTime = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < numVertices; i++) {
        discoveryTime[i] = -1;
    }
    for (int i = 0; i < numVertices; i++) {
        finishTime[i] = -1;
    }


    Graph myGraph(numVertices, "undirected");
    myGraph.addNewEdge(0, 0);
    myGraph.addNewEdge(1, 4);
    myGraph.addNewEdge(1, 2);
    myGraph.addNewEdge(2, 7);
    myGraph.addNewEdge(2, 4);
    myGraph.addNewEdge(3, 4);
    myGraph.addNewEdge(3, 5);
    myGraph.addNewEdge(4, 5);
    myGraph.addNewEdge(5, 6);
    myGraph.print();
    
    int s_id = 1;
    depthFirstSearch(s_id, myGraph, visited, discoveryTime, finishTime);
	
	for (int i = 0; i < numVertices; i++) {
        if (visited[i] == 0) {
            cout << "Visiting unexplored vertex " << i << endl;
           depthFirstSearch(i, myGraph, visited, discoveryTime, finishTime);
        }
    }
	
	cout << "n |\td\tf" << endl;
	cout << "--------------------" << endl;
	// print discover and finish time here
	for (int j = 0; j < numVertices; j++) {
		cout << j << " |\t" << discoveryTime[j] << "\t" << finishTime[j];	
		cout << endl;
	}

    return 0;
}
