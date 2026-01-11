#include <iostream>
#include <stdexcept>

using namespace std;

class Queue {
private:
    int* items;
    int rear;  // enter index
    int front; // out index
    int capacity;

public:
    Queue(int capacity) {
        front = rear = -1;
        this -> capacity = capacity;
        items = new int[capacity];
    }

    //       f r
    // 0 1 2 3 4  
    //       4 5

    bool isFull() {  // Overflow
        return (front == ((rear + 1) % capacity)); // 4 + 1 % 5 == 0
    }

    bool isEmpty() {  // Underflow
        return (front == -1 && rear == -1);
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is Full" << endl;
            return;
        }
        else if (isEmpty()) {
            front = rear = 0;
        }
        else {
            rear = (rear + 1) % capacity; // 4 + 1 % 5 == 0 (keep it circular (in range of 0 -> size - 1))
        }
        items[rear] = value;  // Enqueue
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        else if (front == rear) { // Last Element in queue
            cout << "Last element " << items[front] << " will be dequeued" << endl;
            front = rear = -1; // Now queue is empty
        }
        else {
            // f r       
            // 0 1 2 3 4  
            // 6 8     
            cout << "Dequeued elememnt is " << items[front] << endl; 
            front =  (front +1) % capacity; // Dequeue  --> 3 + 1 % 5 == 4  --> 4 + 1 % 5 == 0
        }
    }
    // when enqueue rear = (rear + 1) % capacity
    // when dequeue front = (front + 1) % capacity
    // to check full front == (rear + 1) % capacity
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        else {
            //   r   f          
            // 0 1 2 3 4  
            // 9 8   3 4
            int i = front; // 3
            while (i != rear)
            {
                cout << items[i] << " "; // items[3], items[4], items[0], items[1] 
                i = (i + 1) % capacity; // 3 + 1 % 5 == 4  --> 4 + 1 % 5 == 0 --> 0 + 1 % 5 == 1
            }
            cout << items[i] << " "; // last element
            cout << endl;
        }
    }

    int peek() { // front element 
        if (isEmpty()) {
            throw runtime_error("Queue is Empty");
        }
        else {
            return items[front];
        }
    }

    ~Queue() {
        delete[] items;
    }
};

int main() {
    Queue q(5);
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    q.enqueue(25);
    q.enqueue(30);
    q.display();

    cout << "Front element is: " << q.peek() << endl;

    q.enqueue(35); // Overflow

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue(); // Underflow

    q.display(); // Empty

    if (!q.isEmpty())
        cout << "Front element is: " << q.peek() << endl;
    else
        cout << "Empty" << endl;

    q.enqueue(-1); // -1
    q.enqueue(1);  // -1 1
    q.enqueue(5);  // -1 1 5
    q.display();

    q.dequeue();   //   1 5
    q.enqueue(2);  //   1 5 2
    q.enqueue(3);  //   1 5 2 3
    q.enqueue(4);  // 4 1 5 2 3
    q.display();

    return 0;
}