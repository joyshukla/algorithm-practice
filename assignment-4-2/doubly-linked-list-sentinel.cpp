// implement doubly linked list
// implement insert, delete and search
// this is the implementation with sentinel

// advantages of sentenel method:
//				no need to handle boundry conditions for pos=0 and pos=size
//				code complexity reduced

// disadvantages of sentinel method"
//				extra memory space for two nodes

#include<iostream>
using namespace std;

struct node
{
	int key;
	node *prev = NULL;
	node *next = NULL;

	bool sentinel = false;
};

class doublyLinkedList
{
private:
	node *head = NULL;
	node *tail = NULL;
	int size = 0;

public:
	doublyLinkedList(void)
	{
		node *sentinel_head = new node();
		sentinel_head->sentinel = true;
		sentinel_head->key = -1;
		node *sentinel_tail = new node();
		sentinel_tail->sentinel = true;
		sentinel_tail->key = -1;

		head = sentinel_head;
		tail = sentinel_tail;
		head->next = tail;
		tail->prev = head;

	}

	void insertNode(int x, int pos = 0)
	{
		if (pos > size)
		{
			// throw an exception
			cout << "Error: position out of range" << endl;
			return;
		}


		node *newnode = new node();
		newnode->key = x;
		{
			node *ptr = head;
			int count = -1;
			while (count != pos)
			{
				ptr = ptr->next;
				count++;
			}
			node *PrevNode = ptr->prev;
			node *NextNode = ptr;

			PrevNode->next = newnode;
			NextNode->prev = newnode;

			newnode->prev = PrevNode;
			newnode->next = NextNode;
		}

		size++;
	}

	node *deleteNode(int pos = 0)
	{
		if (pos >= size)
		{
			// throw an exception
			cout << "Error: position out of range" << endl;
			return NULL;
		}

		{
			node *ptr = head;
			int count = -1;
			while (pos != count)				// find the node at given position 
			{
				ptr = ptr->next;
				count++;
			}
			if (!ptr->sentinel)
			{
				node *PrevNode = ptr->prev;
				node *NextNode = ptr->next;

				PrevNode->next = ptr->next;
				NextNode->prev = ptr->prev;
			}

			return ptr;
		}
		size--;
	}

	node *searchList(int elem)
	{
		node *ptr = head;
		int count = 0;
		while (ptr != NULL)
		{
			if (ptr->key == elem)
			{
				cout << "found node at position " << count << endl;
				return ptr;
			}
			count++;
			ptr = ptr->next;
		}
		cout << "Node with key " << elem << " not found" << endl;
		return NULL;

	}


	void print()
	{
		cout << "List: ";
		node *ptr = head;
		while (ptr != NULL)
		{
			if (ptr->sentinel)
				cout << "<S> ";
			else
				cout << ptr->key << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};


int main()
{
	doublyLinkedList List1;
	List1.print();
	
	cout << "insert node 10 at pos 0" << endl;
	List1.insertNode(10);
	List1.print();
	
	
	cout << "insert node 20 at pos 0" << endl;
	List1.insertNode(20);
	List1.print();

	cout << "insert node 30 at pos 1" << endl;
	List1.insertNode(30, 1);
	List1.print();

	cout << "searching for node 20" << endl;
	List1.searchList(20);

	cout << "delete a node at pos 1" << endl;
	List1.deleteNode(1);
	List1.print();

	cout << "delete a node at pos 0" << endl;
	List1.deleteNode();
	List1.print();

	cout << "delete a node at pos 0" << endl;
	List1.deleteNode();
	List1.print();


	getchar();
	return 1;
}
