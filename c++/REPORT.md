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

- printOrderedList and printTree, which allows the user to visualize the tree structure respectively in a sequential and in a graphic way. They are used for the overloading of operator<< and the default between them can be specified as argument on compile time.

begin and end, which are the methods used to provide stopping conditions to the forward iteration inside the tree.

compare, which is a functional object used to perform templated comparisons between node keys. It is used to allow custom rearrangements of the tree order by the user.

operator[], which is used both to access and change the value of a specific node based on its key value.

Tests
We created a file BinarySearchTreeTest.cpp in which we compared different constructors, using different types for the templates, and in general all the functions defined in the methods section.

Benchmarks
We performed various performance tests on our BinarySearchTree class find method.

First of all, we defined two unbalanced trees having int and double as key values. We compared their behaviour with the one of an int map object by increasing gradually the number of elements. The result is presented in the following plot:



It is evident how a BinarySearchTree with double nodes have a behaviour which is consistent with the one of map, while the int one is much slower. We think that behavior could be explained by the rapidity in which the two values are compared, since a bitwise comparison can be performed much faster on double values rather than integers.

After that, we choose to compare ordered and unordered instances of our class and of map, which has an unordered equivalent named unordered_map, all having integer nodes. We performed two comparisons, in which we used both -O0 and -O3 optimization. The results obtained are presented in the graphs below:





In both cases we can see how our unordered BinarySearchTree has the worst performances, while the unordered map object achieves the best overall time. This is due to the fact that the find method in the unordered map makes the access to elements faster, despite it being unordered. In both cases our balanced tree achieved performances that are very similar to those of map, sometimes being even faster than the latter. This could be explained by our simpler implementation of the class, which may enable the compiler to perform more aggressive optimizations, speeding up the research. Overall, we can be satisfied with our implementation.

