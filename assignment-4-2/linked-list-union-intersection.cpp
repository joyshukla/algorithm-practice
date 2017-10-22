#include<iostream>
using namespace std;

struct node{
	int key;
	node *next = NULL;
	node *prev = NULL;
};

class doublyLinkedList
{
private:
	node* head;
	node* tail;
	int size;

public:
	doublyLinkedList()
	{
		size = 0;
	}
	node *get_head(void)
	{
		return head;
	}

	int get_size(void)
	{
		return size;
	}

	void insertNode(int key, int pos=0)
	{
		if (pos > size)
		{
			cout << "pos > size not allowed";
			return;
		}
		
		node *newNode = new node();
		newNode->key = key;

		node *ptr = head;
		int count = 0;
		while (count != pos)
		{
			ptr = ptr->next;
			count++;
		}

		if (pos == 0) 						// insert at head
		{
			newNode->next = head;
			if (head != NULL)
				head->prev = newNode;
			else
				tail = newNode;
			head = newNode;
		}
		else if (pos == size)						// insert at tail
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		else
		{
			node *prevNode = ptr->prev;
			node *nextNode = ptr;

			newNode->next = nextNode;
			newNode->prev = prevNode;

			prevNode->next = newNode;
			nextNode->prev = newNode;
		}
		size++;
	}


	void print(void)
	{
		node *ptr = head;
		cout << "List : ";
		while (ptr != NULL)
		{
			cout << ptr->key << " ";
			ptr = ptr->next;
		}
		cout << endl;

	}
};

doublyLinkedList listUnion(doublyLinkedList List1, doublyLinkedList List2, string operation)
{
	doublyLinkedList uList,iList;

	node *ptrList1 = List1.get_head();
	node *ptrList2 = List2.get_head();

	while ((ptrList1 != NULL) && (ptrList2 != NULL))
	{
		//cout << ptrList1->key << "-" << ptrList2->key << endl;
		if (ptrList1->key < ptrList2->key)
		{
			// list1 key is smaller
			uList.insertNode(ptrList1->key, uList.get_size());
			ptrList1 = ptrList1->next;
		}
		else if (ptrList1->key > ptrList2->key)
		{
			// list2 key is smaller
			uList.insertNode(ptrList2->key, uList.get_size());
			ptrList2 = ptrList2->next;
		}
		else
		{
			uList.insertNode(ptrList1->key, uList.get_size());
			iList.insertNode(ptrList1->key, iList.get_size());
			ptrList1 = ptrList1->next;
			ptrList2 = ptrList2->next;
		}
	}

	if (ptrList1 == NULL)
	{
		// rest of the elements of ptrList2
		while (ptrList2 != NULL)
		{
			//cout << ptrList2->key << endl;
			uList.insertNode(ptrList2->key, uList.get_size());
			ptrList2 = ptrList2->next;
		}
	}
	else if (ptrList2 == NULL)
	{
		// rest of the elements of ptrList1
		while (ptrList1 != NULL)
		{
			//cout << ptrList1->key << endl;
			uList.insertNode(ptrList1->key, uList.get_size());
			ptrList1 = ptrList1->next;
		}
	}

	if (operation == "union")
		return uList;
	else if (operation == "intersection")
		return iList;
}

int main()
{
	cout << endl << "--input--" << endl << endl;

	doublyLinkedList List1;

	List1.insertNode(120);
	List1.insertNode(100);
	List1.insertNode(50);
	List1.insertNode(40);
	List1.insertNode(20);
	List1.insertNode(10);
	List1.print();

	doublyLinkedList List2;

	List2.insertNode(80);
	List2.insertNode(70);
	List2.insertNode(60);
	List2.insertNode(50);
	List2.insertNode(40);
	List2.insertNode(30);
	List2.insertNode(20);
	List2.insertNode(10);
	List2.print();

	cout << endl << "--output--" << endl << endl;

	doublyLinkedList uList = listUnion(List1, List2,"union");
	doublyLinkedList iList = listUnion(List1, List2, "intersection");
	
	cout << "Union ";
	uList.print();
	cout << "Intersection ";
	iList.print();

	getchar();
	return 1;
}