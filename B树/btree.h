#include <iostream>

class BTreeNode {
public:
  BTreeNode(int _t, bool _leaf); //构造函数
  //遍历所有以该节点为根的字数关键字
  void traverse();
  //查询一个关键字在以该节点为根的子树上
  BTreeNode *search(int k); //没找到返回NULL

  //插入操作(非满节点)
  void insertNonFull(int k);

  //拆分字节点y的函数,调用此函数的前提是字节点y是满的
  void spliChild(int i, BTreeNode *y);
  friend class BTree; //使BTree为友元类，可以访问私有成员
private:
  int *keys;     //关键字数组
  int t;         //最小度(定义了节点关键字的数量限制)
  BTreeNode **C; //节点对应孩子节点的数组指针
  int n;         //节点当前关键字数量
  bool leaf;     //当节点是叶子节点的时候为true,否则为false
};

class BTree {
public:
  BTree(int _t) {
    root = nullptr;
    t = _t;
  }
  //遍历该树的方法
  void traverse() {
    if (root != nullptr)
      root->traverse();
  }
  //查询关键字
  BTreeNode *search(int k) {
    return (root == nullptr) ? nullptr : root->search(k);
  }

  //数据插入
  void insert(int k);

private:
  BTreeNode *root;
  int t; //最小度
};