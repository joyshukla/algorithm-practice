// implement queue using array
// implement enqueue and dequeue


#include<iostream>
using namespace std;

class queue
{
	private:
		int *array;
		int head;
		int tail;
		int size;
		int capacity;

	public:
		queue(int cap)
		{
			capacity = cap;
			head = 0;
			tail = 0;
			size = 0;
			array = new int[capacity];
		}

		void enqueue(int element)
		{
			if(size == capacity)
			{
				cout << "Error: queue is full" << endl;
			}
			else
			{
				array[tail] = element;
				size++;
				tail = (tail + 1) % capacity;
			}
		}

		int dequeue(void)
		{
			if(size == 0)
			{
				cout << "Error: queue is empty" << endl;
				return -1;
			}

			int element = array[head];
			size--;
			head = (head + 1) % capacity;
			return element;

		}
};

int main()
{
	queue myQueue(5);
	
	cout << "queue 10" << endl;
	myQueue.enqueue(10);
	cout << "queue 20" << endl;
	myQueue.enqueue(20);
	
	cout << "dequeue " << myQueue.dequeue() << endl;
	cout << "dequeue " << myQueue.dequeue() << endl;
	cout << "dequeue " << myQueue.dequeue() << endl;

	return 1;
}
