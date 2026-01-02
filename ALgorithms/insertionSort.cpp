#include <iostream>
#include "LinkedList.h"
using namespace std;

/*
Insertion Sort Algorithm for Doubly Linked List
Time Complexity: O(n^2)
Space Complexity: O(1)
*/

template <typename T>
void insertionSort(Node<T>* head) {
    // Empty list or single node -> already sorted
    if (head == NULL || head -> next == NULL) {
        return;
    }

    // Start from the second node
    Node<T>* current = head -> next;

    while (current != NULL) {
        // Store the key (current element to be positioned)
        T key = current -> data;
        
        // Start comparing with previous elements
        Node<T>* previous = current -> prev;

        // Shift elements greater than key to the right
        while (previous != NULL && previous -> data > key) {
            // Move previous node's data to the next position
            previous -> next -> data = previous -> data;
            previous = previous -> prev;
        }

        // Insert key at the correct position
        if (previous != NULL) {
            previous -> next -> data = key;
        } else {
            head -> data = key;
        }
        current = current -> next;
    }
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

    cout << "Before Insertion Sort: ";
    list.display();

    insertionSort(list.getHead());

    cout << "After Insertion Sort:  ";
    list.display();

    LinkedList<int> sortedList;
    sortedList.insertAtEnd(1);
    sortedList.insertAtEnd(2);
    sortedList.insertAtEnd(3);
    sortedList.insertAtEnd(4);
    sortedList.insertAtEnd(5);

    cout << "\nAlready sorted list:   ";
    sortedList.display();
    
    insertionSort(sortedList.getHead());
    
    cout << "After Insertion Sort:  ";
    sortedList.display();

    LinkedList<int> reverseList;
    reverseList.insertAtEnd(5);
    reverseList.insertAtEnd(4);
    reverseList.insertAtEnd(3);
    reverseList.insertAtEnd(2);
    reverseList.insertAtEnd(1);

    cout << "\nReverse sorted list:   ";
    reverseList.display();
    
    insertionSort(reverseList.getHead());
    
    cout << "After Insertion Sort:  ";
    reverseList.display();

    return 0;
}
