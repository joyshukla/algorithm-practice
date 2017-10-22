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

		int peek(void)
		{
			if(top == 0)
			{
				cout << "Error: stack is empty" <<  endl;
				return -1;
			}

			return array[top-1];
		}
		void display(void)
		{
			cout << "Stack Contents : ";
			for(int i =0; i < top; i++)
				cout << array[i] << " ";
			cout << endl;
		}
};

int main()
{
	stack myStack(5);
	
	myStack.display();

	cout << "push 10" << endl;
	myStack.push(10);
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	cout << "push 20" << endl;
	myStack.push(20); 
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	
	cout << "push 30" << endl;
	myStack.push(30);
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	
	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	cout << "push 40" << endl;
	myStack.push(40); 
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	cout << "push 50" << endl;
	myStack.push(50); 
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	cout << "push 60" << endl;
	myStack.push(60); 
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	cout << "push 70" << endl;
	myStack.push(70); 
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 
	cout << "pop " << myStack.pop() << endl;
	myStack.display();
	cout << "peek is " << myStack.peek() << endl << endl; 

	return 1;
}
