#include<iostream>
#include<string>
#include<deque>
#include<stack>
using namespace std;
namespace bintree   //命名空间
{
    //二叉树节点
   class BinTreeNode
   {
    private:
        int data;
        BinTreeNode*left,*right;
    public:
      //构造函数用初始化列表进行初始化
        BinTreeNode(const int&item,BinTreeNode*lptr=NULL,BinTreeNode*rptr=NULL):data(item),left(lptr),right(rptr){};
        void set_data(int item)
        {
            data=item;
        }
        int get_data()const
        {
            return data;
        }
        void set_left(BinTreeNode*l)
        {
            left=l;
        }
        BinTreeNode*get_left()const
        {
            return left;
        }
        void set_right(BinTreeNode*r)
        {
            right=r;
        }
        BinTreeNode*get_right()const
        {
            return right;
        }
   };
class BinTree
{
private:
    BinTreeNode*root;
public:
    BinTree(BinTreeNode*t=NULL):root(t){};
    ~BinTree()
    {
        destroytree(root);
    }
    void destroytree(BinTreeNode*r);
    //设置根节点
    void set_root(BinTreeNode*t)
    {
        root=t;
    }
    //获取根节点
    BinTreeNode*get_root()const
    {
        return root;
    }
    //1.创建二叉树，返回根节点
    BinTreeNode*create_tree();
    //2.前序遍历
    void pre_order(BinTreeNode*r)const;
    //3.中序遍历
    void in_order(BinTreeNode*r)const;
    //4.后续遍历
    void past_order(BinTreeNode*r)const;
    //5.层次遍历
    void level_order(BinTreeNode*r)const;
    //6.获取叶子结点个数
    int get_leaf_num(BinTreeNode*r)const;
    //7.获得二叉树高度
    int get_tree_height(BinTreeNode*r)const;
    //8.交换二叉树的左右儿子
    void swap_left_right(BinTreeNode*r);
    //9.求两个节点pNode1和pNode2在以r为树根的树中的最近公共祖先
    BinTreeNode* get_nearest_common_father(BinTreeNode *r,BinTreeNode *pNode1,BinTreeNode *pNode2)const;
    //10.打印和为某一值的所有路径
    void print_rout(BinTreeNode *r,int sum)const;
    //11.判断一个节点t是否在以r为根的子树中
    bool is_in_tree(BinTreeNode *r,BinTreeNode *t)const;
};
//销毁二叉树
void BinTree::destroytree(BinTreeNode*r)
    {
        if(r==NULL)
            return;
        else
        {
            destroytree(r->get_left());
            destroytree(r->get_right());
            delete(r);
        }
    }
//创建二叉树，这里不妨使用前序创建二叉树，遇到‘#’表示节点为空
BinTreeNode*BinTree::create_tree()
{
    char item;
    BinTreeNode*t,*t_l,*t_r;
    cin>>item;
    if(item!='#')
    {
        BinTreeNode*pTmpNode=new BinTreeNode(item-48);
        t=pTmpNode;
        t_l=create_tree();
        t->set_left(t_l);
        t_r=create_tree();
        t->set_right(t_r);
        return t;
    }
    else 
    {
        t=NULL;
        return NULL;
    }
}
void BinTree::pre_order(BinTreeNode*r)const
{
    BinTreeNode*ptmpNode=r;
    if(ptmpNode!=NULL)
    {
        cout<<ptmpNode->get_data()<<" ";
        pre_order(ptmpNode->get_left());
        pre_order(ptmpNode->get_right());
    }
}
void BinTree::in_order(BinTreeNode*r)const
{
    BinTreeNode*ptmpNode=r;
    if(ptmpNode!=NULL)
    {
        in_order(ptmpNode->get_left());
         cout<<ptmpNode->get_data()<<" ";
        in_order(ptmpNode->get_right());
    }
}
void BinTree::past_order(BinTreeNode*r)const
{
    BinTreeNode*ptmpNode=r;
    if(ptmpNode!=NULL)
    {
        past_order(ptmpNode->get_left());
        past_order(ptmpNode->get_right());
        cout<<ptmpNode->get_data()<<" ";
    }
}
void BinTree::level_order(BinTreeNode*r)const
{   
    if(r==NULL)
        return ;
    deque<BinTreeNode*>q;
    q.push_back(r);
    while(!q.empty())
    {
        BinTreeNode*pTmpNode=q.front();
        cout<<pTmpNode->get_data()<<" ";
        q.pop_front();
        if(pTmpNode->get_left()!=NULL)
        {
            q.push_back(pTmpNode->get_left());
        }
        if(pTmpNode->get_right()!=NULL)
        {
            q.push_back(pTmpNode->get_right());
        }
    }
}
int BinTree::get_leaf_num(BinTreeNode*r)const
{
    if(r==NULL)
    {
        return 0;
    }
    if(r->get_left()==NULL&&r->get_right()==NULL)  //没有子结点
    {
        return 1;
    }
    return get_leaf_num(r->get_left())+get_leaf_num(r->get_right());
}
int BinTree::get_tree_height(BinTreeNode*r)const
{
    if(r==NULL)
    return 0;
    if(r->get_left()==NULL&&r->get_right()==NULL)   //叶子节点
    {
        return 1;
    }
    int l_height=get_tree_height(r->get_left());
    int r_height=get_tree_height(r->get_right());
    return l_height>=r_height?l_height+1:r_height+1;
}
void BinTree::swap_left_right(BinTreeNode*r)
{
    if(r==NULL)
    {
        return ;
    }
    BinTreeNode*pTmpNode=r->get_left();
    r->set_left(r->get_right());
    r->set_right(pTmpNode);
    swap_left_right(r->get_left());
    swap_left_right(r->get_right());
}
bool BinTree::is_in_tree(BinTreeNode*r,BinTreeNode*t)const
{
    bool has=false;
    if(r==NULL)
    return false;
    else if(r==t)
    return true;
    else
    {
        if(r->get_left()!=NULL)
        {
            has=is_in_tree(r->get_left(),t);
        }
        if(!has&&r->get_right()!=NULL)
        {
            has=is_in_tree(r->get_right(),t);
        }
    }
    return has;
}
BinTreeNode* BinTree::get_nearest_common_father(BinTreeNode *r,BinTreeNode *pNode1,BinTreeNode *pNode2)const
{
    if(is_in_tree(pNode1,pNode2))
    {
        return pNode1;
    }
    if(is_in_tree(pNode2,pNode1))
    {
        return pNode2;
    }
    bool one_in_left,one_in_right,another_in_left,another_in_right;
    one_in_left=is_in_tree(r->get_left(),pNode1);
    another_in_right=is_in_tree(r->get_right(),pNode2);
    another_in_left=is_in_tree(r->get_left(),pNode2);
    one_in_right=is_in_tree(r->get_right(),pNode1);
    if((one_in_left&&another_in_right)||(one_in_right&&another_in_left))
    {
        return r;
    }
    else if(one_in_left&&another_in_left)
    {
        return get_nearest_common_father(r->get_left(),pNode1,pNode2);
    }
    else if(one_in_right&&another_in_right)
    {
        return get_nearest_common_father(r->get_right(),pNode1,pNode2);
    }
    else 
    {
        return NULL;
    }
}
stack<BinTreeNode*>dfs_s;
stack<BinTreeNode*>print_s;
void BinTree ::print_rout(BinTreeNode*r,int sum)const
{
    if(r==NULL)
    return;
    sum-=r->get_data();
    dfs_s.push(r);
    if(sum<=0)
    {
        if(sum==0)
        {
            while(!dfs_s.empty())
            {
                print_s.push(dfs_s.top());
                dfs_s.pop();
            }
            while(!print_s.empty())
            {
                cout<<print_s.top()->get_data()<<" ";
                dfs_s.push(print_s.top());
                print_s.pop();
            }
            cout<<endl;
        }
        sum+=r->get_data();
        dfs_s.pop();
        return;
    }
    print_rout(r->get_left(),sum);
    print_rout(r->get_right(),sum);
    sum+=r->get_data();
    dfs_s.pop();
}
}