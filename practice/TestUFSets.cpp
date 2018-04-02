/**
* Definition for a Union-Find Set node.
* struct UFSetNode {
*     int val;
*     int parent;
*     UFSetNode(int x) : val(x), parent(-1), height(1) {};
* };
*/

#include <iostream>


struct UFSetNode {
    int val;
    int parent;
};

class UFSet {
protected:
    // 元素的存储结构为数组
    UFSetNode *sets;
    int s[17];
    int size;

    int Find(int val) {
        int p = 0;
        while (p < size && sets[p].val != val)
            p++;
        if (p == size)
            return -1;
        while(sets[p].parent > -1)
            p = sets[p].parent;
        return p;
    }

public:
    UFSet(int elem[], int n) {
        size = n;
        sets = new UFSetNode[size];
        for (int i = 0; i < size; ++i) {
            sets[i].val = elem[i];
            sets[i].parent = -1;
            s[i] = -1;
        }
    }

    virtual ~UFSet() {
        delete []sets;
    }
    // 简单的把j的双亲指向i
    void Union1(int a, int b) {
        int r1 = Find(a);
        int r2 = Find(b);
        if(r1 != r2 && r1 != -1) {
            sets[r1].parent += sets[r2].parent;
            sets[r2].parent = r1;
            // sets[r1].height += sets[r2].height;
        }
    }
    // 根据节点数量大小
    void Union2(int a, int b) {
        int r1 = Find(a);
        int r2 = Find(b);
        if (r1 != r2 && r1 != -1 && r2 != -1) {
            int temp = sets[r1].parent + sets[r2].parent;
            if (sets[r1].parent <= sets[r2].parent) {
                sets[r2].parent = r1;
                sets[r1].parent = temp;
            } else {
                sets[r2].parent = temp;
                sets[r1].parent = r2;
            }
        }
    }
    // 根据以i,j节点高度大小
    void Union3(int root1, int root2) {
        int r1 = Find(root1);
        int r2 = Find(root2);
        if (r1 != r2 && r1 != -1 && r2 != -1) {
            int temp = sets[r1].parent + sets[r2].parent;
            if(s[root2] < s[root1]) {
                s[root1] = s[root2];
                sets[r2].parent = temp;
                sets[r1].parent = r1;
            }// root2 is deeper
            else {
                if(s[root1] == s[root2]) {
                    s[root1]--; // 将root1的高度加1
                }
                s[root2] = s[root1];
                sets[r2].parent = r1;
                sets[r1].parent = temp;

            }
        }
    }

    void Print() {
        std::cout << "index  " << "val  " << "parent  " << "Height"<< std::endl;
        for (int i = 0; i < size; ++i) {
             std::cout << i << "        " << sets[i].val << "       " <<  sets[i].parent <<  "       "  <<  s[i] <<std::endl;
        }
    }
};


int main() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int n = 17;
    UFSet ufSet(a, n);
//    ufSet.Print();

    ufSet.Union3(1, 2);
    ufSet.Union3(3, 4);
    ufSet.Union3(3, 5);
    ufSet.Union3(1, 7);
    ufSet.Union3(3, 6);
    ufSet.Union3(8, 9);
    ufSet.Union3(1, 8);
    ufSet.Union3(3, 10);
    ufSet.Union3(3, 11);
    ufSet.Union3(3, 12);
    ufSet.Union3(3, 13);
    ufSet.Union3(14, 15);
    ufSet.Union3(16, 0);
    ufSet.Union3(14, 16);
    ufSet.Union3(1, 3);
    ufSet.Union3(1, 14);
//
//    ufSet.Union2(1, 2);
//    ufSet.Union2(3, 4);
//    ufSet.Union2(3, 5);
//    ufSet.Union2(1, 7);
//    ufSet.Union2(3, 6);
//    ufSet.Union2(8, 9);
//    ufSet.Union2(1, 8);
//    ufSet.Union2(3, 10);
//    ufSet.Union2(3, 11);
//    ufSet.Union2(3, 12);
//    ufSet.Union2(3, 13);
//    ufSet.Union2(14, 15);
//    ufSet.Union2(16, 0);
//    ufSet.Union2(14, 16);
//    ufSet.Union2(1, 3);
//    ufSet.Union2(1, 14);

//    ufSet.Union1(1, 2);
//    ufSet.Union1(3, 4);
//    ufSet.Union1(3, 5);
//    ufSet.Union1(1, 7);
//    ufSet.Union1(3, 6);
//    ufSet.Union1(8, 9);
//    ufSet.Union1(1, 8);
//    ufSet.Union1(3, 10);
//    ufSet.Union1(3, 11);
//    ufSet.Union1(3, 12);
//    ufSet.Union1(3, 13);
//    ufSet.Union1(14, 15);
//    ufSet.Union1(16, 0);
//    ufSet.Union1(14, 16);
//    ufSet.Union1(1, 3);
//    ufSet.Union1(1, 14);
//
    ufSet.Print();

    return 0;
}