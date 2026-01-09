#include <iostream>
#include <queue>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// ================= gotoxy =================
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// ================= Colors =================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================= Header UI =================
void printHeader(string title) {
    setColor(11);
    cout << "==========================================\n";
    cout << "       " << title << "       \n";
    cout << "==========================================\n";
}

// ================= Node =================
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// ================= Binary Tree =================
class BinaryTree {
public:
    Node* root;
    BinaryTree() { root = nullptr; }

    void insert(int val) {
        Node* newNode = new Node(val);
        if (!root) {
            root = newNode;
            return;
        }
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();

            if (!temp->left) {
                temp->left = newNode;
                return;
            }
            q.push(temp->left);

            if (!temp->right) {
                temp->right = newNode;
                return;
            }
            q.push(temp->right);
        }
    }

    void printBinaryShape(Node* root) {
        if (!root) return;
        setColor(11);
        cout << "\n           (" << root->data << ")\n";
        if (root->left || root->right) {
            cout << "          /    \\\n";
            if (root->left) cout << "       (" << root->left->data << ")"; else cout << "          ";
            if (root->right) cout << "    (" << root->right->data << ")"; cout << endl;
        }
        if (root->left && (root->left->left || root->left->right)) {
            cout << "       /  \\\n";
            if (root->left->left) cout << "    (" << root->left->left->data << ")"; else cout << "        ";
            if (root->left->right) cout << " (" << root->left->right->data << ")"; cout << endl;
        }
        setColor(15);
    }

    void printTreeShape() { printBinaryShape(root); }

    // --- Traversals ---
    void preorder(Node* r, int x, int &y, vector<int>& order) {
        if (!r) return;
        gotoxy(x, y++); setColor(14);
        cout << "Visit Node " << r->data;
        order.push_back(r->data);
        preorder(r->left, x, y, order);
        preorder(r->right, x, y, order);
    }

    void inorder(Node* r, int x, int &y, vector<int>& order) {
        if (!r) return;
        inorder(r->left, x, y, order);
        gotoxy(x, y++); setColor(10);
        cout << "Visit Node " << r->data;
        order.push_back(r->data);
        inorder(r->right, x, y, order);
    }

    void postorder(Node* r, int x, int &y, vector<int>& order) {
        if (!r) return;
        postorder(r->right, x, y, order);
        postorder(r->left, x, y, order);
        gotoxy(x, y++); setColor(12);
        cout << "Visit Node " << r->data;
        order.push_back(r->data);
    }

    // --- Properties ---
    int height(Node* r, int x, int &y) {
        if (!r) return -1;
        int lh = height(r->left, x, y);
        int rh = height(r->right, x, y);
        int h = 1 + max(lh, rh);
        gotoxy(x, y++); setColor(10);
        cout << "Height of node " << r->data << " = " << h;
        return h;
    }

    void printLevels(int x, int y) {
        if (!root) return;
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        int currentLevel = -1, maxLevel = 0;
        gotoxy(x, y++); setColor(14);
        cout << "LEVEL ANALYSIS:";
        while (!q.empty()) {
            Node* temp = q.front().first;
            int level = q.front().second;
            q.pop();
            if (level != currentLevel) {
                currentLevel = level;
                maxLevel = max(maxLevel, level);
                gotoxy(x, y++); setColor(11);
                cout << "Level " << level << " -> ";
            }
            cout << temp->data << " ";
            if (temp->left) q.push({temp->left, level + 1});
            if (temp->right) q.push({temp->right, level + 1});
        }
        y++;
        gotoxy(x, y++); setColor(10);
        cout << "TOTAL LEVELS IN TREE = " << maxLevel + 1;
    }

    void printRootChildParent(int x, int y) {
        if (!root) return;
        gotoxy(x, y++); setColor(14);
        cout << "ROOT NODE: " << root->data;
        gotoxy(x, y++); setColor(11);
        cout << "PARENT NODES: ";
        queue<Node*> q; q.push(root);
        while (!q.empty()) {
            Node* temp = q.front(); q.pop();
            if (temp->left || temp->right) cout << temp->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        gotoxy(x, y++); setColor(10);
        cout << "CHILD NODES: ";
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front(); q.pop();
            if (temp->left) cout << temp->left->data << " ";
            if (temp->right) cout << temp->right->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
};

int main() {
    BinaryTree tree;
    int choice, n, val;

    while (true) {
        system("cls");
        printHeader("BINARY TREE VISUALIZER");
        setColor(14); 
        cout << "\n1. Insert Nodes\n2. Properties Menu\n3. Traversal Visuals\n4. Exit\n";
        setColor(15); cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter number of nodes: "; cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Value for node " << i + 1 << ": "; cin >> val;
                tree.insert(val);
            }
        }
        else if (choice == 2) {
            int propChoice;
            system("cls");
            printHeader("TREE PROPERTIES");
            tree.printTreeShape();
            gotoxy(60, 2); setColor(13); cout << "--- SELECTION ---";
            gotoxy(60, 3); cout << "1. Total Tree Height";
            gotoxy(60, 4); cout << "2. Total Levels";
            gotoxy(60, 5); cout << "3. Parent/Child Info";
            gotoxy(60, 7); cout << "Choice: "; cin >> propChoice;

            system("cls");
            printHeader("PROPERTY RESULT");
            tree.printTreeShape();
            int y = 5;
            if (propChoice == 1) {
                int totalH = tree.height(tree.root, 60, y);
                y++;
                gotoxy(60, y++); setColor(13);
                cout << "FINAL TREE HEIGHT = " << totalH;
            }
            else if (propChoice == 2) tree.printLevels(60, y);
            else if (propChoice == 3) tree.printRootChildParent(60, y);
            getch();
        }
        else if (choice == 3) {
            system("cls");
            printHeader("TRAVERSAL SEQUENCE");
            tree.printTreeShape();
            int y = 5;
            vector<int> order;

            gotoxy(60, y++); setColor(15); cout << "--- PREORDER ---";
            tree.preorder(tree.root, 60, y, order);
            gotoxy(60, y++); setColor(14); cout << "Final Order: ";
            for (int v : order) cout << v << " ";
            y += 2; order.clear();

            gotoxy(60, y++); setColor(15); cout << "--- INORDER ---";
            tree.inorder(tree.root, 60, y, order);
            gotoxy(60, y++); setColor(10); cout << "Final Order: ";
            for (int v : order) cout << v << " ";
            y += 2; order.clear();

            gotoxy(60, y++); setColor(15); cout << "--- POSTORDER (R, L, Root) ---";
            tree.postorder(tree.root, 60, y, order);
            gotoxy(60, y++); setColor(12); cout << "Final Order: ";
            for (int v : order) cout << v << " ";

            getch();
        }
        else if (choice == 4) break;
    }
    return 0;
}