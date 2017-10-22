// since the doublyLinkedList has ways to insert at head and tail with O(1) time, 
// this implementation of deque also does push,pop,inject and eject in O(1) time.

#include<iostream>
using namespace std;

struct node
{
	int key;
	node *prev = NULL;
	node *next = NULL;
};

class doublyLinkedList
{
private:
	node *head = NULL;
	node *tail = NULL;
	int size = 0;

public:
	int getSize(void)
	{
		return size;
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

		if (pos == 0) 						// insert at head
		{
			newnode->next = head;
			if (head != NULL)
				head->prev = newnode;
			else
				tail = newnode;
			head = newnode;
		}
		else if (pos == size)						// insert at tail
		{
			tail->next = newnode;
			newnode->prev = tail;
			tail = newnode;
		}
		else
		{
			node *ptr = head;
			int count = 0;
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


		if (pos == 0)						// first element
		{
			node *ptr = head;
			head = head->next;
			if (head != NULL)
				head->prev = NULL;			// more than 1 element
			else
				tail = NULL;				// only 1 element
			return ptr;
		}
		else if (pos == (size - 1))		// last element
		{
			node *ptr = tail;
			tail->prev->next = NULL;
			tail = tail->prev;

			return ptr;
		}
		else								// element in the middle
		{
			node *ptr = head;
			int count = 0;
			while (pos != count)				// find the node at given position 
			{
				ptr = ptr->next;
				count++;
			}

			node *PrevNode = ptr->prev;
			node *NextNode = ptr->next;

			PrevNode->next = ptr->next;
			NextNode->prev = ptr->prev;

			return ptr;
		}
		size--;
	}

	void print()
	{
		cout << "List: ";
		node *ptr = head;
		while (ptr != NULL)
		{
			cout << ptr->key << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};

class deque
{
private:
	doublyLinkedList linkedList;

public:
	void push(int elem)											// insert element at head
	{
		linkedList.insertNode(elem,0);
	}

	node *pop()
	{
		return linkedList.deleteNode(0);
	}

	void inject(int elem)										// 
	{
		linkedList.insertNode(elem, linkedList.getSize());
	}

	node *eject()
	{
		return linkedList.deleteNode(linkedList.getSize() - 1);
	}

	void print()
	{
		linkedList.print();
	}
};

int main()
{
	deque deq;

	deq.push(5);
	cout << "push 5" << endl;
	deq.push(10);
	cout << "push 10" << endl;
	deq.push(20);
	cout << "push 20" << endl;
	deq.push(30);
	cout << "push 30" << endl;
	deq.push(40);
	cout << "push 40" << endl;

	deq.print();

	cout << "pop " << deq.pop()->key << endl;
	deq.print();

	deq.inject(100);
	cout << "inject 100" << endl;
	deq.print();

	cout << "eject " << deq.eject()->key << endl;
	deq.print();

	getchar();
	return 1;
}