#include <stdio.h>      
#include <stdlib.h>    
#include <thread>
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstdlib>

#define N 100000

using namespace std;

void insertionSort(int* arr, int n)	//sorts all elements starting at int* up to n
{
    int leftIndex = 0;
    int rightIndex = 1;
    int i = 1;

    while (rightIndex < n)
    {
        leftIndex = rightIndex-1;
		
        while(arr[leftIndex] > arr[rightIndex] && leftIndex >= 0)
        {
            int temp = arr[leftIndex];
            arr[leftIndex] = arr[rightIndex];
            arr[rightIndex] = temp;

            leftIndex--;
            rightIndex--;
        }
        
        i++;
		rightIndex = i;
    }
}

void merge(int* arr1,int* arr2, vector<int> &output, int half1, int half2)
{
	int n = half1*2;

	for (int i = 0; i < n; i++)				// sort all even n elements
	{
		if(arr1[0] < arr2[0] || half2 == 0)	//check if half2 has been fully checked or compare values
		{
			output.push_back(arr1[0]);
			arr1++;							//point to next value
		}
		else 
		{
			output.push_back(arr2[0]);		
			half2--;						
			arr2++;							//point to next value
		}
	}

	if (half2 != half1)						//sort remainder if odd n
		output.push_back(arr2[0]);

}

void multithreadedSort(int* arr, int half1, int half2, int n)
{
	auto start = chrono::high_resolution_clock::now();


	thread a(insertionSort,&arr[0],half1);
	thread b(insertionSort,&arr[half1],half2);
	a.join();
    b.join();

	vector<int> output;
	output.reserve(n);

	thread c(merge,&arr[0], &arr[half1], ref(output), half1, half2);
	c.join();


	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Multithreadded code took " << duration.count() << "ms \n";
}
void singlethreadedSort(int* arr, int half1, int half2, int n)
{
	auto start = chrono::high_resolution_clock::now();

	insertionSort(&arr[0], half1);
	insertionSort(&arr[half1], half2);

	vector<int> output;
	output.reserve(n);

	merge(&arr[0], &arr[half1],output, half1,half2);


	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Singlethreadded code took " << duration.count() << "ms \n";
}


int main()
{
    int arr1[N];          //array
	int arr2[N];          //array

	for (int i = 0; i < N; i++)
	{
		int x = rand() % 99999;
		arr1[i] = x;
		arr2[i] = x;
	}
    const int n = sizeof(arr1) / sizeof(arr1[0]);   // n
 	int half1 = n/2;
	int half2 = (n+1)/2;			//incase there is odd n, round int up.


	
    multithreadedSort(arr1,half1,half2,n);
	singlethreadedSort(arr2,half1,half2,n);

    return 0;
}