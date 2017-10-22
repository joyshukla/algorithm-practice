#include<iostream>
#include<string>
using namespace std;

struct node
{
	int key;
	node *left=NULL;
	node *right=NULL;
};

class tree
{
private:
	node *rootNode = new node();

public:
	tree(int rootKey)
	{
		rootNode->key = rootKey;
	}

	node *getRoot(void)
	{
		return rootNode;
	}

	void insertNode(node *ptr, int elem, string loc)
	{
		cout << "insert a node " << elem << " at " << loc << " of " << ptr->key << endl;
		node *newNode = new node();
		newNode->key = elem;
		if (loc == "left")
			ptr->left = newNode;
		else if (loc =="right")
			ptr->right = newNode;
	}

	void inOrder(node *ptr)
	{
		if (ptr != NULL)
		{
			inOrder(ptr->left);
			cout << ptr->key << " ";
			inOrder(ptr->right);
		}
	}

	void preOrder(node *ptr)
	{
		if (ptr != NULL)
		{
			cout << ptr->key << " ";
			preOrder(ptr->left);
			preOrder(ptr->right);
		}
	}

	void postOrder(node *ptr)
	{
		if (ptr != NULL)
		{
			postOrder(ptr->left);
			postOrder(ptr->right);
			cout << ptr->key << " ";
		}
	}

};

int main()
{
	tree myTree(5);


	myTree.insertNode(myTree.getRoot(),3, "left");
	myTree.insertNode(myTree.getRoot()->left, 2, "left");
	myTree.insertNode(myTree.getRoot()->left, 4, "right");

	myTree.insertNode(myTree.getRoot(), 10, "right");
	myTree.insertNode(myTree.getRoot()->right, 7, "left");
	myTree.insertNode(myTree.getRoot()->right, 13, "right");

	cout << endl;
	cout << "in order traversal :" << endl;
	myTree.inOrder(myTree.getRoot());
	cout << endl << endl;

	cout << "pre order traversal :" << endl;
	myTree.preOrder(myTree.getRoot());
	cout << endl << endl;

	cout << "post order traversal :" << endl;
	myTree.postOrder(myTree.getRoot());
	cout << endl << endl;

	getchar();
	return 1;
}