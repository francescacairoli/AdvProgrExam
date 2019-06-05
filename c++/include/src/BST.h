/**
 * @file BinarySearchTree.h
 * @author Francesca Cairoli
 * @date 30 mAy 2019
 * @brief Header containing variables and method names for the BinarySearchTree class.
 */

#include <iostream> // needed for the << operator
#include <memory> // needed for unique pointers
#include <vector> 

#ifndef BST_H__
#define BST_H__

/**
 * @brief Implementation of a template binary search tree.
 * @tparam TK Type of the key of a node.
 * @tparam TV Type of the value of a node.
 */
template <class TK,class TV>
class BST
{
private:
	/**
	 * @brief A node of the binary search tree with two children nodes and one parent node.
	 */
	struct Node;

public:
	/**
	 * @brief An iterator for the binary search tree.
	 */
	class Iterator;
	/**
	 * @brief A const iterator for the binary search tree.
	 */
	class ConstIterator;

private:
	/** Root node of the binary search tree. */
	std::unique_ptr<Node> root;
	int size;
	int height;

	/**
	 * @brief Recursive private method to create a deep copy of a binary search tree given the root node.
	 * @param node The root node of the tree that should be copied.
	 */
	void copy(const std::unique_ptr<Node>& node);

	/**
	 * @brief Recursive private method to builds a balanced tree from an ordered vector of pairs.
	 * @param v Orderer vector of pairs in key,value format.
	 * @param start The id of the first element of the list, for recursion purposes.
	 * @param end The id of the last element of the list, for recursion purposes.
	 */
	void rebuildBalancedTree(std::vector<std::pair<TK, TV>>& v, int start, int end);

	

public:
	/**
	 * @brief Default constructor for binary search tree.
	 */
	BST() {}
	/**
	 * @brief Constructor for binary search tree given a root node.
	 * @param d The key,value pair for the root node.
	 */
	BST(std::pair<TK, TV> d): root{new Node{d}} {}
	/**
	 * @brief Copy constructor for the binary search tree.
	 * @param bst The binary search tree to be copied.
	 * 
	 * The method uses the copy private method.
	 */
	BST(const BST& bst) { copy(bst.root); }
	/**
	 * @brief Move constructor for the binary search tree.
	 * @param bst The binary search tree to be moved into a new one.
	 */
	BST(BST&& bst) noexcept : root{std::move(bst.root)} {}

	/** 
	 * @brief Return the number of nodes in the binary search tree.
	 */
	int getSize() { return size; }

	/** 
	 * @brief Return the number of generations of the binary search tree
	 *
	 * The height is required for graphical purposes.
	 */
	int getHeight() { return height; }

	/**
	 * @brief Insert a new node in the binary search tree.
	 * @param kv The key,value pair to be inserted.
	 * 
	 * If a node with the same key is already present inside the tree, 
	 * the insert method does not perform any action. 
	 */
	void insert(std::pair<TK, TV> kv);
	/**
	 * @brief Clears all the elements of the tree
	 */
	void clear() { root.reset(); }
	/**
	 * @brief Prints nodes in ascending key order.
	 * @param os The stream to which nodes are sent.
	 */
	std::ostream& printOrderedList(std::ostream& os) const;

	/**
	 * @brief Print the tree structure
	 */
	void printStructure(std::string (&f)(TK), std::string null_str = "XXX", char empty = ' ') const;

	std::string getKeyString(int index, std::string (&f)(TK), std::string null_str = "XXX") const;
	/**
	 * @brief Used to find a node inside the tree.
	 * @param key The key of the node to be found.
	 * @return Iterator An iterator to the node if it's found, else to end().
	 */
	Iterator find(TK k) const;
	/**
	 * @brief Balances the tree to preserve its performances.
	 * 
	 * The method is inspired from the Day algorithm, taking full
	 * advantage of the iterators and the methods we already created
	 * to make it as simple as possible.
	 */
	void balance();
	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return Iterator An iterator to the leftmost node of the tree. 
	 * aka the one with the lowest key value.
	 */
	Iterator begin() const;
	/**
	 * @brief Used to finish an iteration on the binary search tree.
	 * @return Iterator Returns an iterator to nullptr.
	 */
	Iterator end() const { return Iterator{nullptr}; }
	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return ConstIterator A constant iterator to the leftmost node of the tree.
	 * aka the one with the lowest key value.
	 */
	ConstIterator cbegin() const;
	/**
	 * @brief Used to finish an iteration on the binary search tree.
	 * @return ConstIterator Returns a constant iterator to nullptr.
	 */
	ConstIterator cend() const { return ConstIterator{nullptr}; }

	/**
	 * @brief Copy assignment for binary search tree.
	 * @param bst The binary search tree to be copied into an existing one.
	 * @return BinarySearchTree& The modified existing tree.
	 */
	BST& operator=(const BST& bst);
	/**
	 * @brief Move assignment for binary search tree.
	 * @param bst The binary search tree to be moved into an existing one.
	 * @return BinarySearchTree& The modified existing tree.
	 */
	BST& operator=(BST&& bst);
	/**
	 * @brief Operator [] to access a node value in the tree or insert a new one.
	 * @param key The key of the node which value should be accessed.
	 * @return TValue& The value of the accessed node.
	 */
	TV& operator[](const TK& key);
	/**
	 * @brief Constant implementation of operator [] to access a node value in the tree or insert a new one.
	 * @param key The key of the node which value should be accessed.
	 * @return TValue& The value of the accessed node.
	 */
	const TV& operator[](const TK& key) const;
	/**
	 * @brief Operator << to print the binary search tree in ascending key order.
	 * @param os The output stream to which the strings to be printed are appended.
	 * @param bst The binary search tree instance to be printed.
	 * @return std::ostream& The output stream to which strings have been appended.
	 */

	friend std::ostream& operator<<(std::ostream& os, BST<TK,TV>& bst)
	{	
		return bst.printOrderedList(os);
	}
};

#include "BSTNestedClasses.hxx"
#include "BSTMethods.hxx"

#endif //BST_H__