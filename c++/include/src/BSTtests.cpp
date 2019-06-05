/**
 * @file BSTtests.cpp
 * @author Francesca Cairoli
 * @date 30 May 2019
 * @brief Source file to perform various tests on the BST class.
 */
#include "BST.h"


//	Initial consideration: 'BinarySearchTree.h' methods call 
//  the functions defined in 'BinarySearchTreeSubclasses.hxx', 
//  also tested by calling the formal ones.
int main()
{

        std::pair<int, int> pair{4,4};
        std::pair<int, int> pair2{2,2};
        std::pair<int, int> pair3{6,6};
        std::pair<int, int> pair4{1,1};
        std::pair<int, int> pair5{5,5};
        std::pair<int, int> pair6{3,3};
        std::pair<int, int> pair7{7,2};
        std::pair<int, int> pair8{4,7};
        
        BST<int,int> bst{};
        std::cout << bst << std::endl;
        
        //	Testing building-up-tree methods
        bst.insert(pair4); //the insert() method calls functions in BinarySearchTree<TKey,TValue>::Iterator. 
        bst.insert(pair2);			
        bst.insert(pair6);
        bst.insert(pair5);
        bst.insert(pair3);
        bst.insert(pair7);
	    bst.insert(pair8);
        std::cout << bst << std::endl;
        bst.printStructure(std::to_string, "-", ' ');
        bst.balance();
        std::cout << bst << std::endl;

        bst.printStructure(std::to_string, "-", ' ');

         // Testing operator=
        BST<int,int> bst_1{};
        bst_1=bst;
        std::cout << bst_1 << std::endl;
        
        
}