#include<iostream>
#include<string>
using namespace std;
namespace BST
{
    class BstNode
    {
    private:
        BstNode*left,*right;
        int data;
    public:
        BstNode(int Data,BstNode*Left=NULL,BstNode*Right=NULL):data(Data),left(Left),right(Right){};
         void set_data(int item)
        {
            data=item;
        }
        int get_data()const
        {
            return data;
        }
        void set_left(BstNode*l)
        {
            left=l;
        }
        BstNode*get_left()const
        {
            return left;
        }
        void set_right(BstNode*r)
        {
            right=r;
        }
        BstNode*get_right()const
        {
            return right;
        }
        
    };
    class Bst
    {
    private:
        BstNode*root;
    public:
        Bst(BstNode*t=NULL):root(t){};
        ~Bst()
        {

        }
        void set_root(BstNode*iroot)
        {
            root=iroot;
        }
        BstNode*get_root() const
        {
            return root;
        }
        //插入元素
        BstNode*insert(BstNode*root,int val);
        //查找任意元素(递归)
        BstNode*Find(BstNode*root,int val);
        ////查找任意元素(非递归)
        BstNode*iterFind(BstNode*root,int val);
        //查找最大元素
        BstNode*FindMax(BstNode*root);
        //查找最小元素
        BstNode*FindMin(BstNode*root);
        //删除元素
        BstNode*Delete(BstNode*root,int val);

    };
    BstNode*Bst::insert(BstNode*root,int val)
    {
        if(root==NULL)//如果根节点为空，就返回该节点
        {
            root=new BstNode(val);
            root->set_left(nullptr);
            root->set_right(nullptr);
        }
        else//根节点不为空
        {
            if(val<root->get_data())   //插入右子树
            {
               root->set_left(insert(root->get_left(),val));
            }
            else if(val>root->get_data())  //插入左子树
            {
               root->set_right(insert(root->get_right(),val));
            }
            //如果该节点已存在，什么都不用做
        }
        return root;
    }
    //查找任意元素(递归)
    BstNode*Bst::Find(BstNode*root,int val)
    {
        if(root==NULL)
         return NULL;  //查找失败
        if(val<root->get_data())  //在左子树上
            return Find(root->get_left(),val);
        else if(val>root->get_data())   //在有子树上
            return Find(root->get_right(),val);
        else
            return root;   //找到了
    }
     //查找任意元素(非递归)
    BstNode*Bst::iterFind(BstNode*root,int val)
    {
        while(root)
        {
            if(val<root->get_data())
                root=root->get_left();
            if(val>root->get_data())
                root=root->get_right();
        }
        return NULL;
    }
     //查找最大元素
    BstNode*Bst::FindMax(BstNode*root)
    {
        if(root==NULL)
            return NULL;
        while(root->get_right())
        {
            root=root->get_right();
        }
        return root;
    }
    //查找最小元素
    BstNode*FindMin(BstNode*root)
    {
        if(root==NULL)
            return NULL;
        while(root->get_left())
        {
            root=root->get_left();
        }
        return root;
    }
    //删除较为麻烦会有三种情况
    //1.目标节点没有子结点
    //2.目标节点只有一个子节点
    //3.目标节点有两个子结点
    BstNode*Bst::Delete(BstNode*root,int val)
    {
        if(root==NULL)
        cout<<"要删除的元素未找到"<<endl;
        else
        {
            if(val<root->get_data())
            {
                root->set_left(Delete(root->get_left(),val));
            }
            else if(val>root->get_data())
            {
                root->set_right(Delete(root->get_right(),val));
            }
            else
            {
                if(root->get_right()&&root->get_left())  //有左右节点
                {
                    BstNode*temp=FindMax(root->get_left());
                    root->set_data(temp->get_data());
                    root->set_left(Delete(root->get_left(),val));

                }
                else
                {
                    BstNode*temp=root;
                    if(root->get_left()==NULL)   //只有右节点或没有节点
                        root=root->get_right();
                    else
                        root=root->get_left();   //只有左节点
                    delete temp;
                }
            }
        }
         return root;
    }



}