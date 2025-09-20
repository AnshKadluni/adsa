#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int val;
        int height;
        int bf;
        Node* left;
        Node* right;

        Node(int v, int h) : val(v), height(h), bf(0), left(nullptr), right(nullptr) {};
};

int getBF(Node* curr);

int insert(Node*& curr, int val);

void traverse(Node*& curr);

void leftLeftRotation(Node*& curr);

int main(void) {

    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;

    Node* root = nullptr;

    while (ss >> token) {
        if (token == "PRE" || token == "IN" || token == "POST") break;
        char opp = token[0];
        char temp[token.size()];
        for (int i = 1; i < token.size(); ++i) {
            temp[i-1] = token[i];
        }
        int val = atoi(temp);

        insert(root, val);

    }

    //leftLeftRotation(root);
    traverse(root);

    return 0;
}

int getBF(Node* curr) {
    if (curr == nullptr) return 0;
    int bf = 0;
    if (curr->left != nullptr) bf += curr->left->height;
    if (curr->right != nullptr) bf -= curr->right->height;

    return bf;
}

int insert(Node*& curr, int val) {
    if (curr == nullptr) {
        curr = new Node(val, 0);
        return 1;
    }

    int x;

    if (curr->val < val) {
        x = insert(curr->right, val);   
    } else {
        x = insert(curr->left, val);
    }

    if (x > curr->height) {
        (curr->height)++;
    }     

    curr->bf = getBF(curr);

    if (curr->bf > 1) {
        int a = curr->left == nullptr ? 0 : curr->left->height + 1;
        int b = curr->right == nullptr ? 0 : curr->right->height + 1;
        if (a > b) leftLeftRotation(curr);
    }

    return curr->height+1;
}

void traverse(Node*& curr) {
    if (curr == nullptr) return;

    traverse(curr->left);
    cout << curr->val << ' ' << curr->height << ' ' << curr->bf << endl;
    traverse(curr->right);
}

void leftLeftRotation(Node*& curr) {

    Node* temp = curr->left; // B sub tree

    curr->left = temp->right; // A left set to B right

    temp->right = curr; // B left set to A

    curr = temp; // A set to B

    (curr->height)--;
    curr->right->height = curr->height;
    curr->right->bf = getBF(curr->right);
    curr->bf = getBF(curr);
}
