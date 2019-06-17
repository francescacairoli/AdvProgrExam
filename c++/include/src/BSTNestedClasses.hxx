/**
 * @file BSTNestedClasses.hxx
 * @author Francesca Cairoli
 * @date 17 June 2019
 * @brief Header containing the classes nested in BST: Node, Iterator and ConstIterator.
 */

#include "BST.h"

/**
 * @brief A template node of the template binary search tree with two children nodes and one parent node.
 */
template <class TK,class TV>
struct BST<TK, TV>::Node
{
	/** Key-value pair of the node. 
	 * Const was added to the key to ensure tree consistency.
	*/
	std::pair<const TK, TV> keyvalue;

	/** Node's left child node (child with lower key). */
	std::unique_ptr<Node> left;
	/** Node's right child node (child with larger key). */
	std::unique_ptr<Node> right;
	/** Node's parent node. */
	Node * parent;
	
	/**
	 * @brief Default constructor of node
	 */
	Node() {}
	/**
	 * @brief Construct a new Node with a given key-value pair but without parent and childrens.
	 * @param kv The key-value to be inserted into the node.
	 */
	Node(std::pair<TK, TV> kv): keyvalue{kv}, left{nullptr}, right{nullptr}, parent{nullptr} {}
	/**
	 * @brief Construct a new Node object with a given key-value pair and a parent.
	 * @param kv The key-value to be inserted into the node.
	 * @param p The parent of the node to be constructed.
	 */
	Node(std::pair<TK, TV> kv, Node* p) : keyvalue{kv}, left{nullptr}, right{nullptr}, parent{p} {}
	/**
	 * @brief Copy constructor for Node class.
	 * @param n The node to be copied.
	 */
	Node(const Node& n) : keyvalue{n.keyvalue}, left{nullptr}, right{nullptr}, parent{n.parent} {}
	/**
	 * @brief default destructor
	 */
	~Node() = default;

	/**
	 * @brief  Utility recursive function that returns a pointer to the lestmost node, i.e., the node with the lowest key.
	 */
	Node* leftmostdescent(){
		if(left) return left->leftmostdescent();
		return this;
	}
	/**
	 * @brief  Utility recursive function that returns a pointer to first right ancestor. 

	 If the current node is the left child of its parent ir return parent, otherwise it check wheter parent is a left child of its own parent.
	 The procedure terminates when an ancestor is found to be the left child of its own parent, otherwise a nullptr is returned.
	 */
	Node* firstrightancestor(){
		if(parent)
			if(parent->right.get()==this)
				return parent->firstrightancestor();
		return parent;
	}

};

/**
 * @brief An iterator for the BST class.
 */
template <class TK,class TV>
class BST<TK, TV>::Iterator
{
	/** Alias to make the notation easier */
	using Node = BST<TK, TV>::Node;

private:
	/** The node to which the iterator is currently referring. */
	Node * _n;

public:
	/**
	 * @brief Construct an iterator starting at node n.
	 * @param n The node on which the iterator is constructed.
	 */
	Iterator(Node * n) : _n{n} {}
	/**
	 * @brief Operator for deferencing a BST iterator.
	 * @return Node* Returns a pointer to the Node referred to by the iterator.
	 */
	Node* operator*() const{ return _n; }
	/**
	 * @brief Operator ++it to advance the iterator to the successive node.
	 * @return Iterator& Returns a reference to an iterator pointing on the next node.

	 The method uses two recursive utility functions of Node: leftmostdescent and firstrightancestor.
	 */
	Iterator& operator++(){
		if(_n){
			if(_n->right)
				_n = _n->right->leftmostdescent();
			else
				_n = _n->firstrightancestor();
		}
		return *this;
	}	
	/**
	 * @brief Operator it++ to advance the iterator to the next node.
	 * @return Iterator Returns the value (dereference) of the current iterator before advancing it to the next node.
	 */
	Iterator operator++(int)
	{
		Iterator it{*this};
		++(*this);
		return it;
	}
	/**
	 * @brief Operator == to check for iterators equality.
	 * @param it The iterator to be compared with this one.
	 * @return bool Returns True if the two iterators point to the same node, False otherwise.
	 */
	bool operator==(const Iterator& it){return _n == it._n;}

	/**
	 * @brief Operator != to check for iterators inequality.
	 * @param it The iterator to be compared with this one.
	 * @return bool Returns False if the two iterators point to the same node, True otherwise.
	 */
	bool operator!=(const Iterator& it){return _n != it._n;}
};

/**
 * @brief A constant iterator for the BST class.
 * 
 * The only difference with a normal iterator, from which it inherits, is the deferencing operator.
 */
template <class TK,class TV>
class BST<TK,TV>::ConstIterator : 
public BST<TK,TV>::Iterator
{
	/** Alias to make the notation easier */
	using Iterator = BST<TK, TV>::Iterator;

public:
	/** Uses the same method of the base class. */
	using Iterator::Iterator;
	/**
	 * @brief Operator for deferencing a BST const iterator.
	 * @return Node* Returns a const pointer to the Node referred to by the iterator.
	 */
	const Node* operator*() const{ return Iterator::operator*(); }
};
