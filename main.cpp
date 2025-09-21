#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int val;
        int height;
        int bf;
        Node* left;
        Node* right;

        Node(int v) : val(v), height(0), bf(0), left(nullptr), right(nullptr) {};
};

class Tree {
    public:
        Node* head;
        Tree() : head(nullptr) {};

        void insert(int& val) {
            insertHelper(head, val);
        }

        void insertHelper(Node*& curr, int& v) {
            if (curr == nullptr) {
                curr = new Node(v);
                return;
            }

            if (curr->val > v) {
                insertHelper(curr->left, v);
            } else {
                insertHelper(curr->right, v);
            }            
            
            int a = curr->left == nullptr ? 0 : curr->left->height;
            int b = curr->right == nullptr ? 0 : curr->right->height;
            curr->height = 1 + max(a, b);

            calculateBF(curr);
            balanceTree(curr);
        }

        void deleteNode(int val) {
            deleteNodeHelper(head, val);
        }

        // find node to delete
        // -> if node not found, do nothing
        // if found search for right most node in the left subtree 
        // swap nodes and repeat down

        Node* deleteNodeHelper(Node*& curr, int& v) {
            // deleting leaf
            if (curr == nullptr) return nullptr;

            if (curr->val > v) {
                curr->left = deleteNodeHelper(curr->left, v);
            } else if (curr->val < v) {
                curr->right = deleteNodeHelper(curr->right, v);
            } else {
                if (curr->left == nullptr && curr->right == nullptr) {
                    delete curr;
                    return nullptr;
                }

                if (curr->left != nullptr && curr->right != nullptr) {
                    Node* temp = curr->left;
                    while (temp->right != nullptr) {
                        temp = temp->right;
                    }

                    curr->val = temp->val;

                    curr->left = deleteNodeHelper(curr->left, temp->val); // fix the tree
                } else {
                    Node* temp = curr->left == nullptr ? curr->right : curr->left;
                    *curr = *temp;
                    delete temp;
                }
            }

            int a = curr->left == nullptr ? 0 : curr->left->height;
            int b = curr->right == nullptr ? 0 : curr->right->height;
            curr->height = 1 + max(a, b);
            calculateBF(curr);
            balanceTree(curr);
            return curr;
        }

        void balanceTree(Node*& curr) {
            if (curr->bf < -1 && curr->right->bf < 0) rightRightRotation(curr);
            if (curr->bf < -1 && curr->right->bf > 0) rightLeftRotation(curr);     
            if (curr->bf > 1 && curr->left->bf > 0) leftLeftRotation(curr);
            if (curr->bf > 1 && curr->left->bf < 0) leftRightRotation(curr);
        } 

        void calculateBF(Node*& curr) {
            if (curr == nullptr) return;
            int l = curr->left == nullptr ? 0 : curr->left->height+1;
            int r = curr->right == nullptr ? 0 : curr->right->height+1;

            curr->bf = l - r;
        }

        void leftLeftRotation(Node*& curr) {
            Node* temp = curr->left; // B sub tree

            curr->left = temp->right; // A left set to B right

            temp->right = curr; // B left set to A

            curr = temp; // A set to B

            curr->right->height = curr->height - 1;
            calculateBF(curr->right);
            calculateBF(curr);
        }

        void rightRightRotation(Node*& curr) {
            Node* temp = curr->right; // just left-left but swap left and right

            curr->right = temp->left;

            temp->left = curr;

            curr = temp;

            curr->left->height = curr->height - 1;
            calculateBF(curr->left);
            calculateBF(curr);
        }

        void leftRightRotation(Node*& curr) {
            Node* temp = curr->left->right;
            
            curr->left->right = temp->left;

            temp->left = curr->left;

            curr->left = temp;
            
            (curr->left->height)++;

            (curr->left->left->height)--;

            calculateBF(curr->left->left);
            calculateBF(curr->left);
            calculateBF(curr);

            leftLeftRotation(curr);
        }

        void rightLeftRotation(Node*& curr) {
            Node* temp = curr->right->left; // just right left but left <-> right
            
            curr->right->left = temp->right;

            temp->right = curr->right;

            curr->right = temp;
            
            (curr->right->height)++;

            (curr->right->right->height)--;

            calculateBF(curr->right->right);
            calculateBF(curr->right);
            calculateBF(curr);

            rightRightRotation(curr);
        }

        void printTree(string order) {
            if (head == nullptr) {
                cout << "EMPTY" << endl;
                return;
            }
            if (order == "IN") {
                inOrder(head);
            } else if (order == "POST") {
                postOrder(head);
            } else {
                preOrder(head);
            }

            cout << endl;
        }

        void preOrder(Node* curr) {
            if (curr == nullptr) return;

            preOrder(curr->left);
            cout << curr->val << ' ';
            preOrder(curr->right);
        }

        void inOrder(Node* curr) {
            if (curr == nullptr) return;

            cout << curr->val << ' ';
            inOrder(curr->left);
            inOrder(curr->right);
        }

        void postOrder(Node *curr) {
            if (curr == nullptr) return;

            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->val << ' ';
        }
};

int main(void) {

    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;

    Tree t;

    while (ss >> token) {
        if (token == "PRE" || token == "POST" || token == "IN") continue;
        char opp = token[0];
        char temp[token.size()];
        for (int i = 1; i < int(token.size()); ++i) {
            temp[i-1] = token[i];
        }
        int val = atoi(temp);

        if (opp == 'A') {
            t.insert(val);
        } else {
            t.deleteNode(val);
        }

    }

    t.printTree(token);

    return 0;
}