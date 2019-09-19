/**
 * @file BSTMethods.hxx
 * @author Francesca Cairoli
 * @date 30 May 2019
 * @brief Header containing method definitions for the BST class.
 */

#include "BST.h"

// Private Methods


template <class TK,class TV>
void BST<TK, TV>::copy(const std::unique_ptr<Node>& node)
{
    if(node)
    {
        insert(node->keyvalue);
        copy(node->left);
        copy(node->right);
    }
}

template <class TK,class TV>
void BST<TK, TV>::rebuildBalancedTree(std::vector< std::pair<TK,TV> > &v, int start, int end)
{
    if(start>end) return;

    if(start==end) {insert(v[start]); return;}
        
    int mid = (start+end)/2;
    insert(v[mid]);
    rebuildBalancedTree(v, start, mid-1);
    rebuildBalancedTree(v, mid+1, end);
}



// Public methods

template <class TK,class TV>
void BST<TK, TV>::insert(const std::pair<TK, TV> kv){
    int h = 1;
    Node * parent = root.get();
    if( !parent ) {root.reset(new Node{kv});}// if tree is empty insert node as root
    else{
       
        while(1){
            if(parent->keyvalue.first==kv.first){
                parent->keyvalue.second=kv.second;
                break;
            }else if(parent->keyvalue.first < kv.first){
                h++;
                if(parent->right)
                    parent=(parent->right).get();
                else{
                    parent->right.reset(new Node{kv,parent});
                    break;
                } 
            } else {
                h++;
                if(parent->left)
                    parent=(parent->left).get();
                else{
                    parent->left.reset(new Node{kv,parent});
                    break;
                }
            }
        }
    }
    size++;
    if(getHeight()<h) height=h;
}

template <class TK,class TV>
std::ostream& BST<TK, TV>::printOrderedList(std::ostream& os) const
{
    ConstIterator it{cbegin()};
    ConstIterator end{cend()};
    if(it == end)
    {
        os << "The tree is empty!" << std::endl;
    }
    for(; it != end; ++it)
    {
        os << (*it)->keyvalue.first << ": " << (*it)->keyvalue.second << std::endl;
    }
    return os;
}


template <class TK,class TV>
typename BST<TK, TV>::Iterator BST<TK, TV>::find(TK key) const
{
    Node * current= root.get();
    while(current)
        if(key == current->keyvalue.first)
            return Iterator(current);
        else if(key < current->keyvalue.first)
            current = current->left.get();
        else
            current = current->right.get();
    return end();
}


template <class TK,class TV>
void BST<TK, TV>::balance()
{
    std::vector< std::pair<TK,TV> > v;
    for (auto x :  *this)
        v.push_back(x->keyvalue);
    clear();
    rebuildBalancedTree(v, 0, v.size() - 1);
    
}

template <class TK,class TV>
typename BST<TK, TV>::Iterator BST<TK, TV>::begin() const
{ 
    if(!root) return end();

    return Iterator(root->leftmostdescent());
}

template <class TK,class TV>
typename BST<TK, TV>::ConstIterator BST<TK, TV>::cbegin() const
{
    if(!root)
    {
        return ConstIterator{nullptr};
    }
    return ConstIterator(root->leftmostdescent());
}

// Operators

template <class TK,class TV>
BST<TK, TV>& BST<TK, TV>::operator=(const BST& bst)
{
    clear(); 
    copy(bst.root);
    return *this;
}

template <class TK,class TV>
BST<TK, TV>& BST<TK, TV>::operator=(BST&& bst)
{
    root = std::move(bst.root);
    return *this;
}

template <class TK,class TV>
TV& BST<TK, TV>::operator[](const TK& key)
{
    std::pair<TK, TV> pair{key, TV{}};
    Iterator it{*find(key)};
    return (*it)->keyvalue.second;
}

template <class TK,class TV>
const TV& BST<TK, TV>::operator[](const TK& key) const
{
    std::pair<TK, TV> pair{key, TV{}};
    ConstIterator it{*find(key)}; // dereferencing operator *
    if (it == cend())
    {
        throw; // The key is not present in the tree.
    }
    return (*it)->keyvalue.second;
}

template <class TK,class TV>
std::string BST<TK, TV>::getKeyString(int index, std::string (&f)(TK), std::string null_str ) const//= "XXX"
{
    Node * current = root.get();
    int mask = 1;

    while(index >= mask<<1) mask = mask<<1; 
    mask = mask>>1;
    while(mask > 0){
        if(!current) {break;}
        if((index & mask) > 0) current = current->right.get();
        else current = current->left.get();
        mask = mask >> 1;
    }
    if(current) return f(current->keyvalue.first);
    return null_str;
}

template <class TK,class TV>
void BST<TK, TV>::printStructure(std::string (&f)(TK), std::string null_str, char empty ) const// = "XXX" = ' '
{
    int elements = 1;
    elements = elements << height;
    int newline = 1;
    int space_index = height-1; // at each layer the space between nodes changes

    std::cout<<std::string( (1<<space_index) - 1, empty);

    for(int iii = 1;iii<elements;iii++){
        std::cout << getKeyString(iii, f, null_str) << std::string( ( (1 << (space_index+1) ) - 1) , empty);

        if(iii==newline){
            if(space_index) space_index--;
            std::cout<<std::endl<<std::string( (1<<space_index) - 1, empty);
            newline = (newline<<1)+1;
        }
    }
}