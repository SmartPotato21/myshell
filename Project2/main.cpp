#include <stdio.h>      
#include <stdlib.h>    
#include <thread>
#include <iostream>
#include <cmath>

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

	for	(int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\n";
}


int main()
{
    int arr[] = {5,6,7,5,9,8,9,8,6,7,2,1,55};          //array
    int n = sizeof(arr) / sizeof(arr[0]);   // N
 	int half1 = n/2;
	int half2 = (n+1)/2;			//incase there is odd N, round int up.


    thread a(insertionSort,&arr[0],half1);
    a.join();


	thread b(insertionSort,&arr[6],half2);
    b.join();





    return 0;
}