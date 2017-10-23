#include<iostream>
#include<stack>
using namespace std;

struct node{
	int val;
	node *next = NULL;
};

struct AdjList{
	node *head = NULL;
};

int ctime;

class graph{
private:
	AdjList *listMap;
	string type;
	int size;
public:
	graph(int numOfNodes, string type)
	{
		listMap = new AdjList[numOfNodes];

		type = type;
		size = numOfNodes;

	}

	void addEdge(int i, int j)
	{
		node *newNode = new node;
		newNode->val = j;
		newNode->next = listMap[i].head;
		listMap[i].head = newNode;

		if (type == "undirected")
		{
			node *newNode = new node;
			newNode->val = i;
			newNode->next = listMap[j].head;
			listMap[j].head = newNode;
		}
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			node *ptr = getAdjListHead(i);
			cout << i << " -> ";
			while (ptr != NULL)
			{
				cout << ptr->val << ", ";
				ptr = ptr->next;
			}
			cout << endl;
		}
	}

	node *getAdjListHead(int node)
	{
		return listMap[node].head;
	}

	int getSize()
	{
		return size;
	}
};

void depthfirstSearch(graph G, int startNode, int *visited, int *discoveryTime, int *finishingTime)
{
	std::stack<int> traverseStack;

	node *ptr = G.getAdjListHead(startNode);
	cout << "visited node " << startNode << endl;
	discoveryTime[startNode] = ctime++;
	visited[startNode] = 1;

	traverseStack.push(startNode);
	do
	{
		ptr = G.getAdjListHead(traverseStack.top());
		bool unVisitedNodeFound = false;
		while ((ptr != NULL) && (unVisitedNodeFound == false))
		{
			int tempNode = ptr->val;
			if (visited[tempNode] == 0)
			{
				cout << "visited node " << tempNode << endl;
				discoveryTime[tempNode] = ctime++;
				visited[tempNode] = 1;
				traverseStack.push(tempNode);
				unVisitedNodeFound = true;
			}
			else
				cout << tempNode << " already visited." << endl;
			ptr = ptr->next;
		}

		if (unVisitedNodeFound == false)
		{
			int popNode = traverseStack.top();
			traverseStack.pop();
			finishingTime[popNode] = ctime++;
		}

	} while (!traverseStack.empty());
}

void dfsWrapper(graph G, int startNode)
{
	int *visited;
	int *discoveryTime;
	int *finishingTime;
	ctime = 0;

	visited = new int[G.getSize()];
	discoveryTime = new int[G.getSize()];
	finishingTime = new int[G.getSize()];
	for (int i = 0; i < G.getSize(); i++)
		visited[i] = 0;
	for (int i = 0; i < G.getSize(); i++)
		discoveryTime[i] = 0;
	for (int i = 0; i < G.getSize(); i++)
		finishingTime[i] = 0;

	depthfirstSearch(G, startNode, visited, discoveryTime, finishingTime);

	for (int i = 0; i < G.getSize(); i++)
		if (visited[i] == 0)
			depthfirstSearch(G, i, visited, discoveryTime, finishingTime);

	cout << endl;

	cout << "Discovery/Finishing Time" << endl;
	for (int i = 0; i < G.getSize(); i++)
		cout << i << " - " << discoveryTime[i] << "/" << finishingTime[i] << endl;
}


int main()
{
	int size = 8;
	graph G(size, "directed");
	G.addEdge(0, 0);
	G.addEdge(1, 2);
	G.addEdge(1, 4);
	G.addEdge(2, 4);
	G.addEdge(2, 7);
	G.addEdge(3, 4);
	G.addEdge(3, 5);
	G.addEdge(4, 5);
	G.addEdge(5, 6);

	G.print();

	dfsWrapper(G, 1);

	getchar();
	return 1;
}

