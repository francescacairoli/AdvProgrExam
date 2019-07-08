# Introduction

The purpose of the assigned C++ project is to implement a templated binary search tree, complete with iterators.
The final goal is to compare the behavior of my custom implementation, either in a balanced or unbalanced situation, 
with the behaviour of the map and unordered_map standard libraries. 

## Code structure

The BST class relies on a nested class, called Node, defined by a template pair of a key and a value. 
Allowing nodes to have a template type for the keys-value pair, results in the possibility of building
template trees, that is, trees with different types of nodes.

We defined the **Node** as a *struct* because we want all its methods and variables to be public for the tree to use. 
However, we placed the struct nested inside the tree and set it as private, in order not to exposed it to the user. 
The Node's key is set as constant in order to prevent any user to modify its value and thus corrupt
the inner structure of the tree. A node contains three pointers: one points to its parent node and the remaining two point 
to its children. For the pointers to children nodes we used the *unique_ptr* class defined in the standard library.
We expect this choice to facilitate the management of the memory and to improve the consistence of the operations on the tree.

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

+ Constructors for the class Node:
- using a pair of values, 
- using a parent and possibly another node (copy constructor).

+ The iterators notably have an overloading of the operator* which returns a pointer to the node.

+ The method *getNode* was added in order to retrive the Node pointed by the iterator and is defined as private in order not to expose the Node class.

+ BST methods:

- Copy and move semantic, implemented as constructors and overloadings of operator=. 
This allows us to perform deep copies of a tree or moving its elements into another tree structure. 
It make use of the *copy* recursive method to perform the insertion.

- *balance* performs a recursive insertion of elements through bisection on a vector containing the ordered keys. 
It relies strongly on iterators and unique pointers. It uses the function *rebuildBalancedTree*.

- *printStructure* (additional) allows the user to visualize the tree structure in a graphic way. For visualize the order in a sequential way we used the overloading of operator<<.

- *begin* (*cbegin*) and *end* (*cend*) are the methods used to provide starting and stopping conditions to the forward iteration inside the tree.

- *operator[]* is used both to access and change the value of a specific node based on its key value.

## Tests
The file *BST_Test.cpp* is used to observe different behaviours of the BST. It compares different constructors, it tries different types for the template, and in general it tests all the functions defined above.

## Performances
In order to measure the look-up performaces, we performed various tests on our *find* method in the BST class.

First of all, we defined two unbalanced trees having int and double as key values. 
We compared their behaviour with the one of an **int map** object by increasing gradually the number of elements.
The result is presented in the following plot:

![alt pic1](https://github.com/francescacairoli/AdvProgrExam/blob/master/c%2B%2B/tests/graphic_results/IntDoubleComparison.png) 


We notice that, when the BST has double nodes, its performances resemble map. On the contrary the BST with int nodes is much slower. This behaviour may depend on comparison time: bitwise comparisons are performed much faster on double values rather than integers.

Second of all, we compare balanced and unbalanced instances of our class and the map, which has an unordered equivalent named unordered_map. All the trees were set with int nodes.

![alt pic2](https://github.com/francescacairoli/AdvProgrExam/blob/master/c%2B%2B/tests/graphic_results/MapComparison.png) 





We notice how our unbalanced BST has the worst performances, while the unordered map object achieves the best ones. This is due to the fact that the find method in the unordered_map makes the access to elements faster, despite it being unordered. Our balanced tree achieved performances that are very similar to those of map, even a little bit faster. This could be explained by our simpler implementation of the class, which may enable the compiler to perform more aggressive optimizations, speeding up the research.

