// Copyright 2017 SPEL Technologies, Inc.
// Kosaraju-Sharir algorithm for finding strongly connected components
// Performs depth first search of a graph G and its transpose using a stack. The graph is stored using an adjacency list.
// Sample output: Finding a SCC for id 3
// DFS of node with id 3
// ...
// DFS of node with id 5
// ...
// DFS of node with id 4
// Solution: The SCC is (3, 4, 5)
// Update NUM_VERTICES when the graph is modified
// MIT License


#include <iostream>
#include <stack>
#include "time.h"
using namespace std;

#define NUM_VERTICES 9

int numVertices = NUM_VERTICES;
int *finishingTime; // time when a vertex has been explored fully
int *discoveryTime; // time when a vertex is discovered (i.e. visited first)
stack<int> s2; // stores the vertices in descending order of finishing times

// define Data according to requirements
typedef struct data {
    int id;
    int distance;
    int predecessor;
} Data;

// a node in the queue.
struct Node {
    Data* value;
    struct Node *next;
};


 
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

	   int getAdjMatrixHead(int index) {
	   	  for(int k=0; k <numberOfVertices ; k++)
		  {	
		     if (AdjMatrix[index][k] == 1)
			 {
				 return k;
			 }
		  }
		  return (-1);
	   }

	   int getAdjMatrixNextNode(int index, int prevNode)
	   {
		   for(int k=prevNode+1; k < numberOfVertices; k++)
		   {
			  if (AdjMatrix[index][k] == 1)
			  {
				  return k;
			  }
		   }	   
		   return (-1);
	   }	   
       
        // print out the graph
        void print()
        {
            cout << "Displaying adjacency list of graph " << endl;
            for (int j = 0; j < numberOfVertices; j++) {
                ListNode* start = array[j].head;
                cout << "| " << j << " |" ;
                while (start != NULL) {
                    cout << start->value << ",";
                    start = start->next;
                }
                cout << endl;
            }
     		cout << "Adjacancy Matrix"	<< endl;
			cout << "    ";
			for (int ii =0; ii < numberOfVertices; ii++) {
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
 
// performs a depth first search of myGraph starting with given vertex id (s_id)
// visited stores whether a vertex has been discovered
// time when a vertex is discovered (discovery_time) is recorded in array discoveryTime
// time when  vertex has been fully explored is recorded in array finishingTime
void depthFirstSearch(int s_id, Graph myGraph, int *visited, int discovery_time) {    
          
        stack<int> s1;  // this stack is used to store the vertices for the dfs of vertex s_id

        visited[s_id] = 1; // set starting vertex s to visited and push into stack
        s1.push(s_id);
        discoveryTime[s_id] = 0; // set discovery time of starting vertex to 0
    
        while (!s1.empty()) {
           // check the id of first vertex s on stack
           int s_id = s1.top();

           cout << "DFS of Node with id " << s_id << endl;

           // find first unvisited vertex v adjacent to s in adjacency list
           //ListNode *ptr = myGraph.getAdjListHead(s_id);
		   int v_id = myGraph.getAdjMatrixHead(s_id);
           int unVisitedNodeFound = 0; //  set this to 1 if an unvisited vertex v is found
           
           do {
               
               if (v_id != (-1)) {
                   //int v_id = ptr->value;
                   if (visited[v_id] == 0) {
                       cout << "Adjacent vertex v of node with id " << s_id << " is " << v_id << " visited " << visited[v_id] <<  endl;


                       visited[v_id] = 1;
                       s1.push(v_id);
                       discoveryTime[v_id] = ++discovery_time;

                       unVisitedNodeFound = 1;  
                   }
                   else {
                       v_id = myGraph.getAdjMatrixNextNode(s_id, v_id);
				   }
               }
              } while ((v_id != (-1)) && (unVisitedNodeFound == 0));


              
           // there is no unvisited vertex adjacent to s, pop s
            if (unVisitedNodeFound == 0) { 
                    int temp_id = s1.top(); // or use s_id instead of temp_id
                    finishingTime[temp_id] = ++discovery_time; 
                    cout << "pop node with id " << temp_id << " finishing time " << finishingTime[temp_id] << endl;


                    s1.pop();
                    s2.push(temp_id);
					//s_id = temp_id;
            }
           
       }
       
}

void matrixTranspose(int **src, int **dst, const int N, const int M) {
	for(int ii = 0; ii < N; ii++)
	{
		for(int jj = 0; jj < M; jj++)
		{
			dst[ii][jj] = src[jj][ii];
		}
	}
}


//returns the transpose of the Graph G
Graph* transpose(Graph* G) {
    // create the transpose of graph G
    Graph* GT = new Graph(numVertices, "directed");

    // iterate over the array
    for (int i = 0; i < numVertices ; i++){
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

int main()
{
	clock_t	startTime, endTime;
    int *visited = new int[numVertices];
    finishingTime = new int[numVertices];
    discoveryTime = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }
    
    

    Graph myGraph(numVertices, "directed");
    /*// Test 1
    myGraph.addNewEdge(0, 0);
    myGraph.addNewEdge(4, 1);
    myGraph.addNewEdge(1, 2);
    myGraph.addNewEdge(2, 7);
    myGraph.addNewEdge(2, 4);
    myGraph.addNewEdge(3, 4);
    myGraph.addNewEdge(3, 5);
    myGraph.addNewEdge(4, 5);
    myGraph.addNewEdge(5, 6);

    // Test 2
    myGraph.addNewEdge(2, 1); 
    myGraph.addNewEdge(1, 0);
    myGraph.addNewEdge(0, 2);
    myGraph.addNewEdge(0, 3); 
    myGraph.addNewEdge(3, 4); */

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
   
	startTime = clock();

    int s_id = 1;
    depthFirstSearch(s_id, myGraph, visited, 0);


    for (int i = 0; i < numVertices; i++) {
        if (visited[i] == 0) {
            cout << "Visiting unexplored vertex " << i << endl;
           depthFirstSearch(i, myGraph, visited, 0);
        }
    }
    for (int i = 0; i < numVertices; i++) {
        cout << "discovery time for vertex with id " << i << " is " << discoveryTime[i] << endl;
        cout << "finishing time for vertex with id " << i << " is " << finishingTime[i] << endl;
    }
    
//    Graph* gt = transpose(&myGraph);

	int** AdjMatrixTr;
	AdjMatrixTr = new int *[numVertices];
	for (int kk = 0; kk < numVertices; kk++)
		AdjMatrixTr[kk] = new int[numVertices];

	for (int ii = 0; ii < numVertices; ii++)
		for (int jj = 0; jj < numVertices; jj++)
			AdjMatrixTr[ii][jj] = 0;

	matrixTranspose(AdjMatrix, AdjMatrixTr, 9, 9);
	AdjMatrix = AdjMatrixTr;

	myGraph.print();
    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }
    
    while (!s2.empty() ) {
        
         s_id = s2.top();


        discoveryTime[s_id] = 0;
        s2.pop();
        if (!visited[s_id] ) {
            cout << "Finding a SCC for id " << s_id << endl;
            cout << "----------------------- " << endl;
            depthFirstSearch(s_id, myGraph, visited, 0);
        }
    }

	endTime = clock();

	double totalTimeUsed = ((double)(endTime - startTime)) / (CLOCKS_PER_SEC);

	cout << "CPUtime : " << totalTimeUsed;
    /* for (int i = 0; i < numVertices; i++) {
        cout << "discovery time for vertex with id " << i << " is " << discoveryTime[i] << endl;
        cout << "finishing time for vertex with id " << i << " is " << finishingTime[i] << endl;
    }*/

	getchar();
    return 0;
}
