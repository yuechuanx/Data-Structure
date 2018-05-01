//
// Created by Xiaoy on 2018/4/30.
//

#ifndef AVLTREE_AVLNODE_H
#define AVLTREE_AVLNODE_H

#include <iostream>
#include <vector>
#include <algorithm>
template <typename KeyType>
class AVLNode{
public:
    KeyType key;
    AVLNode * left;
    AVLNode * right;
    AVLNode(KeyType k) : key(k), left(nullptr), right(nullptr) {}
    AVLNode() : key(0), left(nullptr), right(nullptr) {}

};

#endif //AVLTREE_AVLNODE_H
