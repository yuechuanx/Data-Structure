//
// Created by Xiaoy on 2018/4/30.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H


#include "AVLNode.h"


//AVL树的模板实现
template <typename KeyType>
class AVLTree
{
    typedef AVLNode<KeyType> AVLNode;//类型定义
    typedef AVLTree<KeyType> AVLTree;

private:
    AVLNode * avlroot;
    int __height(const AVLNode *root);//求树的高度
    int __diff(const AVLNode*root);//高度差（平衡因子）

    //AVL4种旋转：左左，左右，右右，右左
    //X定义为插入位置节点到根节点的路径上平衡条件被改变的节点中最深的那个节点
    //X通过递归返回的方式找到
    //左左：插入点位于X的左孩子节点的左子树
    //左右：插入点位于X的左孩子节点的右子树
    //右右：插入点位于X的右孩子节点的右子树
    //右左：插入点位于X的右孩子节点的左子树

    //单旋转
    AVLNode * __ll_Rotation(AVLNode *root);//left-left rotation
    AVLNode * __rr_Rotation(AVLNode *root);//right-right rotation
    //双旋转
    AVLNode * __lr_Rotation(AVLNode *root);//left-right rotation
    AVLNode * __rl_Rotation(AVLNode *root);//right-left rotation



    AVLNode * __Balance(AVLNode *root);//平衡操作
    AVLNode * __Insert(AVLNode *root, const KeyType &k);//插入的内部实现


    //中序遍历的两种重载
    void __InorderTraversal(const AVLNode* root);//输出
    void __InorderTraversal(const AVLNode*root, std::vector<KeyType>&vec);//结果保存


    bool __isLeaf(AVLNode* const &node) {return (node->left == nullptr && node->right == nullptr) ? true : false};//判断是否是叶子节点
    bool __isNodeWithTwoChild(AVLNode * const &node);//判断是否有两个孩子

    AVLNode* __search(AVLNode *const root, const KeyType &k);//查找的内部实现


    void __deleteTree(AVLNode * root);//删除树的所有节点


    AVLNode* __Delete(AVLNode * root, const KeyType& k);//删除节点

    AVLNode* __treeMin(AVLNode *root);//求当前根节点最小（一路向左）
    AVLNode* __treeMax(AVLNode *root);//求当前根节点的最大（一路向右）


public:
    AVLTree(){ avlroot = nullptr; }//默认构造函数
    ~AVLTree();//析构函数删除树中所有节点
    AVLTree(const std::vector<KeyType>&);//构造函数，容器构造
    AVLTree(const KeyType * arr, size_t len);//构造函数，数组构造
    void InorderTraversal();//中序遍历外部接口
    void InorderTraversal(std::vector<KeyType>&);//中序遍历外部接口重载2
    bool Delete(const KeyType &k);//删除节点的外部接口
    void Insert(const KeyType & k);//插入节点的外部接口
    bool IsEmpty(){ return avlroot == nullptr; } //树空？
    bool search(const KeyType &k);//查询外部接口

};


//构造函数1-容器构造
template < typename KeyType >
AVLTree::AVLTree(const std::vector<KeyType>&vec)
{
    avlroot = nullptr;
    for (int i = 0; i < (int)vec.size(); i++)
    {
        Insert(vec[i]);
    }
}

//构造函数2-数组构造
template < typename KeyType >
AVLTree::AVLTree(const KeyType * arr,size_t len)
{
    avlroot = nullptr;
    for (int i = 0; i < (int)len; i++)
    {
        Insert(*(arr + i));
    }
}

template <typename KeyType>
void AVLTree::__deleteTree(AVLNode *root)//删除所有节点
{
    if (nullptr == root)
        return;
    __deleteTree(root->left);
    __deleteTree(root->right);
    delete root;
    root = nullptr;
    return;
}

//析构函数
template <typename KeyType>
AVLTree::~AVLTree()
{
    __deleteTree(avlroot);
}


template <typename KeyType>
AVLNode * AVLTree::__Insert(AVLNode * root, const KeyType& k)
{
    if (nullptr == root)
    {
        root = new AVLNode(k);
        return root;
    }//递归返回条件
    else if (k < root->key)
    {
        root->left = __Insert(root->left, k);//递归左子树
        //balance operation
        root = __Balance(root);//平衡操作包含了四种旋转
    }
    else if (k>root->key)
    {
        root->right = __Insert(root->right, k);//递归右子树
        //balance operation
        root = __Balance(root);//平衡操作包含了四种旋转
    }
    return root;
}

//树高
template <typename KeyType>
int AVLTree::__height(const AVLNode *root)//求树高
{
    if (root == nullptr)
        return 0;
    return std::max(__height(root->left) , __height(root->right)) + 1;
}

//平衡因子
template <typename KeyType>
int AVLTree::__diff(const AVLNode *root)//求平衡因子，即当前节点左右子树的差
{
    return __height(root->left) - __height(root->right);
}

//平衡操作
template <typename KeyType>
AVLNode * AVLTree::__Balance(AVLNode *root)
{
    int balanceFactor = __diff(root);//__diff用来计算平衡因子（左右子树高度差）
    if (balanceFactor > 1)//左子树高于右子树
    {
        if (__diff(root->left) > 0)//左左外侧
            root=__ll_Rotation(root);
        else//左右内侧
            root=__lr_Rotation(root);
    }
    else if (balanceFactor < -1)//右子树高于左子树
    {
        if (__diff(root->right) > 0)//右左内侧
            root=__rl_Rotation(root);
        else//右右外侧
            root=__rr_Rotation(root);
    }
    return root;
}

//四种AVL旋转

template <typename KeyType>
AVLNode * AVLTree::__rr_Rotation(AVLNode *root)//right-right rotation
{
    AVLNode* tmp;
    tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    return tmp;
}
template <typename KeyType>
AVLNode * AVLTree::__ll_Rotation(AVLNode *root)//left-left rotation
{
    AVLNode * tmp;
    tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    return tmp;
}
template <typename KeyType>
AVLNode * AVLTree::__lr_Rotation(AVLNode *root)//left-right rotation
{
    AVLNode * tmp;
    tmp = root->left;
    root->left = __rr_Rotation(tmp);
    return __ll_Rotation(root);
}

template <typename KeyType>
AVLNode * AVLTree::__rl_Rotation(AVLNode *root)//right-left rotation
{
    AVLNode * tmp;
    tmp = root->right;
    root->right = __ll_Rotation(tmp);
    return __rr_Rotation(root);
}

//删除节点的私有成员实现
template <typename KeyType>
AVLNode * AVLTree::__Delete(AVLNode *root, const KeyType& k)
{
    if (nullptr == root)
        return root;
    if (!search(k))//查找删除元素是否存在
    {
        std::cerr << "Delete error , key not find" << std::endl;
        return root;
    }

    if (k == root->key)//根节点
    {
        if (__isNodeWithTwoChild(root))//左右子树都非空
        {
            if (__diff(root) > 0)//左子树更高，在左边删除
            {
                root->key = __treeMax(root->left)->key;//以左子树的最大值替换当前值
                root->left = __Delete(root->left, root->key);//删除左子树中已经替换上去的节点
            }
            else//右子树更高，在右边删除
            {
                root->key = __treeMin(root->right)->key;
                root->right = __Delete(root->right, root->key);
            }
        }
        else//有一个孩子、叶子节点的情况合并
        {
            //if (!__isLeaf(root))
            AVLNode * tmp = root;
            root = (root->left) ? (root->left) :( root->right);
            delete tmp;
            tmp = nullptr;
        }
    }//end-if
    else if (k < root->key)//往左边删除
    {
        root->left = __Delete(root->left, k);//左子树中递归删除
        //判断平衡的条件与在插入时情况类似
        if (__diff(root) < -1)//不满足平衡条件，删除左边的后，右子树变高
        {
            if (__diff(root->right) > 0)
            {
                root = __rl_Rotation(root);
            }
            else
            {
                root = __rr_Rotation(root);
            }
        }
    }//end else if
    else
    {
        root->right = __Delete(root->right, k);
        if (__diff(root) > 1)//不满足平衡条件
        {
            if (__diff(root->left) < 0)
            {
                root = __lr_Rotation(root);
            }
            else
            {
                root = __ll_Rotation(root);
            }
        }
    }
    return root;
}


//删除节点的外部接口
template <typename KeyType>
bool AVLTree::Delete(const KeyType &k)
{
    return __Delete(avlroot, k)==nullptr?false:true;
}

//查找内部实现
template <typename KeyType>
AVLNode * AVLTree::__search(AVLNode *const root, const KeyType &k)
{
    if (nullptr == root)
        return nullptr;
    if (k == root->key)
        return root;
    else if (k > root->key)
        return __search(root->right, k);
    else
        return __search(root->left, k);
}
//查找外部接口
template <typename KeyType>
bool AVLTree::search(const KeyType &k)
{
    return __search(avlroot, k) == nullptr ? false : true;
}


//中序遍历内部调用（1直接打印）
template <typename KeyType>
void AVLTree::__InorderTraversal(const AVLNode*root)
{
    if (nullptr == root)
        return;
    __InorderTraversal(root->left);
    std::cout << root->key << " ";
    __InorderTraversal(root->right);
}

//中序遍历内部调用（2存入容器）
template <typename KeyType>
void AVLTree::__InorderTraversal(const AVLNode*root,std::vector<KeyType>&vec)
{
    if (nullptr == root)
        return;
    __InorderTraversal(root->left);
    vec.push_back(root->key);
    __InorderTraversal(root->right);
}

//中序遍历外部接口（重载版本1）
template <typename KeyType>
void AVLTree::InorderTraversal()
{
    __InorderTraversal(avlroot);
}

//中序遍历外部接口（重载版本2）
template <typename KeyType>
void AVLTree::InorderTraversal(std::vector<KeyType>&vec)
{
    __InorderTraversal(avlroot,vec);
}

template<typename KeyType>
void AVLTree::Insert(const KeyType &k) {
    if (nullptr == avlroot)
    {
        avlroot = new AVLNode(k);
    }//递归返回条件
    else if (k < avlroot->key)
    {
        avlroot->left = __Insert(avlroot->left, k);//递归左子树
        //balance operation
        avlroot = __Balance(avlroot);//平衡操作包含了四种旋转
    }
    else if (k>avlroot->key)
    {
        avlroot->right = __Insert(avlroot->right, k);//递归右子树
        //balance operation
        avlroot = __Balance(avlroot);//平衡操作包含了四种旋转
    }
}

template<typename KeyType>
bool AVLTree::__isNodeWithTwoChild(AVLNode *const &node) {
    if (nullptr != node -> left && nullptr != node -> right) return true;
    return false;
}

template<typename KeyType>
AVLNode* AVLTree::__treeMin(AVLNode *root) {
    if (nullptr == root->left) return root;
    __treeMin(root->left);

}

template<typename KeyType>
AVLNode* AVLTree::__treeMax(AVLNode *root) {
    if (nullptr == root->right) return root;
    __treeMin(root->right);
//    if (root->right != nullptr) {
//        __treeMax(root->right);
//    }
//    return nullptrptr;
}

#endif //AVLTREE_AVLTREE_H
