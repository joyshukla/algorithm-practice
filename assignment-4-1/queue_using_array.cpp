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
				//tail = tail + 1;
			}
			//cout << "head :" << head;
			//cout << " tail :" << tail;
			//cout << " size :" << size;
			//cout << endl;
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
			//head = head+1;
			//cout << "head :" << head;
			//cout << " tail :" << tail;
			//cout << " size :" << size;
			//cout << endl;

			return element;
		}

		int get_size(void)
		{
			return size;
		}

};

int main()
{
	queue myQueue(5);

	cout << "queue 10" << endl;
	myQueue.enqueue(10);

	cout << "queue 20" << endl;
	myQueue.enqueue(20);
	
	cout << "queue 30" << endl;
	myQueue.enqueue(30);
	
	cout << "dequeue " << myQueue.dequeue() << endl;
	
	cout << "queue 40" << endl;
	myQueue.enqueue(40);
	
	cout << "queue 50" << endl;
	myQueue.enqueue(50);
	
	cout << "queue 60" << endl;
	myQueue.enqueue(60);
	
	cout << "queue 70" << endl;
	myQueue.enqueue(70);
	
	cout << "dequeue " << myQueue.dequeue() << endl;
	
	cout << "dequeue " << myQueue.dequeue() << endl;
	
	cout << "dequeue " << myQueue.dequeue() << endl;

	cout << "dequeue " << myQueue.dequeue() << endl;
	
	cout << "dequeue " << myQueue.dequeue() << endl;

	cout << "dequeue " << myQueue.dequeue() << endl;	

	return 1;
}
