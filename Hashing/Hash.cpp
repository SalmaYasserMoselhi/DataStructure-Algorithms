#include <iostream>
using namespace std;

/*
Hashing is a technique used in data structures that efficiently stores and retrieves data in a way that allows for quick access.
involves mapping data to a specific index "hash code" using a hash function. This index is then used to store and retrieve the data in a hash table.
We can achieve average time complexity of O(1) for search, insert, and delete operations using hashing.
*/

/*
HashTable:
- key (data)
- Hash Function
- Table index (array of pointers)
- Collision Handling

*/
class Node
{
public:
    int key; // data
    Node *next;

    Node(int key)
    {
        this->key = key;
        next = NULL;
    }
};

class HashTable
{
    int size;
    // Dynamic array of pointers -> each element contains pointer to linked list
    Node **table;

public:
    HashTable(int size)
    {
        this->size = size;
        // Create array of pointers
        table = new Node *[size];
        for (int i = 0; i < size; i++)
        {
            table[i] = NULL; // each pointer points to run. AVOID wild pointer
        }
    }

    int HashFunction(int key)
    {                           // data == (key)
        int index = key % size; // keep it in range
        return index;
    }

    void insert(int key)
    {
        // Create new node
        Node *newNode = new Node(key);

        // Get index using hash function
        int index = HashFunction(key);

        // Insert node at the beginning of linked list at table[index]
        newNode->next = table[index];
        table[index] = newNode;
    }

    bool search(int key)
    {
        int index = HashFunction(key);
        Node *curr = table[index];
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                return true; // key found
            }
            curr = curr->next;
        }
        return false; // key not found
    }

    void remove(int key)
    {
        int index = HashFunction(key);
        Node *curr = table[index];
        Node *prev = NULL;
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                // Case1: key is at the head of linked list
                if (prev == NULL)
                {
                    table[index] = curr->next;
                }
                // Case2: key is in middle or end of linked list
                else
                {
                    prev->next = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Index " << i << ": ";
            Node *curr = table[i]; // get pointer to first node in linked list for the index i
            while (curr != NULL)
            {
                cout << curr->key << " -> ";
                curr = curr->next;
            }
            cout << "NULL" << endl;
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < size; i++)
        {
            Node *curr = table[i]; // get pointer to first node in linked list for the index i
            while (curr != NULL)
            {
                Node *temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table; // after deleting all linked lists -> delete all table
    }
};

int main()
{
    HashTable ht(10); // size of hash table
    ht.insert(10);    // 10 % 10 = 0
    ht.insert(20);    // 20 % 10 = 0 (collision with 10)
    ht.insert(15);    // 15 % 10 = 5
    ht.insert(7);     // 7 % 10 = 7
    ht.insert(32);    // 32 % 10 = 2
    ht.insert(5);     // 5 % 10 = 5 (collision with 15)
    ht.insert(3);     // 3 % 10 = 3
    ht.insert(12);    // 12 % 10 = 2 (collision with 32)
    ht.insert(17);    // 17 % 10 = 7 (collision with 7)
    ht.insert(25);    // 25 % 10 = 5 (collision with 15 and 5)
    ht.insert(30);    // 30 % 10 = 0 (collision with 10 and 20)
    ht.insert(40);    // 40 % 10 = 0 (collision with 10, 20 and 30)

    ht.display();

    int keysToSearch[] = {15, 99, 7, 40, 100};
    for (int key : keysToSearch)
    {
        if (ht.search(key))
        {
            cout << "Key " << key << " found in hash table." << endl;
        }
        else
        {
            cout << "Key " << key << " not found in hash table." << endl;
        }
    }

    cout << "Removing key 40 from hash table." << endl;
    ht.remove(40);
    ht.display();

    return 0;
}