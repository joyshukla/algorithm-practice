#include<iostream>
#include<map>
#include<string>
using namespace std;

struct node
{
	std::pair<int,int> value;
	node *left = NULL;
	node *right = NULL;
	bool IsStarNode = false;
	string code = "";
};

class huffman_tree
{
private:
	node* root;
public:
	huffman_tree(std::map<int, int> freqTable)
	{
		// initialize the huffman tree based on freqTable map
		node *rootNode=NULL;
		node *leftNode;
		node *rightNode;
		map<int, node *> starNodesMap;
		while(freqTable.size() > 1)
		{
			if (freqTable.begin()->second != NULL)
			{
				// create two leaf nodes from lowest frequency terms 
				leftNode = new node();
				leftNode->value.first = freqTable.begin()->first;
				leftNode->value.second = freqTable.begin()->second;
				cout << "Created  a leaf node on left with " << leftNode->value.first << " : " << leftNode->value.second << endl;
			}
			else
			{
				// 
				leftNode = starNodesMap.at(freqTable.begin()->first);
			}

			// erase the term from freqTable
			freqTable.erase(freqTable.begin());

			if (freqTable.begin()->second != NULL)
			{
				rightNode = new node();
				rightNode->value.first = freqTable.begin()->first;
				rightNode->value.second = freqTable.begin()->second;
				cout << "Created  a leaf node on right with " << rightNode->value.first << " : " << rightNode->value.second << endl;
			}
			else
			{
				// 
				rightNode = starNodesMap.at(freqTable.begin()->first);
			}

			// erase the term from freqTable
			freqTable.erase(freqTable.begin());

			node *starNode = new node();
			starNode->value.first = leftNode->value.first + rightNode->value.first;
			starNode->value.second = NULL;
			starNode->left = leftNode;
			starNode->right = rightNode;
			starNode->IsStarNode = true;
			cout << "Created  a star node with " << starNode->value.first << " : " << starNode->value.second << endl;
			// keep a map of star nodes so that they can be linked
			starNodesMap[starNode->value.first] = starNode;

			freqTable[starNode->value.first] = NULL;

			// when only 1 element left, it is the root
			if (freqTable.size() == 1)
				root = starNode;
		}
	}

	void printInOrder(node *ptr)
	{
		if (ptr == NULL)
			return;

		printInOrder(ptr->left);
		cout << ptr->value.first << " : " << ptr->value.second << " ";
		printInOrder(ptr->right);
	}

	node *getRoot()
	{
		return root;
	}

	// do a preorder traversal
	void encode(node *ptr)
	{
		if (ptr == NULL)
			return;
		if (!ptr->IsStarNode)
		{
			cout.width(5);
			cout << ptr->value.first << "," << ptr->value.second;
			//cout << "(" << ptr->value.first << "," << ptr->value.second << ")";
			cout << " -> " << ptr->code << endl;
		}
		if (ptr->left != NULL)
			ptr->left->code = ptr->code + "0";
		if (ptr->right != NULL)
			ptr->right->code = ptr->code + "1";
		encode(ptr->left);
		encode(ptr->right);
	}


};

int main()
{
	std::map<int, int> freqTable;

	freqTable[10] = 3;
	freqTable[5] = 1;
	freqTable[7] = 2;
	freqTable[15] = 4;
	freqTable[20] = 5;
	freqTable[45] = 6;

	huffman_tree myHuffmanTree(freqTable);

	cout << endl;

	myHuffmanTree.encode(myHuffmanTree.getRoot());
	getchar();
	return 1;
}