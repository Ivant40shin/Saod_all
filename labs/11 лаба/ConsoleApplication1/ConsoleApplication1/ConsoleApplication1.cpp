#include <iostream>
#include <vector>

struct Node 
{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) 
{
    Node* newNode = new Node();
    if (!newNode) 
    {
        std::cout << "Memory error\n";
        return nullptr;
    }
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* convertForestToBinaryTree(std::vector<std::vector<int>>& forest) 
{
    Node* root = nullptr;
    for (int i = 0; i < forest.size(); i++) 
    {
        Node* prev = nullptr;
        for (int j = 0; j < forest[i].size(); j++) 
        {
            Node* temp = createNode(forest[i][j]);
            if (j == 0) 
            {
                if (root == nullptr) 
                {
                    root = temp;
                }
                else 
                {
                    Node* ptr = root;
                    while (ptr->right != nullptr) 
                    {
                        ptr = ptr->right;
                    }
                    ptr->right = temp;
                }
            }
            else 
            {
                prev->left = temp;
            }
            prev = temp;
        }
    }
    return root;
}

void printInorder(Node* temp) 
{
    if (temp == nullptr)
        return;

    printInorder(temp->left);
    std::cout << temp->data << ' ';
    printInorder(temp->right);
}

int main() 
{
    std::vector<std::vector<int>> forest = { {1, 2}, {3, 4, 5, 6}, {7, 8, 9} };
    Node* root = convertForestToBinaryTree(forest);
    printInorder(root);
    return 0;
}
