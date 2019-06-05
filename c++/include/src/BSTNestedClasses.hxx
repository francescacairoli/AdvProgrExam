/**
 * @file BSTNestedClasses.hxx
 * @author Francesca Cairoli
 * @date 31 May 2019
 * @brief Header containing Node, Iterator and ConstIterator nested classes.
 */

#include "BST.h"

/**
 * @brief A node of the binary search tree with two children nodes and one parent node.
 */
template <class TK,class TV>
struct BST<TK, TV>::Node
{
	/** Node's data in key-value format. 
	 * Const was added to the key to ensure tree consistency.
	*/
	std::pair<const TK, TV> keyvalue;
	/** Node's left child node (smaller key). */
	std::unique_ptr<Node> left;
	/** Node's right child node (bigger key). */
	std::unique_ptr<Node> right;
	/** Node's parent node. */
	Node * parent;
	/**
	 * @brief Default constructor of node
	 * This constructor is used only to create the pseudoRoot node in the DSW algorithm.
	 */
	Node() {}
	/**
	 * @brief Construct a new Node object without parent.
	 * @param d The data to be inserted into the node.
	 */
	Node(std::pair<TK, TV> kv): keyvalue{kv}, left{nullptr}, right{nullptr}, parent{nullptr} {}
	/**
	 * @brief Construct a new Node object with a parent.
	 * @param d The data to be inserted into the node.
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
	 * @brief  utility function
	 */
	Node* leftmostdescent(){
		if(left) return left->leftmostdescent();
		return this;
	}
	/**
	 * @brief utility function
	 */
	Node* firstrightancestor(){
		if(parent)
			if(parent->right.get()==this)
				return parent->firstrightancestor();
		return parent;
	}

};

/**
 * @brief An iterator for the binary search tree class.
 */
template <class TK,class TV>
class BST<TK, TV>::Iterator
{
	/** Used to give access to getNode method */
	friend class BST;
	/** Alias to make names shorter and intuitive*/
	using Node = BST<TK, TV>::Node;
private:
	/** The node to which the iterator is currently referring. */
	Node * _n;
	/**
	 * @brief Returns a pointer to the node pointed to by the iterator.
	 */
	Node * getNode() { return _n; }
public:
	/**
	 * @brief Construct an iterator on current node.
	 * @param n The node on which the iterator is constructed.
	 */
	Iterator(Node * n) : _n{n} {}
	/**
	 * @brief Operator it() for deferencing a binary search tree iterator.
	 * @return std::pair<TKey, TValue>& Reference to current node's data in key, value format.
	 */
	Node* operator*() const{ return _n; }
	/**
	 * @brief Operator ++it to advance iterator to the next node.
	 * @return Iterator& Reference to an iterator pointing on the next node.
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
	 * @brief Operator it++ to advance iterator to the next node.
	 * @return Iterator Value of the current iterator before advancing it to the next node.
	 */
	Iterator operator++(int)
	{
		Iterator it{*this};
		++(*this);
		return it;
	}
	/**
	 * @brief Operator == to check for iterators equality.
	 * @param other The iterator to be compared with this one.
	 * @return True if iterators point to the same node, else false
	 */
	bool operator==(const Iterator& it){return _n == it._n;}

	/**
	 * @brief Operator != to check for iterators inequality.
	 * @param other The iterator to be compared with this one.
	 * @return False if iterators point to the same node, else true.
	 */
	bool operator!=(const Iterator& it){return _n != it._n;}
};

/**
 * @brief A constant iterator for the binary search tree class.
 * 
 * The only difference with a normal iterator from which it inherits is the 
 * constant pair returned by the deferencing operator.
 */
template <class TK,class TV>
class BST<TK,TV>::ConstIterator : 
public BST<TK,TV>::Iterator
{
	/** Used to give access to getNode method */
	friend class BST;
	/** Alias to make names shorter and intuitive*/
	using Iterator = BST<TK, TV>::Iterator;
private:
	/**
	 * @brief Returns a constant pointer to the node pointed to by the iterator.
	 */
	const Node * getNode() const { return Iterator::getNode(); }
public:
	/** Uses the same method of the base class. */
	using Iterator::Iterator;
	/**
	 * @brief Operator it() for deferencing a binary search tree iterator.
	 * @return const std::pair<TKey, TValue>& Constant reference to current 
	 * node's data in key, value format.
	 */
	const Node* operator*() const{ return Iterator::operator*(); }
};
