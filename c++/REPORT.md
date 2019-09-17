# Introduction

The purpose of the assigned project is to implement a templated binary search tree in C++ language. A binary search tree is a hierarchical data structure, ordered according to the keys: each node in the tree as a key and a value, a smaller key is found in the left child, whereas a larger key is found in the right child.
The final goal is to compare the behavior of my custom implementation, either in a balanced or unbalanced situation, 
with the behaviour of the map and unordered_map standard libraries. 

## Code structure

The class BST implement the structure of our custom binary search tree, templated on the type of the key and the type of the values associated to nodes residing in it.
The BST class relies on a nested class, called Node, defined by a template pair of a key and a value. 
Allowing nodes to have a template type for the keys-value pair, results in the possibility of building
template trees, that is, trees with different types of nodes.

We defined the **Node** as a *struct* because we want all its methods and variables to be public for the tree to use. 
However, we placed the struct nested inside the tree and set it as private, in order not to exposed it to the user. 
The Node's key is set as constant in order to prevent any user to modify its value and thus corrupt
the inner structure of the tree. A node contains three pointers: one points to its parent node and the remaining two point 
to its children. For the pointers to children nodes we used the *unique_ptr* class defined in the standard library.
We expect this choice to facilitate the management of the memory and to improve the consistence of the operations on the tree. In fact, pointers can be problematic, in particular during node deletion: we don't want to leave behind any orphan node, which causes memory leaks and dangling references.
A unique_ptr holds a pointer to an object and deletes this object when the unique_ptr<> object is deleted. In addition, unique pointers allow to use the move semantics.


BST has three member variables: 
- **root** which is a private unique pointer to its root node,
- **size**, which indicates the number of nodes in the binary search tree, and
- **height**, which indicates the number of horizontal layers (generations) in the binary search tree. 

The other two sub-classes are Iterator and ConstIterator, used to perform forwards iterations on the tree. 
Since the user may want use them to iterate on the tree, we set them as public. 


These iterators are only able to iterate forward, using the overload of the operator++.
The Constant Iterator is a child class of the normal Iterator. The constant version is needed to ensure the functionality of methods which require 
a constant access to member variables. 

## Methods

- Constructors for the class Node:
  - using a pair of values, 
  - using a parent and possibly another node (copy constructor).

- The iterators notably have an overloading of the operator* which returns a pointer to the node.

- The method *getNode* was added in order to retrive the Node pointed by the iterator and is defined as private in order not to expose the Node class.

- BST methods:

  - Copy and move semantic, implemented as constructors and overloadings of operator=. 
This allows us to perform deep copies of a tree or moving its elements into another tree structure. 
It make use of the *copy* recursive method to perform the insertion.

  - **insert**, this method insert a node in the BST given a key-value pair. If the tree is empty, it insert the root node. If a key is already present, it replace the old value with the new one.

  - **clear**, this method clears the content of the tree. It leverages unique pointers, avoiding the use of recursion.

  - **balance** performs a non-in-place balancing of the tree. 
The ordered keys are store in a standard vector and reordered using a recursive bisection. Then the tree is cleared and the function *rebuildBalancedTree* is used to rebuild the tree according to the order dictated by the balanced vector. This method relies strongly on iterators and unique pointers.

  - **find**, this methos finds a given key and return an iterator to that node.

  - **printStructure** (additional) allows the user to visualize the tree structure in a graphic way. For visualize the order in a sequential way we used the overloading of operator<<.

  - **begin** (**cbegin**) and **end** (**cend**) are the methods used to provide starting and stopping conditions to the forward iteration inside the tree.

  - **operator[]** is used both to access and change the value of a specific node based on its key value.

## Tests

As starter, we compiled our code with the flags `-Wall -Wextra` in order to be sure of not getting any warning. We also checked not to have any memory leak, using the following command `valgrind -v ./tests.o`.

```
==16681== HEAP SUMMARY:
==16681==     in use at exit: 0 bytes in 0 blocks
==16681==   total heap usage: 34 allocs, 34 frees, 74,840 bytes allocated
==16681== 
==16681== All heap blocks were freed -- no leaks are possible
==16681== 
==16681== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==16681== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The file *BST_Test.cpp* is used to test the correctness of the BST. It compares different constructors, it tries different types for the template, and in general it tests all the functions defined above.

```
Original unbalanced BST     

// operator<<
1: 1
3: 3
4: 4
6: 6
7: 7
8: 8
10: 3
13: 13
14: 14

// printStructure
       8               
   3       10       
 1   6   -   14   
- - 4 7 - - 13 - 
```

```
Balanced BST

// operator<<
1: 1
3: 3
4: 4
6: 6
7: 7
8: 8
10: 3
13: 13
14: 14

// printStructure
       7               
   3       10       
 1   4   8   13   
- - - 6 - - - 14 

```

## Performances
In order to measure the look-up performaces, we performed various tests on our *find* method.

First of all, we defined two unbalanced trees having int and double as key values. 
We compared their behaviour with the one of an **int map** object by increasing gradually the number of elements.
The result is presented in the following plot:

![alt pic1](https://github.com/francescacairoli/AdvProgrExam/blob/master/c%2B%2B/tests/graphic_results/IntDoubleComparison.png) 


We notice that, when the BST has double nodes, its performances resemble map. On the contrary the BST with int nodes is much slower. This behaviour may depend on comparison time: bitwise comparisons are performed much faster on double values rather than integers.

Second of all, we compare balanced and unbalanced instances of our class and the map, which has an unordered equivalent named unordered_map. All the trees were set with int nodes.

![alt pic2](https://github.com/francescacairoli/AdvProgrExam/blob/master/c%2B%2B/tests/graphic_results/MapComparison.png) 





We notice how our unbalanced BST has the worst performances, while the unordered map object achieves the best ones. This is due to the fact that the find method in the unordered_map makes the access to elements faster, despite it being unordered. Our balanced tree achieved performances that are very similar to those of map, even a little bit faster. This could be explained by our simpler implementation of the class, which may enable the compiler to perform more aggressive optimizations, speeding up the research.

