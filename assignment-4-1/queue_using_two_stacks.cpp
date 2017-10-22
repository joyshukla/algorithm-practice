#include<iostream>
#include<stack>
using namespace std;

class QueueWithTwoStacks
{
	private:
		stack<int> stack1;
		stack<int> stack2;
		int size;
		int capacity;
		int frontEle = -1;
		int backEle = -1;
	
	public:
		QueueWithTwoStacks(int _capacity)
		{
			size =0;
			capacity = _capacity;
		}

		void enqueue(int elem)
		{
			if(size < capacity)
			{
				stack1.push(elem);
				++size;

				if(size == 1)
				{
					frontEle = backEle = elem;
				}
				else
				{
					backEle = elem;
				}
			}
			else
			{
				cout << "Error: queue is full." << endl;
			}
		}

		int dequeue()
		{
			int elem;
			if(size == 0)
			{
				cout << "Error: queue is empty." << endl;
				elem = -1;
			}
			else
			{
				if (stack2.empty())
				{
					while (!stack1.empty())
					{
						int temp = stack1.top();
						stack1.pop();
						stack2.push(temp);
					}
				}

				elem = stack2.top();
				stack2.pop();
				--size;

				if (size > 0)
				{
					if (stack2.empty())
					{
						while (!stack1.empty())
						{
							int temp = stack1.top();
							stack1.pop();
							stack2.push(temp);
						}
					}
					frontEle = stack2.top();
				}
				else
				{
					frontEle = backEle = -1;
				}
			}
			return elem;
		}

		int front()
		{
			return frontEle;
			/*			
			if(stack2.empty())
			{
				while(!stack1.empty())
				{	
					int temp = stack1.top();
					stack1.pop();
					stack2.push(temp);
				}
			}	

			return stack2.top();
			*/
		}

		int back()
		{
			return backEle;
			/*
			if(!stack1.empty())
			{
				return stack1.top();
			}
			else
			{
				// need to handle this case still
				cout << "Error: this should not occur, stack1 should not be empty" << endl;	
			}
			*/
		}

		void print()
		{
			int count =0;
			cout << "Queue contents : ";
			// transfer all elements from stack2 to stack1 and print out
			while(!stack2.empty())
			{
				int temp = stack2.top();
				cout << temp << " ";
				stack2.pop();
				stack1.push(temp);
				++count;
			}

			// transfer all elements from stack1 to stack2, do not print out
			while(!stack1.empty())
			{
				int temp = stack1.top();
				stack2.push(temp);	
				stack1.pop();
			}

			// print all elements originally in stack1 and put them back in stack1
			int numValuesToPop = size - count;
			while(numValuesToPop > 0)
			{
				int temp = stack2.top();
				cout << temp << " ";
				stack2.pop();
				stack1.push(temp);
				numValuesToPop--;
			}
			cout << endl;
		}

		int get_size(void)
		{
			return size;
		}
};

int main()
{
	QueueWithTwoStacks myQueue(5);

	cout << "enqueue 10" << endl;
	myQueue.enqueue(10);
	myQueue.print();

	cout << "enqueue 20" << endl;
	myQueue.enqueue(20);
	myQueue.print();
	
	cout << "enqueue 30" << endl;
	myQueue.enqueue(30);
	myQueue.print();
	
	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();
	
	cout << "enqueue 40" << endl;
	myQueue.enqueue(40);
	myQueue.print();
	
	cout << "enqueue 50" << endl;
	myQueue.enqueue(50);
	myQueue.print();
	
	cout << "enqueue 60" << endl;
	myQueue.enqueue(60);
	myQueue.print();
	
	cout << "enqueue 70" << endl;
	myQueue.enqueue(70);
	myQueue.print();
	
	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();
	
	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();
	
	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();

	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();
	
	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();

	cout << "dequeueing " << myQueue.front() << endl;	
	myQueue.dequeue();
	myQueue.print();

	return 1;
}
/*
int main()
{
	QueueWithTwoStacks myQueue(10);

	myQueue.enqueue(10);
	myQueue.enqueue(20);
	myQueue.enqueue(30);

	myQueue.print();
	cout << "front : " << myQueue.front() << endl;

	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();
	cout << "dequeueing " << myQueue.front() << endl;
	myQueue.dequeue();
	myQueue.print();

	return 1;
}*/
