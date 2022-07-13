#include"bst.hpp"
using namespace BST;
int main()
{
    Bst tree;
    tree.set_root(tree.insert(tree.get_root(),15));
    tree.insert(tree.get_root(),7);
    tree.insert(tree.get_root(),9);
    tree.insert(tree.get_root(),6);
    tree.insert(tree.get_root(),3);
    tree.insert(tree.get_root(),7);
    tree.insert(tree.get_root(),9);
    tree.insert(tree.get_root(),56);
    tree.insert(tree.get_root(),3);
    tree.insert(tree.get_root(),3333);
    tree.insert(tree.get_root(),9);
    tree.insert(tree.get_root(),6);
    tree.insert(tree.get_root(),35);
    tree.insert(tree.get_root(),73);
    tree.insert(tree.get_root(),92);
    tree.insert(tree.get_root(),64);
    tree.insert(tree.get_root(),36);
     tree.in_order(tree.get_root());
    cout<<endl;
     tree.Delete(tree.get_root(),73);
     tree.in_order(tree.get_root());
      cout<<endl;
     tree.Delete(tree.get_root(),56);
     tree.in_order(tree.get_root());
     cout<<endl;
tree.Delete(tree.get_root(),64);
tree.in_order(tree.get_root());
 cout<<endl;


            
}