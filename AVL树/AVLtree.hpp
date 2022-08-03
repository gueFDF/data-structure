#include <iostream>
template <class T>
struct AVLTreeNode
{
    AVLTreeNode(T value, AVLTreeNode<T> *l, AVLTreeNode<T> *r)
        : key(value), lchild(l), rchild(r){};

    T key;      //节点值
    int heigth; //节点高度用于计算平衡因子
    AVLTreeNode<T> *lchild;
    AVLTreeNode<T> *rchild;
};
template <class T>
class AVLTree
{
public:
    AVLTreeNode<T> *root; // AVL树的根节点

public:
    AVLTree();  //构造函数
    ~AVLTree(); //析构函数
    void inOrder(AVLTreeNode<T> *pnode) const;
    void destory(AVLTreeNode<T> *&pnode);
    int height(AVLTreeNode<T> *pnode);
    AVLTreeNode<T> *insert(AVLTreeNode<T> *&pnode, T key); //插入节点
    AVLTreeNode<T> *remove(AVLTreeNode<T> *&pnode, T key); //删除节点
    AVLTreeNode<T> *Findmin(AVLTreeNode<T> *pnode) const;  //找最小节点
    AVLTreeNode<T> *Findmax(AVLTreeNode<T> *pnode) const;  //找最大节点

    AVLTreeNode<T> *leftRotation(AVLTreeNode<T> *pnode);      //单旋:左旋操作
    AVLTreeNode<T> *rightRotation(AVLTreeNode<T> *pnode);     //单旋:右旋操作
    AVLTreeNode<T> *leftRightRotation(AVLTreeNode<T> *pnode); //双旋:先左旋后右旋操作
    AVLTreeNode<T> *rightLeftRotation(AVLTreeNode<T> *pnode); //双旋:先右旋后左旋操作
};

template <class T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
}
template <class T>
AVLTree<T>::~AVLTree() //析构函数
{
    if (root != nullptr)
        destory(root);
}
template <class T>
int AVLTree<T>::height(AVLTreeNode<T> *pnode)
{
    if (pnode != nullptr)
    {
        return pnode->heigth;
    }
    return 0;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::leftRotation(AVLTreeNode<T> *pnode) //单旋:左旋操作
{
    AVLTreeNode<T> *node = pnode->rchild;
    pnode->rchild = node->lchild;
    node->lchild = pnode;
    //更新高度
    pnode->heigth = std::max(height(pnode->lchild), height(pnode->rchild)) + 1;
    node->heigth = std::max(height(node->lchild), height(node->rchild)) + 1;
    return node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::rightRotation(AVLTreeNode<T> *pnode) //单旋：右旋操作
{
    AVLTreeNode<T> *node = pnode->lchild;
    pnode->lchild = node->rchild;
    node->rchild = pnode;
    //更新高度
    pnode->heigth = std::max(height(pnode->lchild), height(pnode->rchild)) + 1;
    node->heigth = std::max(height(node->lchild), height(node->rchild) + 1) + 1;

    return node;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::rightLeftRotation(AVLTreeNode<T> *pnode) //双旋:先右旋后左旋操作
{
    pnode->rchild = rightRotation(pnode->rchild);
    return leftRotation(pnode);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::leftRightRotation(AVLTreeNode<T> *pnode) //双旋:先左旋后右旋操作
{
    pnode->lchild = leftRotation(pnode->lchild);
    return rightRotation(pnode);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::insert(AVLTreeNode<T> *&pnode, T key) //节点插入
{
    if (pnode == nullptr) //若该树为空树
    {
        pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
        // return pnode;
    }
    else if (key > pnode->key) //右树
        pnode->rchild = insert(pnode->rchild, key);
    else if (key < pnode->key) //左树
        pnode->lchild = insert(pnode->lchild, key);
    /*else
         return pnode;*/
    //判断是否平衡
    if (height(pnode->lchild) - height(pnode->rchild) == 2)
    {
        AVLTreeNode<T> *temp = pnode->lchild;
        if (height(temp->lchild) - height(temp->rchild) == 1) //右旋
            pnode = rightRotation(pnode);
        else //右左旋
            pnode = leftRightRotation(pnode);
    }
    else if (height(pnode->lchild) - height(pnode->rchild) == -2)
    {
        AVLTreeNode<T> *temp = pnode->rchild;
        if (height(temp->lchild) - height(temp->rchild) == 1) //左右旋
            pnode = rightLeftRotation(pnode);
        else //左旋
            pnode = leftRotation(pnode);
    }
    pnode->heigth = std::max(height(pnode->lchild), height(pnode->rchild)) + 1; //更新高度
    return pnode;
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::remove(AVLTreeNode<T> *&pnode, T key)
{
    if (pnode == nullptr)
        std::cout << "要删除的元素未找到" << std::endl;
    else
    {
        if (key < pnode->key) //在左子树找
        {
            pnode->lchild = remove(pnode->lchild, key);
            pnode->heigth = std::max(height(pnode->lchild), height(pnode->rchild)) + 1; //更新高度

            if (height(pnode->lchild) - height(pnode->rchild) == -2)
            {
                AVLTreeNode<T> *temp = pnode->rchild;
                if (height(temp->lchild) - height(temp->rchild) == 1) //左右旋
                    pnode = rightLeftRotation(pnode);
                else //左旋
                    pnode = leftRotation(pnode);
            }
        }
        else if (key > pnode->key) //在右子树找
        {
            pnode->rchild = remove(pnode->rchild, key);
            pnode->heigth = std::max(height(pnode->lchild), height(pnode->rchild)) + 1; //更新高度
            if (height(pnode->lchild) - height(pnode->rchild) == 2)
            {
                AVLTreeNode<T> *temp = pnode->lchild;
                if (height(temp->lchild) - height(temp->rchild) == 1) //右旋
                    pnode = rightRotation(pnode);
                else //右左旋
                    pnode = leftRightRotation(pnode);
            }
        }
        else //找到了,进行删除
        {
            if (pnode->lchild && pnode->rchild) //有左右子树
            {
                if (height(pnode->lchild) > height(pnode->rchild)) //左子树比右子树高，在左子树找最大
                {
                    AVLTreeNode<T> *temp = Findmax(pnode->lchild);
                    pnode->key = temp->key;
                    pnode->lchild = remove(pnode->lchild, temp->key); //递归删除
                }
                else //在右子树找最小
                {
                    AVLTreeNode<T> *temp = Findmin(pnode->rchild);
                    pnode->key = temp->key;
                    pnode->rchild = remove(pnode->rchild, temp->key);
                }
            }
            else
            {
                AVLTreeNode<T> *temp = pnode;
                if (pnode->lchild) //只有左节点，或没有节点
                    pnode = pnode->lchild;
                else //只有右节点
                    pnode = pnode->rchild;
                delete temp;
            }
        }
    }
    return pnode;
}

//中序遍历
template <class T>
void AVLTree<T>::inOrder(AVLTreeNode<T> *pnode) const
{
    if (pnode == nullptr)
        return;
    inOrder(pnode->lchild);
    std::cout << pnode->key << " ";
    inOrder(pnode->rchild);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::Findmin(AVLTreeNode<T> *pnode) const //最左边
{
    if (pnode == nullptr)
        return NULL;
    else
    {
        while (pnode->lchild)
        {
            pnode = pnode->lchild;
        }
        return pnode;
    }
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::Findmax(AVLTreeNode<T> *pnode) const //最右边
{
    if (pnode == nullptr)
        return NULL;
    else
    {
        while (pnode->rchild)
        {
            pnode = pnode->rchild;
        }
        return pnode;
    }
}
template <class T>
void AVLTree<T>::destory(AVLTreeNode<T> *&pnode)
{
    if (pnode == nullptr)
        return;
    destory(pnode->lchild);
    destory(pnode->rchild);
    delete pnode;
}