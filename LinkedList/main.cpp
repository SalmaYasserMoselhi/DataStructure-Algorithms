#include "LinkedList.h"

int main() {
    LinkedList<int> list; // Create a linked list without initial node
    list.insertAtFront(5); // 5
    list.insertAtFront(2); // 2 5
    list.display();

    list.insertAtEnd(15); // 2 5 15
    list.insertAtEnd(20); // 2 5 15 20
    list.display();

    // Node* foundNode = list.getNode(15);
    // if (foundNode != NULL) {
    //     cout << "Node found with data: " << foundNode -> data << endl;
    // } else {
    //     cout << "Node not found." << endl;
    // }

    list.InsertAfter(10, 5); // 2 5 10 15 20
    list.display();

    list.InsertAfter(25, 20); // 2 5 10 15 20 25
    list.display();

    list.insertBefore(1, 2); // 1 2 5 10 15 20 25
    list.display();

    list.insertBefore(12, 15); // 1 2 5 10 12 15 20 25
    list.display();

    cout << "Total nodes in the list: " << list.gerCount() << endl;

    cout << "Data at index 3: " << list.getDataByIndex(3) << endl;

    list.removeNode(10); // 1 2 5 12 15 20 25
    list.display();

    list.removeNode(1); // 2 5 12 15 20 25
    list.display();

    list.removeNode(25); // 2 5 12 15 20
    list.display();

    list.insertAtEnd(15); // 2 5 12 15 20 15
    list.insertAtFront(15); // 15 2 5 12 15 20 15
    list.display();

    list.removeAllOccurrences(15); // 2 5 12 20
    list.display();
    return 0;
}