#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// AVL tree node structure
struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
};
//Function declarations
int maxheight(int x, int y); 
int balanceFactor(Node* AVLNode); 
Node* balance(Node* root, int BF);
Node* findMax(Node* node); 
int height(Node* AVLNode); 
Node* createNode(int data); 
Node* insertNode(Node* AVLNode, int data); 
Node* deleteNode(Node* AVLNode, int data); 
Node* rightRotate(Node* a); 
Node* leftRotate(Node* a); 

// Utility function to create a new node
Node* createNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Utility function to calculate height of a node
int height(Node* AVLNode) {
    if (AVLNode == NULL) {
        return 0;
    }
    return AVLNode->height;
}

int maxheight(int x, int y) {
    return (x > y) ? x : y;
}

// Utility function to find the maximum node
Node *findMax(Node *node) {
    if (node->right == NULL) {
        return node;
    } else {
        return findMax(node->right);
    }
}

// Utility function to insert a node with value val into the AVL tree rooted at AVLNode
Node* insertNode(Node* AVLNode, int data) {
    if (AVLNode == NULL) {
        return createNode(data);
    }
    if (data < AVLNode->data) {
        AVLNode->left = insertNode(AVLNode->left, data);
    } else if (data > AVLNode->data) {
        AVLNode->right = insertNode(AVLNode->right, data);
    } else {
        return AVLNode;
    }
    //update Height(AVLNode);
    int leftHeight = height(AVLNode->left);
    int rightHeight = height(AVLNode->right);
    AVLNode->height = 1+ maxheight(leftHeight, rightHeight);

    int BF = balanceFactor(AVLNode);
    AVLNode = balance(AVLNode, BF);

    return AVLNode;
}

// Utility function to delete a node with value val from the AVL tree rooted at AVLNode
Node* deleteNode(Node* AVLNode, int data) {
    if (AVLNode == NULL) {
	  return AVLNode;
    }
    else if (data < AVLNode->data) {
        AVLNode->left = deleteNode(AVLNode->left, data);
    } else if (data > AVLNode->data) {
        AVLNode->right = deleteNode(AVLNode->right, data);
    } else {
	  // Node with no child
        if (AVLNode->left == NULL && AVLNode->right == NULL) {
            delete AVLNode;
            AVLNode = NULL;
        }
	  
	  // Node with left child
        else if (AVLNode->right == NULL && AVLNode->left != NULL) {
            Node* tempNode = AVLNode;
            delete tempNode;
            AVLNode = AVLNode->left;
        }

	  // Node with right child
	  else if (AVLNode->right != NULL && AVLNode->left == NULL) {
		Node* tempNode = AVLNode;
		delete tempNode;
		AVLNode = AVLNode->right;
	  }
	  // Node with right and left child
	  else {
	  	Node* tempNode = findMax(AVLNode->left);
        	AVLNode->data = tempNode->data;
        	AVLNode->left = deleteNode(AVLNode->left, tempNode->data);
	  }
    }
    if (AVLNode == NULL) {
	    return NULL;
    }
    //update Height(AVLNode);
    int leftHeight = height(AVLNode->left);
    int rightHeight = height(AVLNode->right);
    AVLNode->height = 1+ maxheight(leftHeight, rightHeight);

    int BF = balanceFactor(AVLNode);
    AVLNode = balance(AVLNode, BF);

    return AVLNode;
}

// Utility function to calculate balance factor of a node
int balanceFactor(Node* AVLNode) {
    if (AVLNode == NULL) {
        return 0;
    }
    return height(AVLNode->left) - height(AVLNode->right);
}

// Utility function to perform left rotation on a node
Node* leftRotate(Node* a) {
    Node* c = a->right;
    Node* c1 = c->left;
    c->left = a;
    a->right = c1;
    // Update Height of a & c
    a->height = 1 + maxheight(height(a->left), height(a->right));
    c->height = 1 + maxheight(height(c->left), height(c->right));

    return c;
}

// Utility function to perform right rotation on a node
Node* rightRotate(Node* a) {
    Node* b = a->left;
    Node* b1 = b->right;
    b->right = a;
    a->left = b1;
    // Update Height of a & b
    a->height = 1 + maxheight(height(a->left), height(a->right));
    b->height = 1 + maxheight(height(b->left), height(b->right));
    return b;
}

// Utility function to perform the balance of AVL tree
Node* balance(Node* root, int BF) {
    if (BF > 1) {
        if (height(root->left->left) >= height(root->left->right)) {
            root = rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
    } else if (BF < -1) {
        if (height(root->right->right) >= height(root->right->left)) {
            root = leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
    }
    return root;
}

// in-order traversal of the tree
void printinOrder(Node *node) {
    if (node == NULL)
        return;
    printinOrder(node->left);
    cout << node->data << " ";
    printinOrder(node->right);
}

// pre-order traversal of the tree
void printpreOrder(Node *root) {
    if (root == NULL)
        return;
    cout << root->data << " ";
    printpreOrder(root->left);
    printpreOrder(root->right);
}

// post-order traversal of the tree
void printpostOrder(Node *node) {
    if (node == NULL)
        return;
    printpostOrder(node->left);
    printpostOrder(node->right);
    cout << node->data << " ";
}

// extract integer from a string
int extractIntegerStrings(string inputStr)
{
    string intStr = inputStr.substr(1);
    // Convert the integer string to an integer
    int IntegerData = std::stoi(intStr);
    // Return the integer data
    return IntegerData;
}

int main()
{
    string input;
    getline(cin, input);

    istringstream ss(input);
    string subString;
    vector<string> subStrings;
    int num = 0;

    // devide string and restore value in array
    while (ss >> subString)
    {
        subStrings.push_back(subString);
        num++;
    }
    string *arr = new string[num];
    int i = 0;
    for (const auto &str : subStrings)
    {
        arr[i] = str;
        i++;
    }

    string in;
    Node *root = NULL;

    for (int i = 0; i < num; i++)
    {
        in = arr[i];

        if (in.find('A') != string::npos)
        {
            root = insertNode(root, extractIntegerStrings(in));
        }
        if (in.find('D') != string::npos)
        {
            root = deleteNode(root, extractIntegerStrings(in));
        }
    }
    if (root != NULL)
    {
        if (arr[num - 1] == "IN")
        {
            printinOrder(root);
        }
        else if (arr[num - 1] == "PRE")
        {
            printpreOrder(root);
        }
        else
        {
            printpostOrder(root);
        }
    }
    else
    {

        cout << "EMPTY";
    }

    return 0;
}