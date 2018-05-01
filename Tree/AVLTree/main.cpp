#include <iostream>
#include <vector>

#include "AVLTree.h"

int main() {

    std::vector<int>vec = { 7, 6, 5, 4, 3, 2, 1 };
    AVLTree<int> avl(vec);
    avl.Insert(8);
    int keyToFind = 9;
    if (avl.search(keyToFind))
    {
        std::cout << keyToFind << " is found" << std::endl;
    }
    else
    {
        std::cerr << keyToFind << " is not found" << std::endl;
    }

    keyToFind = 4;
    if (avl.search(keyToFind))
    {
        std::cout << keyToFind << " is found" << std::endl;
    }
    else
    {
        std::cerr << keyToFind << " is not found" << std::endl;
    }

    avl.Delete(4);
    //avl.InorderTraversal();
    std::cout << std::endl;
    avl.InorderTraversal();

//    system("pause");
    
    return 0;
}
