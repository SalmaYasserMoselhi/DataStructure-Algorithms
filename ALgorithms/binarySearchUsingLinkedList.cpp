#include <iostream>
#include "LinkedList.h"
using namespace std;

/*
Ex: A -> B -> C -> D -> E -> NULL
start = A, end = NULL

iteration 0:
    start = A
    end = B
iteration 1:
    start = B
    end = D
iteration 2:
    start = B
    end = NULL --> (midlle = slow = B)

*/
template <typename T>
Node<T>* getMid(Node<T>* start, Node<T>* end) {
    Node<T>* slow = start;
    Node<T>* fast = start -> next;

     while (fast != end && fast->next != end)
    {
        // MOVE fast 2 steps & slow 1 step
        fast = fast -> next -> next;
        slow = slow -> next;
    }

    return slow;
}

template <typename T>
Node<T>* binarySearch(Node<T>* head, T target) {
    Node<T>* start = head;
    Node<T>* end = NULL;

    while (start != end) {
        Node<T>* mid = getMid(start, end);

        if (mid == NULL)
            return NULL;
        
        if (mid -> data == target)
        {
            return mid;
        }
        else if (mid -> data < target) {
            start = mid -> next;
        }
        else {
            end = mid;
        }
    }
    return NULL;
}


int main() {
    
    LinkedList<int> list;
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);
    
    cout << "Linked List: ";
    list.display();
    
    Node<int>* result = binarySearch(list.getHead(), 3);
    if (result != NULL) {
        cout << "Found 3 in the list" << endl;
    } else {
        cout << "3 not found in the list" << endl;
    }

    result = binarySearch(list.getHead(), 10);
    if (result != NULL) {
        cout << "Found 10 in the list" << endl;
    } else {
        cout << "10 not found in the list" << endl;
    }
    
    return 0;
}