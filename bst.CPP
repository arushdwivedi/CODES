#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
    Node(int x)
    {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};
void LevelOrderTraversal(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(nullptr);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (temp == nullptr)
        {
            if (!q.empty())
                q.push(nullptr);
            cout << endl;
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
}
Node *insertIntoBst(Node *root, int data)
{
    if (root == nullptr)
    {
        root = new Node(data);
        return root;
    }
    if (data > root->data)
        root->right = insertIntoBst(root->right, data);
    else
        root->left = insertIntoBst(root->left, data);

    return root;
}
void TakeInput(Node *&root)
{
    int data;
    cout << "\n Enter value:";
    cin >> data;
    while (data != -1)
    {
        root = insertIntoBst(root, data);
        cout << "\n Enter value:";
        cin >> data;
    }
}

int main()
{
    cout << "\n Enter data to create BST:";
    Node *root = nullptr;
    TakeInput(root);
    LevelOrderTraversal(root);
}