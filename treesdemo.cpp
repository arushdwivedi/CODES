#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node *buildTree(node *root)
{

    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    if (data == -1)
    {

        return NULL;
    }
    root = new node(data);

    cout << "Enter data for inserting in left of " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << data << endl;
    root->right = buildTree(root->right);
    return root;
}

void levelOrderTraversal(node *root)
{
    queue<node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();

        if (temp == NULL)
        {
            // purana level complete traverse ho chuka hai
            cout << endl;
            if (!q.empty())
            {
                // queue still has some child ndoes
                q.push(NULL);
            }
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
            {
                q.push(temp->left);
            }

            if (temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}

void inorder(node *root)
{
    // base case
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node *root)
{
    // base case
    if (root == NULL)
    {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node *root)
{
    // base case
    if (root == NULL)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void buildFromLevelOrder(node *&root)
{
    queue<node *> q;

    cout << "Enter data for root" << endl;
    int data;
    cin >> data;
    root = new node(data);

    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();

        cout << "Enter left node for: " << temp->data << endl;
        int leftData;
        cin >> leftData;

        if (leftData != -1)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }

        cout << "Enter right node for: " << temp->data << endl;
        int rightData;
        cin >> rightData;

        if (rightData != -1)
        {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}
pair<int, int> diameterfast(node *root)
{
    if (root == NULL)
    {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }
    pair<int, int> left = diameterfast(root->left);
    pair<int, int> right = diameterfast(root->right);
    int op1 = left.first;
    int op2 = right.first;
    int op3 = left.second + right.second;

    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3));
    ans.second = max(left.second, right.second) + 1;
    return ans;
}
int diameter(node *root)
{
    return diameterfast(root).first;
}
pair<bool, int> balancedtreefast(node *root)
{
    if (root == NULL)
    {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    pair<bool, int> left = balancedtreefast(root->left);
    pair<bool, int> right = balancedtreefast(root->right);
    bool leftans = left.first;
    bool rightans = right.first;
    bool diff = abs(left.second - right.second) <= 1;
    pair<bool, int> ans;
    if (diff && leftans && rightans)
        ans.first = true;
    else
        ans.first = false;

    ans.second = max(left.second, right.second) + 1;
    return ans;
}
int isbalancedtree(node *root)
{
    return balancedtreefast(root).first;
}
bool identicaltree(node *r1, node *r2)
{
    if (r1 == NULL && r2 == NULL)
        return true;
    if (r1 == NULL && r2 != NULL)
        return false;
    if (r1 != NULL && r2 == NULL)
        return false;

    bool checkleft = identicaltree(r1->left, r2->left);
    bool checkright = identicaltree(r1->right, r2->right);
    bool valcheck = r1->data == r2->data;
    if (checkleft && checkright && valcheck)
        return true;
    else
        return false;
}
pair<bool, int> isSumTreeFast(node *root)
{
    if (root == NULL)
    {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    if (root->left == NULL && root->right == NULL)
    {
        pair<bool, int> p = make_pair(true, root->data);
        return p;
    }
    pair<bool, int> leftcheck = isSumTreeFast(root->left);
    pair<bool, int> rightcheck = isSumTreeFast(root->right);
    bool isleftsumtree = leftcheck.first;
    bool isrightsumtree = rightcheck.first;
    bool condn = root->data == leftcheck.second + rightcheck.second;
    pair<bool, int> ans;
    ans.second = root->data + leftcheck.second + rightcheck.second;
    if (condn && isleftsumtree && isrightsumtree)
        ans.first = true;
    else
        ans.first = false;
    return ans;
}
vector<int> boundary(node *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    ans.push_back(root->data);
    leftTraversal(root->left, ans);
    LeafNodes(root->left, ans);
    LeafNodes(root->right, ans);
    RightTraversal(root->right, ans);
    return ans;
}
void leftTraversal(node *root, vector<int> &a)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return;

    a.push_back(root->data);
    if (root->left)
        leftTraversal(root->left, a);
    else
        leftTraversal(root->right, a);
}
void RightTraversal(node *root, vector<int> &a)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return;

    if (root->right)
        RightTraversal(root->right, a);
    else
        RightTraversal(root->left, a);
    a.push_back(root->data);
}
void LeafNodes(node *root, vector<int> &a)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        a.push_back(root->data);
        return;
    }
    LeafNodes(root->left, a);
    LeafNodes(root->right, a);
}
vector<int> topView(node *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    map<int, int> topNodes;
    queue<pair<node *, int>> q;
    q.push(make_pair(root, 0));
    while (!q.empty())
    {
        pair<node *, int> temp = q.front();
        q.pop();
        node *frontnode = temp.first;
        int hd = temp.second;

        if (topNodes.find(hd) == topNodes.end())
        {
            topNodes[hd] = frontnode->data;
        }
        if (frontnode->left)
            q.push(make_pair(frontnode->left, hd - 1));
        if (frontnode->right)
            q.push(make_pair(frontnode->right, hd + 1));
    }
    for (auto i : topNodes)
        ans.push_back(i.second);
}
void solve(node *root, vector<int> &ans, int level)
{
    // base case
    if (root == NULL)
        return;

    // we entered into a new level
    if (level == ans.size())
        ans.push_back(root->data);

    solve(root->left, ans, level + 1);
    solve(root->right, ans, level + 1);
}

vector<int> leftView(node *root)
{
    vector<int> ans;
    solve(root, ans, 0);
    return ans;
}
int main()
{

    node *root = NULL;

    buildFromLevelOrder(root);
    levelOrderTraversal(root);
    // 1 3 5 7 11 17 -1 -1 -1 -1 -1 -1 -1

    /*
    //creating a Tree
    root = buildTree(root);
    //1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
    //level order
    cout << "Printing the level order tracersal output " << endl;
    levelOrderTraversal(root);

    cout << "inorder traversal is:  ";
    inorder(root);

    cout << endl << "preorder traversal is:  ";
    preorder(root);

    cout << endl << "postorder traversal is:  ";
    postorder(root);
    */

    return 0;
}