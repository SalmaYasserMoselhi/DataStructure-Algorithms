#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string key;
    string value;
    Node *next;

    Node(string key, string value)
    {
        this->key = key;
        this->value = value;
        next = NULL;
    }
};
class HashTable {
    int size;
    Node** table;

public:
    HashTable(int size) {
        this->size = size;
        table = new Node*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }

    // key  --->  hash function  --->  index
    /*
        table[5] -> ("age", 21) -> ("language", "C++") -> NULL (In case of "age" and "language" both hash to index 5)
    */
    int HashFunction(string key) {
        int hash = 0;
        for (char ch : key) {
            hash = hash * 31 + ch;
        }
        return abs(hash) % size;
    }

    // insert or update
    void put(string key, string value) {
        // say "name" hashes to index 3 and also "age" hashes to index 3 and user put("name", "Salma") and if i have 3: ("name", "Salma Yasser") -> NULL it will be updated to 3: ("name", "Salma") -> NULL
        int index = HashFunction(key); 
        Node* curr = table[index];

        // check if key already exists -> update value
        while (curr != NULL) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // insert new key
        // in case of collision, we add the new node at the beginning of the linked list 
        // ex: put("age", "21") so now we have 3: ("age", "21") -> ("name", "Salma Yasser") -> NULL
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // get value by key
    bool get(string key, string& result) {
        int index = HashFunction(key);
        Node* curr = table[index];

        while (curr != NULL) {
            if (curr->key == key) {
                result = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void remove(string key) {
        int index = HashFunction(key);
        Node* curr = table[index];
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->key == key) {
                if (prev == NULL)
                    table[index] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            Node* curr = table[i];
            while (curr != NULL) {
                cout << "(" << curr->key << ", " << curr->value << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* curr = table[i];
            while (curr != NULL) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

int main() {
    HashTable dict(10);

    dict.put("name", "Salma");
    dict.put("age", "21");
    dict.put("country", "Egypt");
    dict.put("language", "C++");
    dict.put("name", "Salma Yasser"); // update

    dict.display();

    string value;
    if (dict.get("name", value))
        cout << "name = " << value << endl;
    else
        cout << "name not found\n";

    dict.remove("age");
    cout << "\nAfter removing age:\n";
    dict.display();

    return 0;
}
