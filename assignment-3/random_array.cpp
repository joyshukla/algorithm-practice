#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_array(int *arr, size_t n)
{
    for (size_t i=0; i<n; i++){
        arr[i] = i;
    }
 
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

int main()
{
    int i;
    int *arr;
	int size = 100;
	arr = new int[size];
    random_array(arr, size);
    for (i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
}
