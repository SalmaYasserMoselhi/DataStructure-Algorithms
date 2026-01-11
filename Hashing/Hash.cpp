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
    int key; // data -> hashfunction input -> hashcode
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
            table[i] = NULL; // each pointer points to NULL. AVOID wild pointer
        }
    }

    int HashFunction(int key)
    {
        // data == (key)
        int index = key % size; // keep it in range
        /* 
        Example: size = 5
        data = 1  -> index = 1
        data = 5  -> index = 0
        data = 15 -> index = 0
        Result:
        0: 15 -> 5 -> NULL
        1: 1 -> NULL
        2: NULL
        3: NULL
        4: NULL
        */
        return index;
    }

    void insert(int key)
    {
        /*
        Example: Insert 15 into hash table of size 5
        HashFunction(15) = 15 % 5 = 0
        
        Before insert:
        0: 5 -> 10 -> NULL
        
        Step 1: Create newNode
        newNode -> 15 -> NULL
        
        Step 2: newNode->next = table[0]
        newNode -> 15 -> 5 -> 10 -> NULL
        
        Step 3: table[0] = newNode
        0: newNode -> 15 -> 5 -> 10 -> NULL
        
        After insert:
        0: 15 -> 5 -> 10 -> NULL
        */
        
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
        /*
        Example: Search for key 5 in hash table
        HashFunction(5) = 5 % 5 = 0
        
        List at index 0:
        0: curr -> 15 -> 5 -> 10 -> NULL
        
        Step 1: curr->key = 15, not equal to 5
                curr = curr->next
        0: 15 -> curr -> 5 -> 10 -> NULL
        
        Step 2: curr->key = 5, equal to 5
                return true (found!)
        */
        
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
        /*
        Example: Remove key 20 from hash table
        HashFunction(20) = 20 % 10 = 0
        
        Initial state:
        prev  curr
         |      |
        NULL   0: 15 -> 5 -> 20 -> 25 -> NULL
        
        Step 1: curr->key = 15, not equal to 20
                prev = curr, curr = curr->next
                
               prev  curr
                 |     |
        0: 15 -> 5 -> 20 -> 25 -> NULL
        
        Step 2: curr->key = 5, not equal to 20
                prev = curr, curr = curr->next
                
                      prev  curr
                       |     |
        0: 15 -> 5 -> 20 -> 25 -> NULL
        
        Step 3: curr->key = 20, equal to 20 (found!)
                prev is NOT NULL (Case 2)
                prev->next = curr->next
                
                      prev        curr
                       |           |
        0: 15 -> 5 ------------> 25 -> NULL
                  (skips 20)
        
        Step 4: delete curr (free memory for node 20)
        
        Final state:
        0: 15 -> 5 -> 25 -> NULL
        */
        
        int index = HashFunction(key);
        Node *curr = table[index];
        Node *prev = NULL;

        while (curr != NULL)
        {
            if (curr->key == key)
            {
                // Case1: key is at the head of linked list
                /*
                Example: Remove 15 from: 0: 15 -> 5 -> 20 -> NULL
                
                prev  curr
                 |     |
                NULL  0: 15 -> 5 -> 20 -> NULL
                
                table[0] = curr->next
                
                0: 5 -> 20 -> NULL
                */
                if (prev == NULL)
                {
                    table[index] = curr->next;
                }
                // Case2: key is in middle or end of linked list
                else
                {
                    prev->next = curr->next;
                }
                delete curr; // free memory
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void display()
    {
        /*
        Example output:
        Index 0: 40 -> 30 -> 20 -> 10 -> NULL
        Index 1: NULL
        Index 2: 12 -> 32 -> NULL
        Index 3: 3 -> NULL
        Index 4: NULL
        Index 5: 25 -> 5 -> 15 -> NULL
        Index 6: NULL
        Index 7: 17 -> 7 -> NULL
        Index 8: NULL
        Index 9: NULL
        
        Traversal for Index 0:
        curr
         |
        40 -> 30 -> 20 -> 10 -> NULL
        
              curr
               |
        40 -> 30 -> 20 -> 10 -> NULL
        
                    curr
                     |
        40 -> 30 -> 20 -> 10 -> NULL
        
                          curr
                           |
        40 -> 30 -> 20 -> 10 -> NULL
        
                                curr
                                 |
        40 -> 30 -> 20 -> 10 -> NULL (stop, curr == NULL)
        */
        
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
        /*
        Example: Destructor cleanup for index 0
        0: 15 -> 5 -> 20 -> NULL
        
        Step 1: curr = table[0]
        curr
         |
        15 -> 5 -> 20 -> NULL
        
        Step 2: temp = curr, curr = curr->next, delete temp
        temp      curr
         |         |
        15 -> 5 -> 20 -> NULL
        (delete 15)
        
        Step 3: temp = curr, curr = curr->next, delete temp
              temp  curr
               |     |
        5 -> 20 -> NULL
        (delete 5)
        
        Step 4: temp = curr, curr = curr->next, delete temp
                    temp  curr
                     |     |
        20 -> NULL
        (delete 20)
        
        Step 5: curr == NULL, exit loop
        */
        
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
        delete[] table; // after deleting all linked lists -> delete the table
    }
};

// leetcode 141. Linked List Cycle
class Solution
{
public:
    bool hasCycle(Node *head)
    {
        /*
        Example: Linked list with cycle
        1 -> 2 -> 3 -> 4
             ^         |
             |_________|
        
        Step 1: curr = 1
                search(1) -> false
                insert(1)
                HashTable: {1}
        
        Step 2: curr = 2
                search(2) -> false
                insert(2)
                HashTable: {1, 2}
        
        Step 3: curr = 3
                search(3) -> false
                insert(3)
                HashTable: {1, 2, 3}
        
        Step 4: curr = 4
                search(4) -> false
                insert(4)
                HashTable: {1, 2, 3, 4}
        
        Step 5: curr = 2 (back to node 2, cycle!)
                search(2) -> TRUE (already visited!)
                return true (cycle detected)
        */
        
        Node *curr = head;
        if (curr == NULL || curr->next == NULL)
            return false;

        HashTable ht(1000); // size of hash table
        while (curr != NULL)
        {
            if (ht.search(curr->key))
            {
                return true;
            }
            ht.insert(curr->key);
            curr = curr->next;
        }
        return false;
    }
};

int main()
{
    Solution sol;
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = head->next; // create a cycle
    if (sol.hasCycle(head))
    {
        cout << "Cycle detected in the linked list." << endl;
    }
    else
    {
        cout << "No cycle in the linked list." << endl;
    }

    // HashTable ht(10); // size of hash table
    // ht.insert(10);    // 10 % 10 = 0
    // ht.insert(20);    // 20 % 10 = 0 (collision with 10)
    // ht.insert(15);    // 15 % 10 = 5
    // ht.insert(7);     // 7 % 10 = 7
    // ht.insert(32);    // 32 % 10 = 2
    // ht.insert(5);     // 5 % 10 = 5 (collision with 15)
    // ht.insert(3);     // 3 % 10 = 3
    // ht.insert(12);    // 12 % 10 = 2 (collision with 32)
    // ht.insert(17);    // 17 % 10 = 7 (collision with 7)
    // ht.insert(25);    // 25 % 10 = 5 (collision with 15 and 5)
    // ht.insert(30);    // 30 % 10 = 0 (collision with 10 and 20)
    // ht.insert(40);    // 40 % 10 = 0 (collision with 10, 20 and 30)

    // ht.display();

    // int keysToSearch[] = {15, 99, 7, 40, 100};
    // for (int key : keysToSearch)
    // {
    //     if (ht.search(key))
    //     {
    //         cout << "Key " << key << " found in hash table." << endl;
    //     }
    //     else
    //     {
    //         cout << "Key " << key << " not found in hash table." << endl;
    //     }
    // }

    // cout << "Removing key 40 from hash table." << endl;
    // ht.remove(40);
    // ht.display();

    return 0;
}