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

// 0  1  2  3  4  5  6
// 80|90 60 30 50 70 40
// 80 90|60 30 50 70 40
// 80 60 90|30 50 70 40
// 60 80 90|30 50 70 40
// 60 80 30 90|50 70 40
// 60 30 80 90|50 70 40
// 30 60 80 90|50 70 40
// 30 60 80 50 90|70 40
// 30 60 50 80 90|70 40
// 30 50 60 80 90|70 40
// 30 50 60 80 70 90|40
// 30 50 60 70 80 90|40
// 30 50 60 70 80 40 90|
void insertionSort(int* arr, int size) { 
    for (int i = 1; i < size; i++) { // iterate from second element to last
        int key = arr[i]; // current element to be positioned -> key = arr[1] = 90 -> key = arr[2] = 60
        int j = i - 1; // index of previous element -> j = 0 -> j = 1

        // Shift elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {  // arr[0] > 90 -> 80 > 90 (false) -> arr[1] > 60 -> 90 > 60 (true)
            arr[j + 1] = arr[j];
            j = j - 1; // j = -1
        }
        arr[j + 1] = key; // place key at its correct position -> arr[1] = 90
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