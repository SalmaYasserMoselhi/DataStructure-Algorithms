#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class Node {
    public:
        T data;
        Node<T>* prev;
        Node<T>* next;

        Node(T data) {
            this -> data = data;
            this -> prev = NULL;
            this ->  next = NULL;
        }
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    
    Node<T>* getNode(T data) {
        Node<T>* curr = head;
        while (curr != NULL) {
            if (curr -> data == data)
                return curr;
            curr = curr -> next;
        }
        return NULL; // Node with given data not found
    }

public:
    LinkedList() { // Default constructor 
        head = NULL;
        tail = NULL;
    }

    LinkedList(T data) { // Parameterized constructor
        Node<T>* newNode = new Node<T>(data);
        head = tail = newNode;
    }

    void insertAtFront(T data) {
        // Create new node
        Node<T>* newNode = new Node<T>(data);

        // LinkedList is empty
        if (head == NULL) {
            head = tail = newNode;
            return;
        }

        // LinkedList is not empty
        newNode -> next = head;
        head -> prev = newNode;
        head = newNode;
    }

    void insertAtEnd(T data) {
        // Create a new node
        Node<T>* newNode = new Node<T>(data);

        // LinkedList is empty
        if (tail == NULL) {
            head = tail = newNode;
            return;
        }

        // LinkedList is not empty
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
    }

    void InsertAfter(T data, T afterData) {
        Node<T>* currNode = getNode(afterData);
        if (currNode == NULL)
            return;
        
        // Create a new node
        Node<T>* newNode = new Node<T>(data);

        // Store the next node
        Node<T>* nextNode = currNode -> next;

        // Inserting the new node after the given node
        currNode -> next = newNode;
        newNode -> prev = currNode;
        
        if (nextNode != NULL) {
            newNode -> next = nextNode;
            nextNode -> prev = newNode;
        } else {
            tail = newNode; // new node inserted at the end
        }
    }

    void insertBefore(T data, T beforeData) {
        Node<T>* currNode = getNode(beforeData);
        if (currNode == NULL)
            return;

        // Create a new node
        Node<T>* newNode = new Node<T>(data);

        // Store the previous node
        Node<T>* prevNode = currNode -> prev;

        // Inserting the new node before the given node
        newNode -> next = currNode;
        currNode -> prev = newNode;
        if (prevNode != NULL) {
            newNode -> prev = prevNode;
            prevNode -> next = newNode;
        }
        else {
            head = newNode; // new node inserted at the front
        }
    }

    Node<T>* getHead() {
        return head;
    }

    int gerCount() {
        int count = 0;
        Node<T>* curr = head;
        while(curr != NULL) {
            count++;
            curr = curr -> next;
        }
        return count;
    }

    T getDataByIndex(int index) {
        int count = 0;
        Node<T>* curr = head;
        while (curr != NULL) {
            if (count == index) 
                return curr -> data;
            count++;
            curr = curr -> next;
        }
        return T(); // Index out of bounds
    }

    void removeNode(T data) {
        Node<T>* currNode = getNode(data);
        if(currNode == NULL)
            return;

        // Node to be deleted is the only node in the list
        if (head == tail) {
            head = tail = NULL;
        }
        // Node to be deleted is the head node
        else if (currNode == head) {
            head = currNode -> next;
            head -> prev = NULL; // remove connection
        }
        // Node to be deleted is the tail node
        else if (currNode == tail) {
            tail = currNode -> prev;
            tail -> next = NULL; // remove connection
        }
        // Node to be deleted is in the middle
        else {
            Node<T>* prevNode = currNode -> prev;
            Node<T>* nextNode = currNode -> next;

            prevNode -> next = nextNode;
            nextNode -> prev = prevNode;
        }

        delete currNode; // Free memory
    }

    void removeAllOccurrences(T data) {
        Node<T>* curr = head;
        while (curr !=NULL) {
            if (curr -> data == data) {
                Node<T>* nodeToDelete = curr;

                // Move curr to next node before deleting
                curr = curr -> next;

                // Node to be deleted is the only node in the list
                if (head == tail) {
                    head = tail = NULL;
                }
                // Node to be deleted is the head node
                else if (nodeToDelete == head) {
                    head = nodeToDelete -> next;
                    head -> prev = NULL; // remove connection
                }
                // Node to be deleted is the tail node
                else if (nodeToDelete == tail) {
                    tail = nodeToDelete -> prev;
                    tail -> next = NULL; // remove connection
                }
                // Node to be deleted is in the middle
                else {
                    Node<T>* prevNode = nodeToDelete -> prev;
                    Node<T>* nextNode = nodeToDelete -> next;

                    prevNode -> next = nextNode;
                    nextNode -> prev = prevNode;
                }
            
                delete nodeToDelete; // Free memory
            }
            else 
                curr = curr -> next;
        }
    }

    void display() {
        Node<T>* curr = head;
        while (curr !=NULL) {
            cout << curr -> data << " ";
            curr = curr -> next;
        }
        cout << endl;
    }
};
#endif