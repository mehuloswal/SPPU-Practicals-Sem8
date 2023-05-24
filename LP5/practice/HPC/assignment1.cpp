#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
#include <chrono>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : val(val), left(NULL), right(NULL) {}
};

void sequential_bfs(TreeNode *root)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left)
        {
            q.push(node->left);
        }
        if (node->right)
        {
            q.push(node->right);
        }
    }
}

void sequential_dfs(TreeNode *root)
{
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty())
    {
        TreeNode *node = s.top();
        s.pop();
        cout << node->val << " ";
        if (node->right)
        {
            s.push(node->right);
        }
        if (node->left)
        {
            s.push(node->left);
        }
    }
}

void parallel_bfs(TreeNode *root)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int qsize = q.size();
#pragma omp parallel
        {
#pragma omp for
            for (int i = 0; i < qsize; i++)
            {
                TreeNode *node;
#pragma omp critical
                {
                    node = q.front();
                    q.pop();
                }
                cout << node->val << " ";
                if (node->left)

                {
#pragma omp critical
                    q.push(node->left);
                }
                if (node->right)
                {
#pragma omp critical
                    q.push(node->right);
                }
            }
        }
    }
}

void parallel_dfs(TreeNode *root)
{
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty())
    {
        int sSize = s.size();
#pragma omp parallel
        {
#pragma omp for
            for (int i = 0; i < sSize; i++)
            {
                TreeNode *node;
#pragma omp critical
                {
                    node = s.top();
                    s.pop();
                }
                cout << node->val << " ";
                if (node->right)
                {
#pragma omp critical
                    {
                        s.push(node->right);
                    }
                }
                if (node->left)
                {
#pragma omp critical
                    {
                        s.push(node->left);
                    }
                }
            }
        }
    }
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->left->left = new TreeNode(8);

    cout << "\nSequential BFS traversal: ";
    auto start = chrono::high_resolution_clock::now();
    sequential_bfs(root);
    auto end = chrono::high_resolution_clock::now();
    cout << "\n Sequential BFS took: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    cout << "\nParallel BFS traversal: ";
    start = chrono::high_resolution_clock::now();
    parallel_bfs(root);
    end = chrono::high_resolution_clock::now();
    cout << "\n Parallel BFS took: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    cout << "\nSequential DFS traversal: ";
    start = chrono::high_resolution_clock::now();
    sequential_dfs(root);
    end = chrono::high_resolution_clock::now();
    cout << "\n Sequential DFS took: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    cout << "\nParallel DFS traversal: ";
    start = chrono::high_resolution_clock::now();
    parallel_dfs(root);
    end = chrono::high_resolution_clock::now();
    cout << "\n Parallel DFS took: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    return 0;
}