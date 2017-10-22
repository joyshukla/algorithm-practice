// implement doubly linked list
// implement insert, delete and search

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
		void insertNode(int x, int pos=0)
		{
			if(pos > size)
			{
				// throw an exception
				cout << "Error: position out of range" << endl;
				return;
			}


			node *newnode = new node();
			newnode->key = x;
			
			if(pos == 0) 						// insert at head
			{	
				newnode->next = head;
				if (head != NULL)
					head->prev = newnode;
				else
					tail = newnode;
				head = newnode;
			}
			else if(pos == size)						// insert at tail
			{
				tail->next = newnode;
				newnode->prev = tail;
				tail = newnode;	
			}	
			else
			{
				node *ptr = head;
				int count = 0;
				while(count != pos)
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
	
		node *deleteNode(int pos=0)
		{
			if(pos >=size)
			{
				// throw an exception
				cout << "Error: position out of range" << endl;
				return NULL;
			}


			if(pos == 0)						// first element
			{
				node *ptr = head;
				head = head->next;
				if (head != NULL)
					head->prev = NULL;			// more than 1 element
				else
					tail = NULL;				// only 1 element
				return ptr;
			}			
			else if(pos == ( size - 1 ))		// last element
			{
				node *ptr = tail;
				tail->prev->next = NULL;
				tail = tail->prev;
			}
			else								// element in the middle
			{
				node *ptr = head;
				int count = 0;
				while(pos != count)				// find the node at given position 
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
			while(ptr!= NULL)
			{
				cout << ptr->key << " ";
				ptr = ptr->next;
			}
			cout << endl;
		}
};


int main()
{
	doublyLinkedList List1;

	cout << "insert node 10 at pos 0" << endl;
	List1.insertNode(10);
	List1.print();

	cout << "insert node 20 at pos 0" << endl;
	List1.insertNode(20);
	List1.print();

	cout << "insert node 30 at pos 2" << endl;
	List1.insertNode(30,2);
	List1.print();

	cout << "delete a node at pos 1" << endl;
	List1.deleteNode(1);
	List1.print();

	cout << "delete a node at pos 0" << endl;
	List1.deleteNode();
	List1.print();

	cout << "delete a node at pos 0" << endl;
	List1.deleteNode();
	List1.print();

	cout << "insert node 40 at pos 5" << endl;
	List1.insertNode(40,5);
	List1.print();

	getchar();
	return 1;
}
