#include "AVLtree.hpp"
int main()
{
    AVLTree<int> tree;
    tree.insert(tree.root, 16);
    tree.insert(tree.root, 4);
    tree.insert(tree.root, 8);
    tree.insert(tree.root, 9);
    tree.insert(tree.root, 6);
    tree.insert(tree.root, 6);
    tree.insert(tree.root, 6);
    tree.insert(tree.root, 6);
    tree.insert(tree.root, 6);
    tree.insert(tree.root, 3);
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 19);
    tree.insert(tree.root, 19);
    tree.insert(tree.root, 19);
    tree.insert(tree.root, 19);
    tree.insert(tree.root, 19);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 30);
    tree.inOrder(tree.root);
    std::cout << std::endl;
    std::cout << "root: " << tree.root->key << std::endl;

    tree.remove(tree.root, 4);
    tree.inOrder(tree.root);
    std::cout << std::endl;

    tree.remove(tree.root, 9);
    tree.inOrder(tree.root);
    std::cout << std::endl;
    tree.remove(tree.root, 16);
    tree.inOrder(tree.root);
    std::cout << std::endl;
    tree.remove(tree.root, 20);
    tree.inOrder(tree.root);
    std::cout << std::endl;
    tree.remove(tree.root, 30);
    tree.inOrder(tree.root);
    std::cout << std::endl;
    tree.remove(tree.root, 30);
    tree.inOrder(tree.root);
    std::cout << std::endl;

    tree.remove(tree.root, 30);
    tree.inOrder(tree.root);
    std::cout << std::endl;
    tree.remove(tree.root, 30);
    tree.inOrder(tree.root);
    std::cout << std::endl;

    tree.remove(tree.root, 30);
    tree.inOrder(tree.root);
    std::cout << std::endl;


    return 0;
}