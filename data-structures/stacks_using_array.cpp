// stacks using array
// implement push and pop

#include <iostream>
using namespace std;

class stack
{
	private:
		int *array;
		int capacity;
		int top;

	public:
		stack(int cap)
		{
			capacity = cap;
			array = new int[capacity];

			top = 0;
		}

		void push(int element)
		{
			if(top == capacity) 
			{
				cout << "Error: stack is full" << endl;
				return;
			}
			else
			{
				array[top++] = element;
			}
		}

		int pop(void)
		{
			if(top == 0)
			{
				cout << "Error: stack is empty" <<  endl;
				return -1;
			}
		
			int element = array[--top];

			return element;
		}
};

int main()
{
	stack myStack(5);

	cout << "push 10" << endl;
	myStack.push(10);
	cout << "push 20" << endl;
	myStack.push(20); 
	
	cout << "pop " << myStack.pop() << endl;
	cout << "pop " << myStack.pop() << endl;
	cout << "pop " << myStack.pop() << endl;

	return 1;
}
