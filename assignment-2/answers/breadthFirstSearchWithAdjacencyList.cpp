// Copyright 2017 SPEL Technologies, Inc.
// C++ implementation of queue using a linked list; Each node stores generic Data.
// MIT License

#include <iostream>
using namespace std;

// define Data according to requirements
typedef struct data {
    int id;
    int distance;
    int predecessor;
} Data;

// a node in the queue
struct Node {
    Data* value;
    struct Node *next;
};


// queue has a head that points to first node and a tail that points to the last node.
class Queue {
    private:
        Node *head = NULL;
        Node *tail = NULL;
        int size = 0;
    
    public: 
        // create a node with specified Data and add it to the end of the queue
        void enqueue(Data* newValue) {
            try {
              Node *newNode = new Node();
              newNode->value = newValue;
              newNode->next = NULL;
           
              if (head == NULL) {
                  head = newNode;
                  tail = newNode;
                  tail->next = NULL;                  
              }
              else {
                tail->next = newNode;
                tail = newNode;
                tail->next = NULL;                  
              }   
                
              ++size;
            } catch (std::bad_alloc&) {
                cout << "Memory allocation failed" << endl;
            }
        }
        
        // remove and return the node at the front of the queue
        Node* dequeue() {
			if (head == NULL)
				cout << "empty queue" << endl;
            else {
                struct Node *tmp = head;
                head = head->next;
                //delete(tmp);
                --size;
                return tmp;
            }
                
        }
    
        // return 1 if queue is empty
        int isEmpty() {
            if (size == 0) 
                return 1;
            else
                return 0;
        }
    
    // print out the queue
    void print() {
        cout << "The queue is:" << endl;
        Node *ptr = head;
        while (ptr != NULL) {
            cout << "Node id:"<< (ptr->value)->id << " distance:" << (ptr->value)->distance << " predecessor:" << (ptr->value)->predecessor << endl;
            ptr = ptr->next;
        }
    }
};


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
            array = new AdjList [numVertices];
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
 

    

int main()
{
    Queue q1;
    
    int numVertices = 8;
    int *visited = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    Graph myGraph(numVertices, "undirected");
    myGraph.addNewEdge(0, 0);
    myGraph.addNewEdge(1, 2);
    myGraph.addNewEdge(1, 4);
    myGraph.addNewEdge(2, 4);
    myGraph.addNewEdge(2, 7);
    myGraph.addNewEdge(3, 4);
    myGraph.addNewEdge(3, 5);
    myGraph.addNewEdge(4, 5);
    myGraph.addNewEdge(5, 6);
    myGraph.print();
   
    Data *data1 = new Data();
    data1->id = 3;
    data1->distance = 0;
    data1->predecessor = -1;
    q1.enqueue(data1);
    q1.print();
    
    while (! q1.isEmpty() ) {
        // dequeue vertex s from q
        Node* s = q1.dequeue();
        int s_id = s->value->id;
        int s_distance = s->value->distance;
        visited[s_id] = 1;
      
		// find adj Matrix 1 
		for (int ii = 0; ii < numVertices; ii++) {
			if (AdjMatrix[s_id][ii] == 1) {
				cout << "Id is " << ii << endl;
				int v_id = ii;
				// if vertex v has not been visited, insert it into queue
				if  (visited[v_id] == 0) {
					// mark vertex as visited and insert into queue
					visited[v_id] = 1;
					Data *data1 = new Data();
					data1->id = v_id;
					data1->distance = s_distance + 1;
					data1->predecessor = s_id;
				
					cout << "enqueue " << v_id << endl;	
					q1.enqueue(data1);
					q1.print();
            	}
				else
					cout << v_id << " already visited" << endl;
			}
		}	
       
  	}
	//print visited
	for (int i = 0; i < numVertices; i++)
		cout << i << " -> " << visited[i] << " " << endl; 
    return 0;

}
