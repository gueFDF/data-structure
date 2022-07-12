#include"bintree.hpp"
using namespace bintree;
int main()
{
    BinTree tree;
    /*--------------------------------------------------------------------------*/
    cout<<"请输入二叉树前序序列进行建树，'#'代表空节点："<<endl;
    tree.set_root(tree.create_tree());
    cout<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"前序遍历的结果：";
    tree.pre_order(tree.get_root());
    cout<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"中序遍历的结果：";
    tree.in_order(tree.get_root());
    cout<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"后序遍历的结果：";
    tree.past_order(tree.get_root());
    cout<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"层次遍历的结果：";
    tree.level_order(tree.get_root());
    cout<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"该二叉树叶子节点的个数：";
    cout<<tree.get_leaf_num(tree.get_root())<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"该二叉树的高度是：";
    cout<<tree.get_tree_height(tree.get_root())<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    tree.swap_left_right(tree.get_root());
    cout<<"交换左右子树之后的先序遍历结果为：";
    tree.pre_order(tree.get_root());
    cout<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    BinTreeNode *p1 = tree.get_root()->get_left()->get_right();
    BinTreeNode *p2 = tree.get_root()->get_left()->get_left();
    BinTreeNode *p3 = tree.get_root()->get_right()->get_right()->get_right();
    cout<<p1->get_data()<<" 和 "<<p2->get_data()<<"的最近公共祖先是：";
    BinTreeNode *p = tree.get_nearest_common_father(tree.get_root(),p1,p2);
    cout<<p->get_data()<<endl;
    cout<<p1->get_data()<<" 和 "<<p3->get_data()<<"的最近公共祖先是：";
    p = tree.get_nearest_common_father(tree.get_root(),p1,p3);
    cout<<p->get_data()<<endl<<endl;
    /*--------------------------------------------------------------------------*/
    cout<<"路径如下："<<endl;
    tree.print_rout(tree.get_root(),12);
    return 0;
}