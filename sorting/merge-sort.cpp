#include<iostream>
using namespace std;

#define SIZE 7

void print(int *list, int left, int right)
{
	cout << "list : ";
	for(int i=left; i<= right; i++)
		cout << list[i] << " ";
	cout << endl;
}

void merge(int *list, int left, int mid, int right)
{
	//cout << "merge " << left << " " << mid << " " << right << endl;
	int *list1;
	int len1 = mid - left + 1;
	list1 = new int[len1];

	int *list2;
	int len2 = right - mid;
	list2 = new int[len2];

	for (int i = 0; i < len1; i++)
		list1[i] = list[left+i];

	for (int i = 0; i < len2; i++)
		list2[i] = list[mid+1+i];

	//cout << "part1 ";
	//print(list1, 0, len1-1);
	//cout << "part2 ";
	//print(list2, 0, len2-1);

	int i=0, j=0,k=left;
	while ((i < len1) && (j < len2))
	{
		if (list1[i] < list2[j])
		{
			list[k] = list1[i];
			i++;
			k++;
		}
		else if (list1[i] > list2[j])
		{
			list[k] = list2[j];
			j++;
			k++;
		}
	}

	// remaining elements of list1, if any
	while (i < len1)
	{
		list[k] = list1[i];
		i++;
		k++;
	}

	// remaining elements of list2, if any
	while (j < len2)
	{
		list[k] = list2[j];
		j++;
		k++;
	}

	//cout << "merged ";
	//print(list, 0, k-1);


}

void mergeSort(int *list, int left, int right)
{
	if (left < right)
	{
		//cout << "mergeSort " << left << " " << right << endl;
		//print(list, left, right);

		int mid = (left + right) / 2;
		mergeSort(list, left, mid);
		mergeSort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}


int main()
{
	int list[] = {38, 27, 43, 3, 9, 82, 10};

	int left = 0;
	int right = SIZE-1;
	print(list, left, right);	
	mergeSort(list, left, right);
	print(list, left, right);
	getchar();
	return 1;
}
