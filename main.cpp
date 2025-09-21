#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int val;
        int height;
        Node* left;
        Node* right;

        Node(int v) : val(v), height(0), left(nullptr), right(nullptr) {};
};

class Tree {
    public:
        Node* head;
        Tree() : head(nullptr) {};

        int calculateFactors(Node*& curr) {
            if (curr == nullptr) return 0;

            int a = curr->left == nullptr ? -1 : curr->left->height;
            int b = curr->right == nullptr ? -1 : curr->right->height;

            curr->height = 1 + max(a, b);

            return a - b; // balance factor
        }

        Node* leftLeftRotation(Node*& curr) {
            Node* Y = curr->left->right;
            Node* B = curr->left;

            B->right = curr;
            curr->left = Y;

            calculateFactors(curr);
            calculateFactors(B);

            return B;
        }

        Node* rightRightRotation(Node*& curr) {
            Node* Y = curr->right->left;
            Node* B = curr->right;

            B->left = curr;
            curr->right = Y;

            calculateFactors(curr);
            calculateFactors(B);

            return B;
        }

        Node* leftRightRotation(Node*& curr) {
            Node* A = curr->left;
            Node* B = curr->left->right;

            A->right = B->left;
            B->left = A;
            curr->left = B;

            calculateFactors(A);
            calculateFactors(B);

            return leftLeftRotation(curr);
        } 

        Node* rightLeftRotation(Node*& curr) {
            Node* A = curr->right;
            Node* B = curr->right->left;

            A->left = B->right;
            B->right = A;
            curr->right = B;

            calculateFactors(A);
            calculateFactors(B);

            return rightRightRotation(curr);
        }

        void insertNode(int val) {
            head = insertNodeHelper(head, val);
        }

        Node* insertNodeHelper(Node*& curr, int v) {
            if (curr == nullptr) return new Node(v);

            if (curr->val > v) {
                curr->left = insertNodeHelper(curr->left, v);
            } else if (curr->val < v) {
                curr->right = insertNodeHelper(curr->right, v);
            } else {
                return curr;
            }

            int x = calculateFactors(curr);

            if (x > 1 && calculateFactors(curr->left) >= 0) curr = leftLeftRotation(curr);
            if (x > 1 && calculateFactors(curr->left) < 0) curr = leftRightRotation(curr);
            if (x < -1 && calculateFactors(curr->right) <= 0) curr = rightRightRotation(curr);
            if (x < -1 && calculateFactors(curr->right) > 0) curr = rightLeftRotation(curr);

            return curr;
        }

        void deleteNode(int val) {
            head = deleteNodeHelper(head, val);
        }

        Node* deleteNodeHelper(Node*& curr, int v) {
            if (curr == nullptr) return nullptr;

            if (curr->val > v) {
                curr->left = deleteNodeHelper(curr->left, v);
            } else if (curr->val < v) {
                curr->right = deleteNodeHelper(curr->right, v);
            } else {

                if (curr->right == nullptr || curr->left == nullptr) {
                    Node* temp = curr->left == nullptr ? curr->right : curr->left;

                    delete curr;

                    return temp;
                } else {
                    Node* temp = curr->left;

                    while (temp->right != nullptr) {
                        temp = temp->right;
                    }

                    curr->val = temp->val;
                    curr->left = deleteNodeHelper(curr->left, temp->val);
                }
            }

            if (curr == nullptr) return nullptr;

            int x = calculateFactors(curr);

            if (x > 1 && calculateFactors(curr->left) >= 0) curr = leftLeftRotation(curr);
            if (x > 1 && calculateFactors(curr->left) < 0) curr = leftRightRotation(curr);
            if (x < -1 && calculateFactors(curr->right) <= 0) curr = rightRightRotation(curr);
            if (x < -1 && calculateFactors(curr->right) > 0) curr = rightLeftRotation(curr);

            return curr;
        }

        // traversal
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

        void inOrder(Node* curr) {
            if (curr == nullptr) return;

            inOrder(curr->left);
            cout << curr->val << ' ';
            inOrder(curr->right);
        }

        void preOrder(Node* curr) {
            if (curr == nullptr) return;

            cout << curr->val << ' ';
            preOrder(curr->left);
            preOrder(curr->right);
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

        int val = stoi(token.substr(1));

        if (opp == 'A') {
            t.insertNode(val);
        } else {
            t.deleteNode(val);
        }
    }

    t.printTree(token);

    return 0;
}