#include "btree.h"
#include <asm-generic/errno-base.h>

// BTreeNide构造函数
BTreeNode::BTreeNode(int _t, bool _leaf) {
  t = _t;
  leaf = _leaf;

  //分配节点可以存放关键字的最大内存,以及孩子指针
  keys = new int[2 * t - 1];
  C = new BTreeNode *[2 * t];

  //初始化节点内部的孩子数目
  n = 0;
}

//遍历以这个节点为根的所有子树上的关键字
void BTreeNode::traverse() {
  //节点内共计n个关键字，n+1个孩子
  int i = 0;
  for (i = 0; i < n; i++) {
    if (leaf == false)
      C[i]->traverse();
    printf("%d ", keys[i]);
  }

  //打印最后一棵树上的所有节点(待改进)
  if (leaf == false)
    C[i]->traverse();
}

//查找以这个节点为根的所有子树上的关键字
BTreeNode *BTreeNode::search(int k) {
  //找到节点上第一个比k大的关键字
  int i = 0;
  while (i < n && k > keys[i])
    i++;
  //查看该关键字是否是我们要找的关键字
  if (keys[i] == k)
    return this;
  //如果没有找到k,且本节点是叶子节点，返回NULL
  if (leaf == true)
    return nullptr;

  //递归子树进行循找
  return C[i]->search(k);
}

//插入操作(前提该节点为非空)
void BTreeNode::insertNonFull(int k) {
  //将索引初始化最右边的节点
  int i = n - 1;
  //如果是叶子节点
  if (leaf == true) {
    //需要干两件事
    // a.找到插入位置
    // b.将插入位置后的往后移动
    while (i >= 0 && keys[i] > k) //找到第一个比key小的值
    {
      keys[i + 1] = keys[i]; //数据移动
      i--;
    }
    //找到位置后进行数据插入
    keys[i + 1] = k;
    n = n + 1;
  } else {
    //如果不是叶子节点

    while (i >= 0 && keys[i] > k)
      i--;
    //查看子节点是否full,进行split
    if (C[i + 1]->n == 2 * t - 1) {
      spliChild(i + 1, C[i + 1]);

      //因为分裂后C[i],将会被分成两部分，c[i]将会被往上提，判断属于哪一部分
      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}

//拆分字节点y的函数,调用此函数的前提是该节点的子节点y是满的

void BTreeNode::spliChild(int i, BTreeNode *y) {

  //因为要分裂为两个节点，所以需要新创建一个节点，存放(t-1)个keys
  //也就是存放，keys[t-1]右边的数据
  BTreeNode *z = new BTreeNode(y->t, y->leaf);
  z->n = t - 1;

  //将y中keys[t-1]左边的数据拷贝到z当中
  for (int j = 0; j < t - 1; j++) {
    z->keys[j] = y->keys[j+t];
  }

  //如果y不是叶子节点,则需要将y中C[t]左边的数据拷贝到z当中
  if (y->leaf == false) {
    for (int j = 0; j < t; j++) {
      z->C[j] = y->C[j+t];
    }
  }


  //减少y中keys的数量
  y->n = t - 1;

  //因为该节点需要存放从子节点提升上来的节点，所以需要为新节点腾出位置
  for (int j = n; j >= i + 1; j--) {
    C[j + 1] = C[j];
  }
  C[i + 1] = z;

  //为key腾出位置
  for (int j = n - 1; j >= i; j++) {
    keys[j + 1] = keys[j];
  }
  keys[i] = y->keys[t - 1];

  n = n + 1;
}

//插入操作

void BTree::insert(int k) {
  //判断树是否为空
  if (root == nullptr) {
    //开辟根节点
    root = new BTreeNode(t, true);
    root->keys[0] = k; //插入
    root->n = 1;       //更新key值数量
  } else {
    //不为空

    //判断根节点是否full,若full树的高度会增加
    if (root->n == 2 * t - 1) {
      // new出新节点
      BTreeNode *s = new BTreeNode(t, false);
      s->C[0] = root;

      //分裂
      s->spliChild(0, root);

      //现在新节点有两个孩子，判断要插入的key应加入哪一个孩子
      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);
      root = s;
    } else //根节点现在必定不会full
    {
      root->insertNonFull(k);
    }
  }
}