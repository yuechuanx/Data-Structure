/**
* Definition for a child-brother tree node.
* struct TreeNode {
*     int val;
*     TreeNode *firstchild;
*     TreeNode *nextsibling;
*     TreeNode(int x) : val(x), firstchild(NULL), nextsibling(NULL) {}
* };
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


struct TreeNode {
    int val;
    TreeNode *firstchild;
    TreeNode *nextsibling;
    TreeNode(int x) : val(x), firstchild(NULL), nextsibling(NULL){}
};

int getDegreeOfNode(TreeNode* root) {
    int res = 0;
    if(root->firstchild) {
        res = 1;
        TreeNode* p = root->firstchild;
        while (p->nextsibling) {
            res++;
            p = p->nextsibling;
        }
    }
    return res;
}


// 递归求解
int Degree2() {

    return 0;
}

// 非递归求解，使用队列
int Degree(TreeNode* root) {
    std::queue<TreeNode*> q;

    int res = 0;
    q.push(root);
    while (!q.empty()) {
        res = std::max(res, getDegreeOfNode((TreeNode *) q.front()));
        if(q.front()->firstchild) q.push(q.front()->firstchild);
        while (q.back()->nextsibling) q.push(q.back()->nextsibling);
        q.pop();
    }
    return res;
}


int main(int argc, char const *argv[]) {


    /** 构造一棵树，树的样式如下：
     *      -1
     *      /
     *     1
     *   /  \
     *   11  2
     *   \
     *    12
     *     \
     *      13
     *       \
     *        14
     */
    TreeNode *root = new TreeNode(-1);
    TreeNode *C = new TreeNode(1);
    TreeNode *D = new TreeNode(2);
    TreeNode *E = new TreeNode(11);
    TreeNode *F = new TreeNode(12);
    TreeNode *G = new TreeNode(13);
    TreeNode *H = new TreeNode(14);
    root->firstchild = C;
    C->nextsibling = D;
    D->firstchild = E;
    E->nextsibling = F;
    F->nextsibling = G;
    G->nextsibling = H;

    std::cout << Degree(root) << '\n';

    return 0;
}






