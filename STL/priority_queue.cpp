// implement a min priority queue (sorted ascending order )
#include<iostream>
#include<queue>
using namespace std;

int main()
{
	// default max_priority
	priority_queue<int> pq;
	// to make it min_priority
	//priority_queue<int, vector<int>, greater<int>> pq;
	
	pq.push(10);
	pq.push(20);
	pq.push(5);
	
	while(!pq.empty())
	{
		cout << pq.top() << endl;
		pq.pop();
	}
	return 1;
}
