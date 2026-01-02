#include <iostream>
#include <stdexcept>


using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;


    Node(int data) {
        this -> data = data;
        this -> prev = NULL;
        this ->  next = NULL;
    }
};


class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() {
        front = NULL;
        rear = NULL;
    }

    bool isEmpty() {  // There is no queue list
        return front == NULL;
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
            return;
        }
        newNode -> prev = rear;
        rear -> next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (isEmpty()) {  // No elements to delete
            cout << "Queue is Empty" << endl;
            return;
        }

        // Store node before deletion to avoid memory leak
        Node* temp = front;

        // Delete Node 
        if (front == rear) { // one element
            front = rear = NULL;
        }
        else {
            front = front -> next;
            front -> prev = NULL;
        }
        delete temp;
    }

    void display() {
        if (isEmpty()) {  // No elements to display
            cout << "Queue is Empty" << endl;
            return;
        }
        Node* temp = front;
        while (temp != NULL) {
            cout << temp -> data << " ";
            temp = temp -> next;
        }
        cout << endl;
    }

    int peek() {
        if (isEmpty()) {
            throw runtime_error("Queue is Empty");
        }
        return front -> data;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

int main() {
    Queue q;
    q.enqueue(5);
    q.enqueue(7);
    q.enqueue(10);
    cout << "First Element: " << q.peek() << endl;
    q.display();

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.display();
    
    q.dequeue();



    return 0;
}