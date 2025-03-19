
#include <iostream>

struct Tree {
    int val;
    Tree* left;
    Tree* right;

    Tree(int val) :
        val(val),
        left(nullptr),
        right(nullptr) {}

};

bool isBST(Tree *root, int min, int max) 
{
    if (root == nullptr) {
        return true;
    }

    if (root->val <= min && root->val >= max)
    {
        return false;
    }

    return isBST(root->left, min, root->val) && isBST(root->right, root->val, max);
}