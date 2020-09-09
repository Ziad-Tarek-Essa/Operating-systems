#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>

#define N 100

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

/* Driver program to test above functions */
int main()
{
    int min = -1000, max = 1000;
    int arr[10], arr2[10], arr3[10];
    int i,r;
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int id1,id2;
    //Threads init
    pthread_t thread1 , thread2, thread3;
    int ans1, ans2, ans3;


    for( i = 0; i < arr_size; i++){
        r = rand() % (max - min + 1);
        arr[i] = r;
        arr2[i] = r;
        arr3[i] = r;
    }
    //printf("Before: \n");

    if((id1 = fork()) == 0)
    {
        printf("Child1: \n");
        mergeSort(arr2, 0, arr_size - 1);
        printArray(arr2, arr_size);
        execl("/bin/date", "date",0);
    }

    if((id2 = fork()) == 0 && id1 != 0)
    {
        printf("Child2: \n");
        ans1 = pthread_create ( &thread1 , NULL , mergeSort ,(arr3, (arr_size / 2) - 1 ,arr_size - 1 )) ;
        ans2 = pthread_create ( &thread2 , NULL , mergeSort ,(arr3, 0, (arr_size / 2)-  1 )) ;
        ans3 = pthread_create ( &thread3 , NULL , printArray ,(arr3, arr_size) ) ;
        execl("/bin/date", "date",0);
        if ( ans1 != 0 || ans2 != 0 || ans3 != 0) {
            printf ( " \n can't create threads " ) ;
            exit(0) ;
        }
            pthread_join ( thread1 , NULL ) ;
            pthread_join ( thread2 , NULL ) ;
            pthread_join ( thread3 , NULL ) ;

    }
    wait();
    if(id1 != 0 && id2 != 0){

        printf("Given array is \n");
        printArray(arr, arr_size);
        printf("Father:\n");
        mergeSort(arr, 0, arr_size - 1);
        printArray(arr, arr_size);
        execl("/bin/date", "date",0);
        printf("\nSorted array is \n");
        //printf("After: \n");
    }
    return 0;
}
