#include <iostream>
#include "LinkedList.h"
using namespace std;

/*
Linear Search Algorithm for Linked List
Time Complexity: O(n)
Space Complexity: O(1)

Traverses the linked list from head to end,
checking each node's data against the target value.
Returns pointer to the node if found, NULL otherwise.
*/

template <typename T>
Node<T>* linearSearch(Node<T>* head, T target) {
    Node<T>* curr = head;

    // Traverse the linked list
    while (curr != NULL) {
        // Check if current node's data matches target
        if (curr -> data == target) {
            return curr;
        }
        curr = curr -> next;
    }

    return NULL;
}


int main() {
    LinkedList<int> list;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);

    cout << "Linked List: ";
    list.display();

    Node<int>* result;

    result = linearSearch(list.getHead(), 30);
    if (result != NULL) {
        cout << "Found 30 in the list" << endl;
    } else {
        cout << "30 not found in the list" << endl;
    }

    result = linearSearch(list.getHead(), 100);
    if (result != NULL) {
        cout << "Found 100 in the list" << endl;
    } else {
        cout << "100 not found in the list" << endl;
    }

    result = linearSearch(list.getHead(), 10);
    if (result != NULL) {
        cout << "Found 10 (head) in the list" << endl;
    } else {
        cout << "10 not found in the list" << endl;
    }

    result = linearSearch(list.getHead(), 50);
    if (result != NULL) {
        cout << "Found 50 (tail) in the list" << endl;
    } else {
        cout << "50 not found in the list" << endl;
    }
    
    return 0;
}
