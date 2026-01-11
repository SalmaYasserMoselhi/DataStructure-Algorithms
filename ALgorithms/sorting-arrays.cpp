#include <iostream>
using namespace std;

void display(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int* arr, int size) {
    int sorted = 0; // flag to check if array is sorted
    for (int i = 0; (i < size && sorted == 0); i++)  // iterate n (size) times 
    {
        sorted = 1; // assume sorted
        for (int j = 0; j < size - 1 - i; j++)  // iterate n-i-1 times (last i elements are sorted)
        {
            if (arr[j] > arr [j+1])
            {
                swap(arr[j], arr[j + 1]);
                sorted = 0; // found a pair out of order so not sorted
            }
        }
    }
    
}

int main() {
    int arr[] = {5, 10, 20, 1, 9, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Before Sorting: ";
    display(arr, size);
    bubbleSort(arr, size);
    cout << "After Sorting: ";
    display(arr, size);

    return 0;
}