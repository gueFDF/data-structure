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
    cout<<tree.get_root()->get_data()<<endl;
    cout<<tree.Find(tree.get_root(),15)->get_data()<<endl;
    cout<<tree.Find(tree.get_root(),9)->get_data()<<endl;
    cout<<tree.Find(tree.get_root(),7)->get_data()<<endl;
    cout<<tree.FindMax(tree.get_root())->get_data()<<endl;
     tree.set_root(tree.Delete(tree.get_root(),15));
    cout<<tree.FindMax(tree.get_root())->get_data()<<endl;
            
}