#include <iostream>
#include <stdexcept>

using namespace std;

class Deque {
private:
    int* items;
    int rear;  // enter index
    int front; // out index
    int capacity;

public:
    Deque(int capacity) {
        front = rear = -1;
        this -> capacity = capacity;
        items = new int[capacity];
    }

    bool isFull() {  // Overflow
        return (front == ((rear + 1) % capacity));
    }

    bool isEmpty() {  // Underflow
        return (front == -1 && rear == -1);
    }

    void insertRear(int value) {
        if (isFull()) {
            cout << "Queue is Full" << endl;
            return;
        }
        else if (isEmpty()) {
            front = rear = 0;
        }
        else {
            rear = (rear + 1) % capacity;
        }
        items[rear] = value;  // Enqueue
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        else if (front == rear) { // Last Element in queue
            cout << "Last element " << items[front] << " will be dequeued" << endl;
            front = rear = -1; // Now queue is empty
        }
        else {
            cout << "Dequeued elememnt from front is " << items[front] << endl; 
            front =  (front +1) % capacity; // Dequeue
        }
    }

    void insertFront(int value) {
        if (isFull()) {
            cout << "Queue is Full" << endl;
            return;
        }
        else if (isEmpty()) {
            front = rear = 0;
        }
        else {
            front = (front - 1 + capacity) % capacity;
        }
        items[front] = value;  // Enqueue
    }

    // Another Implemtention Way 
    // void insertFront(int value) {
    //     if ((front == 0 && rear == capacity - 1) || (front == rear + 1)) {  // Full
    //         cout << "Queue is Full" << endl;
    //         return;
    //     }
    //     else if (front == -1 && rear == -1) { // Empty
    //         front = rear = 0;
    //     }
    //     else if (front == 0) { // front at 0 but rear not at the end of array
    //         front = capacity - 1; // round front to the end of array
    //     }
    //     else {
    //         front--;
    //     }
    //     items[front] = value;  // Enqueue
    // }


    void deleteRear() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        else if (front == rear) { // Last Element in queue
            cout << "Last element " << items[front] << " will be dequeued" << endl;
            front = rear = -1; // Now queue is empty
        }
        else {
            cout << "Dequeued elememnt from rear is " << items[rear] << endl; 
            rear = (rear - 1 + capacity) % capacity; // Dequeue
        }
    }    
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        else {
            int i = front;
            while (i != rear)
            {
                cout << items[i] << " ";
                i = (i + 1) % capacity;
            }
            cout << items[i] << " "; // last element
            cout << endl;
        }
    }

    int getFront() {
        if (isEmpty()) {
            throw runtime_error("Queue is Empty");
        }
        return items[front];
    }

    ~Deque() {
        delete[] items;
    }
};

int main() {
    Deque q(5);
    q.insertFront(2);  // 2
    q.insertFront(5);  // 5 2
    q.insertRear(-1);  // 5 2 -1
    q.insertRear(0);   // 5 2 -1 0
    q.insertFront(7);  // 7 5 2 -1 0
    q.insertFront(4);  // Overflow

    q.display();

    cout << "Front element : " << q.getFront() << endl;

    q.deleteFront(); // 5 2 -1 0
    q.display();

    q.deleteFront(); // 2 -1 0
    q.display();

    q.deleteRear();  // 2 -1
    q.display();

    q.deleteFront(); // 0
    q.display();

    q.deleteRear();
    q.display();  // empty

    q.deleteFront();  // queue is empty - underflow
    return 0;
}