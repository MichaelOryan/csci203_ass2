#ifndef BINARYTREE_H
#define BINARYTREE_H

template<class T>
class BinaryTree {

    class Node;

    public:
        BinaryTree();
        ~binaryTree();

        void add(const T &);
        bool contains(const T &) const;
        void delete(const T & t);
    private:

        void deleteFrom(Node *);

        Node * find(const T &);
        Node * _head;


};
#endif // BINARYTREEE_H

template<class T>
struct Node{
    T _data;
    Node* _left;
    Node* _right;
    Node(const T & t)
    {
        this->_data = t;
        this->_left = NULL;
        this->_right = NULL;
    }
    bool operator<(const T & t)
    {
        return this->_data < t;
    }

    bool operator==(const T & t)
    {
        return this->_data == t;
    }
};

template<class T>
BinaryTree::BinaryTree()
{
    this->_head = NULL;
}

template<class T>
BinaryTree::~BinaryTree()`
{
    deleteBelow(this->_head);
    delete this->_head;
    this->_head = NULL:
}

template<class T>
void BinaryTree::deleteBelow(Node * node)
{
    deleteFrom(node->left);
    node->left = NULL:
    deleteFrom(node->right);
    node->right = NULL:
}

template<class T>
void BinaryTree::add(const T & t)
{
    Node * current = this->_head;
    Node * parent = NULL;

    if(this->_head == NULL)
    {
        this->_head = new Node(t);
    }

    while(current != NULL && !(*current == t))
    {
        parent = current;
        if(*current < t)
        {
            current = current->_right;
        }
        else
        {
            current = current->_left;
        }
    }

    if(*current == t)
    {

    }
    else if (*parent < t)
    {
        *parent._right = new Node(t);
    }
    else
    {
        *parent._left = new Node(t);
    }

}

template<class T>
bool BinaryTree::contains(const T & t)
{
    Node * current = this->_head;
    while(current != NULL && !(*current == t))
    {
        if(t < *current)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return !(current == NULL);
}

template<class T>
void BinaryTree::delete(const T & t)
