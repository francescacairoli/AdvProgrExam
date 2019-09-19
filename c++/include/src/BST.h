/**
 * @file BST.h
 * @author Francesca Cairoli
 * @date 17 June 2019
 * @brief Header for the BST class containing the signature of the variables and the methods of a template binary search tree.
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
	 * @brief A node of the binary search tree. The node contains also information about its two children nodes and its parant node.
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

	/** Number of nodes in the binary search tree */
	int size;

	/** Number of horizontal layers (generations) in the binary search tree. */
	int height;

	/**
	 * @brief Recursive private method to create a deep copy of a binary search tree given the root node.
	 * @param node The root node of the tree that should be copied.
	 */
	void copy(const std::unique_ptr<Node>& node);

	/**
	 * @brief Recursive private method to builds a balanced tree from an ordered vector of key-value pairs.
	 * @param v Orderer vector of  key-value pairs.
	 * @param start The index representing the starting point in the vector, information needed for the recursion.
	 * @param end The index representing the ending point in the vector, information needed for the recursion.
	 */
	void rebuildBalancedTree(std::vector<std::pair<TK, TV>>& v, int start, int end);

	

public:
	/**
	 * @brief Default constructor for the binary search tree.
	 */
	BST(): size{0}, height{0} {}
	
	/**
	 * @brief Constructor for the binary search tree given a root node.
	 * @param d The key,value pair for the root node.
	 */
	BST(std::pair<TK, TV> d): root{new Node{d}}, size{1}, height{1} {}
	
	/**
	 * @brief Copy constructor for the binary search tree. It initializes a BST class by making a copy of an object of the same class.
	 * @param bst The BST to be copied.
	 * 
	 * The constructor uses the recursive private copy method.
	 */
	BST(const BST& bst): size{1}, height{1} {copy(bst.root);}

	/**
	 * @brief Move constructor for the binary search tree.
	 * @param bst The binary search tree to be moved into a new one.
	 */
	BST(BST&& bst) noexcept : root{std::move(bst.root)}, size{1}, height{1} {}

	/**
	 * @brief default destructor 
	 */
    ~BST() noexcept = default;

	/** 
	 * @brief Return the number of nodes in the binary search tree.
	 */
	int getSize() const noexcept { return size; }

	/** 
	 * @brief Return the number of generations of the binary search tree
	 *
	 * The height is required for graphical purposes.
	 */
	int getHeight() const noexcept { return height; }

	/**
	 * @brief Insert a new node in the binary search tree.
	 * @param kv The key,value pair to be inserted.
	 * 
	 * If a node with the same key is already present inside the tree, 
	 * the insert method substitute the value associated to that key with the new one. 
	 */
	void insert(const std::pair<TK, TV> kv);
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
	 * @brief Print the tree structure.
	 * @param f(TK) function to convert the template key type to a string
	 * @param null_str string used to graphically represent the empty positions in the binary search tree.
	 * @param empty char used as unit for graphical separation between nodes.

	Uses the method getKeyString.
	 */
	void printStructure(std::string (&f)(TK), std::string null_str = "XXX", char empty = ' ') const;

	/**
	 * @brief Returns the keys of the binary search tree as strings.

	 */
	std::string getKeyString(int index, std::string (&f)(TK), std::string null_str = "XXX") const;
	/**
	 * @brief Method used to find a node inside the binary search tree.
	 * @param key The key of the node to be found.
	 * @return Iterator An iterator to the node if the node was found, otherwise it returns an iterator to nullptr.
	 */
	Iterator find(TK key) const;
	/**
	 * @brief Balances the tree structure.
	 */
	void balance();
	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return Iterator An iterator to the node with the lowest key. 
	 */
	Iterator begin() const;
	/**
	 * @brief Used to end an iteration on the binary search tree.
	 * @return Iterator An iterator to nullptr.
	 */
	Iterator end() const { return Iterator{nullptr}; }
	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return ConstIterator A constant iterator to the node with the lowest key.
	 */
	ConstIterator cbegin() const;
	/**
	 * @brief Used to end an iteration on the binary search tree.
	 * @return ConstIterator A constant iterator to nullptr.
	 */
	ConstIterator cend() const { return ConstIterator{nullptr}; }

	/**
	 * @brief Copy assignment for the binary search tree.
	 * @param bst The BST to be copied into an existing one.
	 * @return BST& The modified binary search tree.
	 */
	BST& operator=(const BST& bst);
	/**
	 * @brief Move assignment for the binary search tree.
	 * @param bst The BST to be moved into an existing one.
	 * @return BST& The modified binary search tree.
	 */
	BST& operator=(BST&& bst);
	/**
	 * @brief Operator [] to access a node value in the tree.
	 * @param key The key of the node which value should be accessed.
	 * @return TV& The value of the accessed node.
	 */
	TV& operator[](const TK& key);
	/**
	 * @brief Constant implementation of operator [] to access a node value in the tree.
	 * @param key The key of the node which value should be accessed.
	 * @return TV& The value of the accessed node.
	 */
	const TV& operator[](const TK& key) const;
	/**
	 * @brief Operator << to print the binary search tree in ascending key order.
	 * @param os The output stream to which the strings to be printed are appended.
	 * @param bst The BST instance to be printed.
	 * @return std::ostream& The output stream to which strings have been appended.
	 */

	friend std::ostream& operator<<(std::ostream& os, BST<TK,TV>& bst)
	{	
		return bst.printOrderedList(os);
	}
};

#include "BST_NestedClasses.hxx"
#include "BST_Methods.hxx"

#endif //BST_H__