#include <iostream>
#include "LinkedList.h"
using namespace std;

/*
Bubble Sort Algorithm for Linked List
Time Complexity: O(n^2)
Space Complexity: O(1)
*/

template <typename T>
void bubbleSort(Node<T>* head) {
    // Empty list or single node -> already sorted
    if (head == NULL || head -> next == NULL) {
        return;
    }

    Node<T>* end = NULL;  // Marks the sorted portion (from end)
    bool swapped = false;

    do {
        swapped = false;
        Node<T>* curr = head;

        // Traverse until we reach the sorted portion
        while (curr -> next != end) {
            // Compare adjacent elements
            if (curr -> data > curr -> next -> data) {
                // Swap data values
                T temp = curr -> data;
                curr -> data = curr -> next -> data;
                curr -> next -> data = temp;
                
                swapped = true;
            }
            curr = curr -> next;
        }
        
        // After each pass, the largest element goes to the end
        end = curr;
        
    } while (swapped);
}


int main() {
    LinkedList<int> list;
    list.insertAtEnd(64);
    list.insertAtEnd(34);
    list.insertAtEnd(25);
    list.insertAtEnd(12);
    list.insertAtEnd(22);
    list.insertAtEnd(11);
    list.insertAtEnd(90);

    cout << "Before Bubble Sort: ";
    list.display();

    bubbleSort(list.getHead());

    cout << "After Bubble Sort:  ";
    list.display();

    LinkedList<int> sortedList;
    sortedList.insertAtEnd(1);
    sortedList.insertAtEnd(2);
    sortedList.insertAtEnd(3);
    sortedList.insertAtEnd(4);
    sortedList.insertAtEnd(5);

    cout << "\nAlready sorted list: ";
    sortedList.display();
    
    bubbleSort(sortedList.getHead());
    
    cout << "After Bubble Sort:   ";
    sortedList.display();

    LinkedList<int> reverseList;
    reverseList.insertAtEnd(5);
    reverseList.insertAtEnd(4);
    reverseList.insertAtEnd(3);
    reverseList.insertAtEnd(2);
    reverseList.insertAtEnd(1);

    cout << "\nReverse sorted list: ";
    reverseList.display();
    
    bubbleSort(reverseList.getHead());
    
    cout << "After Bubble Sort:   ";
    reverseList.display();
    
    return 0;
}
