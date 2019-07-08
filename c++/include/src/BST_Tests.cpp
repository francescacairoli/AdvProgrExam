/**
 * @file BSTtests.cpp
 * @author Francesca Cairoli
 * @date 17 June 2019
 * @brief Source file to perform various tests on the BST class.
 */
#include "BST.h"


int main()
{

        std::pair<int, int> pair1{8,8};
        std::pair<int, int> pair2{3,3};
        std::pair<int, int> pair3{10,10};
        std::pair<int, int> pair4{1,1};
        std::pair<int, int> pair5{6,6};
        std::pair<int, int> pair6{4,4};
        std::pair<int, int> pair7{7,7};
        std::pair<int, int> pair8{14,14};
        std::pair<int, int> pair9{13,13};
        
        // Printing the empty BST
        BST<int,int> bst{};
        std::cout << bst << std::endl;
        
        //Testing building-up-tree methods
        bst.insert(pair1);
        bst.insert(pair2);			
        bst.insert(pair3);
        bst.insert(pair4);
        bst.insert(pair5);
        bst.insert(pair6);
        bst.insert(pair7);
        bst.insert(pair8);
        bst.insert(pair9);        

        // Print the BST as ordered list
        std::cout << "Original unbalanced BST" << std::endl;
        std::cout << bst << std::endl;

        // Print the BST structure
        bst.printStructure(std::to_string, "-", ' ');

        // Test the balance method
        bst.balance();

        std::cout << "Balanced BST" << std::endl;
        std::cout << bst << std::endl;

        bst.printStructure(std::to_string, "-", ' ');


        //  Testing operator[] 
        int key = 13;
        std::cout << "The value associated to key " << key << " is " << bst[key] << std::endl;

        // Test copy and move constructors

        BST<int,int> copy_bst = bst;
        BST<int,int> move_bst = std::move(bst);

        std::cout << "Testing copy constructor" << std::endl;
        std::cout << copy_bst << std::endl;
        std::cout << "Testing move constructor" << std::endl;
        std::cout << move_bst << std::endl;

         // Testing operator=
        BST<int,int> bst_1{};
        bst_1 = bst;
        std::cout << "Testing operator=" << std::endl;
        std::cout << bst_1 << std::endl;

        // Testing the move semantics
        std::cout << "Testing move semantics" << std::endl;
        BST<int,int> bst_2{};
        bst_2 = std::move(bst);
        std::cout << bst_2 << std::endl;

        // Test the clear method
        std::cout << "Testing the clear method" << std::endl;
        bst_2.clear();
        std::cout << bst_2 << std::endl;
        std::cout << bst << std::endl;

        bst_1.clear();
        std::cout << bst_1 << std::endl;
        std::cout << bst << std::endl;


        
}