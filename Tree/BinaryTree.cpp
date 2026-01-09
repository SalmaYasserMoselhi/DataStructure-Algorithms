#include <iostream>
using namespace std;

/*
Data structure classification:
    Linear: arrays, linked lists, stack, queue
    Non-linear: tree, graph

Tree — informal definition:
    A collection of entities (nodes) linked together to simulate a hierarchy.
    Root: the topmost node (no parent).
    Leaf node: a node with no children.
    Internal node: a node with one or more children.

Relationships and basic terms:
    Parent: **immediate predecessor** of a node.
    Child: **immediate successor** of a node.
    Sibling: nodes that share the same parent.
    Ancestor: **any predecessor** on the path from the root to that node (parent, grandparent, ...).
    Descendant: **any successor** on paths from that node down to leaves (children, grandchildren, ...).
    Path: sequence of nodes connected by edges.
    Degree of a node: number of children that node has.
    Degree of a tree: maximum degree among all nodes in the tree.

Depth / level / height:
    Depth of a node: length of the path from the root to that node (often root depth = 0).
    Level of a node: sometimes defined as depth (root at level 0).
    Height of a node: number of edges in the longest path from that node down to a leaf.
    Height of a tree: height of the root node.

Useful observations:
    Leaves have height 0.
    A node is internal if its degree > 0.
    Depth increases as you move down from the root; height increases as you move up toward the root.
*/

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this -> data = data;
        this -> left = NULL;
        this -> right = NULL;
    }

    ~Node() {}
};

class BST {
private:
    Node* root;
public:
    BST() {
        root = NULL;
    }

    void add(int value) {
        // Create Node
        Node* newNode = new Node(value);

        // Build Connections
        // Tree Empty No Root
        if (root ==NULL) {
            root = newNode;
        }
        // Tree Not Empty
        else {
            Node* curr = root; // Jump
            Node* parent = NULL; // Jump-1
            while (curr != NULL) {
                parent = curr;
                if (value < curr -> data) {
                    curr = curr -> left; // Move curr to left
                } else {
                    curr = curr -> right;
                }
            }

            // Connect New Node
            if (value < parent -> data) {
                parent -> left = newNode;
            } else {
                parent -> right = newNode;
            }
        }
    }

    bool contains(int value) {
        return getNode(value) != NULL;
    }

    int getParent(int childValue) {
        Node* child = getNode(childValue);  // Find Node
        if (child != NULL) {
            Node* parent = getParentHelper(child); // Find Parent
            if (parent != NULL) {
                return parent -> data;
            } else {
                return -1; // Root has no parent
            }
        }
        return -5; // Child Not Found
    }

    void removeNode(int value) {
        Node* target = getNode(value);
        if(target == NULL) return; // Node Not Found

        // Case 1: Target is Root
        if (target == root) {
            // Only Root Node
            if (root -> left == NULL && root -> right == NULL) {
                delete root;
                root = NULL;
            }
            // Root has only right subtree
            else if (root -> left == NULL) {
                Node* temp = root;
                root = root -> right;
                delete temp;
            }
            // Root has only left subtree
            else if (root -> right == NULL) {
                Node* temp = root;
                root = root -> left;
                delete temp;
            }
            // Root has both left and right subtree
            else {
                // Solution1: Get Max from Left Subtree
                // Node* maxLeft = getRightMost(root -> left);

                // Solution2: Get Min from Right Subtree
                // Node* minRight = getLeftMost(root -> right);

                // Solution3: NOT RECOMMENDED - Make left subtree as new root
                // root -> left becomes new root
                Node* newRoot = root -> left;
                // Conneect old right subtree to the rightmost of new root
                Node* maxRight = getRightMost(newRoot);
                maxRight -> right = root -> right;
                // Delete old root
                delete root;
                // Update root pointer
                root = newRoot;

            }
        }
        else {  // Remove Non-Root Node
            Node* parent = getParentHelper(target);
            // Case 2: Target is Leaf Node
            if (target -> left == NULL && target -> right == NULL) {
                if (parent -> left == target) {
                    parent -> left = NULL;
                } else {
                    parent -> right = NULL;
                }
            }
            // Case 3: Target has only left subtree
            else if (target -> right == NULL) {
                if (parent -> left == target) {
                    parent -> left = target -> left;
                } else {
                    parent -> right = target -> left;
                }
            }
            // Case 4: Target has only right subtree
            else if (target -> left == NULL) {
                if (parent -> left == target) {
                    parent -> left = target -> right;
                } else {
                    parent -> right = target -> right;
                }
            }
            // Case 5: Target has both left and right subtree
            else {
                // NOT RECOMMENDED - Make left subtree as new subtree root
                Node* newSubtreeRoot = target -> left;
                // Connect old right subtree to the rightmost of new subtree root
                Node* maxRight = getRightMost(newSubtreeRoot);
                maxRight -> right = target -> right;

                // Connect new subtree root to parent
                if (parent -> left == target) {
                    parent -> left = newSubtreeRoot;
                } else {
                    parent -> right = newSubtreeRoot;
                }
            }
            // Delete target node
            delete target;
        }
    }
    
    void displayAsc() {  // LDR
        traverseInorder(root);
    }

    void displacePreOrder() { // DLR - USED FOR COPING TREE
        traversePreorder(root);
    }

    void displayPostOrder() {  // LRD - USED FOR DELETING TREE
        traversePostorder(root);
    }


    int getMaxDepth() {
        return getMaxDepthHelper(root);
    }
   
private:
    int getMaxDepthHelper(Node* node) {
        if (node == NULL) {
            return 0;
        }
        int leftDepth = getMaxDepthHelper(node -> left);
        int rightDepth = getMaxDepthHelper(node -> right);
        return max(leftDepth, rightDepth) + 1; // +1 for current node
    }

    Node* getNode(int value) {
        Node* curr = root; // Jump
        while (curr != NULL) {
            if (value == curr -> data) {
                return curr; // Found
            } else if (value < curr -> data) {
                curr = curr -> left;
            } else {
                curr = curr -> right;
            }
        }
        return NULL; // Not Found
    }
    
    Node* getParentHelper(Node* child) {
        if (child == root) {
            return NULL; // Root has no parent
        }
        Node* parent = root;
        while(parent != NULL) {
            if (parent -> left == child || parent -> right == child) {
                return parent; // Found Parent
            }
            else {
                // Jump
                if(child -> data < parent -> data) {
                    parent = parent -> left;
                } else {
                    parent = parent -> right;
                }
            }
        }
    }

    // Inorder Predecessor
    Node* getRightMost(Node* node) { // Maximum in Left Subtree is the **Rightmost Node**
        if (node == NULL) return NULL;
        while (node -> right !=NULL) {
            node = node -> right;
        }
        return node;
    }

    // Inorder Successor
    Node* getLeftMost(Node* node) { // Minimum in Right Subtree is the **Leftmost Node**
        if (node == NULL) return NULL;
        while (node -> left !=NULL) {
            node = node -> left;
        }
        return node;
    }

    // LDR
    void traverseInorder(Node* node) {
        if (node != NULL) {
            // Traverse left subtree
            traverseInorder(node -> left);

            // Visit Node
            cout << node -> data << " ";

            // Traverse left subtree
            traverseInorder(node -> right);
        }
    }

    void traversePreorder(Node* node) {  // DLR
        if (node != NULL) {
            // Visit Node
            cout << node->data << " ";

            // Traverse left subtree
            traversePreorder(node->left);

            // Traverse left subtree
            traversePreorder(node->right);
        }
    }


    void traversePostorder(Node* node) {  // LRD
        if (node != NULL) {
            // Traverse left subtree
            traversePostorder(node->left);
            
            // Traverse left subtree
            traversePostorder(node->right);
            
            // Visit Node
            cout << node->data << " ";
        }
    }
};

int main() {
    BST tree;
    tree.add(50);
    tree.add(40);
    tree.add(30);
    tree.add(60);
    tree.add(70);
    tree.add(65);
    tree.add(25);
    tree.add(45);
    tree.add(47);

    tree.displayAsc();

    tree.contains(25) ? cout << "\nFound\n" : cout << "\nNot Found\n";
    tree.contains(100) ? cout << "Found\n" : cout << "Not Found\n";

    // tree.removeNode(50);
    // cout << "Removing 50:\n";
    // int parent = tree.getParent(50);  // Not Found
    // parent == -1 ? cout << "Root\n" : parent == -5 ? cout << "<<Not Found>>\n" : cout << "Parent = " << parent << "\n";
   
    // int parent1 = tree.getParent(40);  // Root
    // parent1 == -1 ? cout << "Root\n" : parent1 == -5 ? cout << "<<Not Found>>\n" : cout << "Parent = " << parent1 << "\n";

    // int parent2 = tree.getParent(60);  // 47
    // parent2 == -1 ? cout << "Root\n" : parent2 == -5 ? cout << "<<Not Found>>\n" : cout << "Parent = " << parent2 << "\n";
   

    int depth = tree.getMaxDepth();
    cout << "Max Depth of Tree: " << depth << "\n";
    return 0;
}