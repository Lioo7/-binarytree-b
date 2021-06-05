#include <iostream>
#include <stdio.h>
using namespace std;
namespace ariel
{
    /*====================================Implementation-Of-A-Generic-Binary-Tree=============================*/
    template <typename T>
    class BinaryTree
    {
        /*===========================================Inner-Node-Class=========================================*/
        class Node
        {
        public:
            T value;     // the value of the node
            Node *left;  // left child
            Node *right; //right child
            // constructor
            Node(T input_value)
            {
                this->value = input_value;
                this->left = nullptr;
                this->right = nullptr;
            }
            // destructor
            ~Node();

        };

        /*===========================================Private-Methods=========================================*/

        Node *root;                  // the root of the tree
        multimap<T, Node *> my_tree; // contains all the nodes in the tree

        // This function search the given node value in the tree and return a poniter to its node
        Node *search_node(T target_value)
        {
            Node target_node;
            // the tree is empty
            if (this->root == nullptr)
            {
                target_node = nullptr;
            }
            // the tree is not empty
            else
            {
                target_node = my_tree.find(target_value);
            }

            return target_node;
        }

        void add_to_map(T node_value, Node *node_pointer)
        {
            //inserts the node into the multimap
            my_tree.insert({node_value, node_pointer});
        }

        /*===========================================Public-Methods=========================================*/

    public:
        // constructor
        BinaryTree()
        {
            this->root = nullptr;
        }
        // copy constructor
        

        /*===========================================Insert-Methods=========================================*/

        // gets an input and puts it at the root of the tree
        BinaryTree<T> &add_root(T new_root_value)
        {
            // empty tree
            if (root == nullptr)
            {
                root = new Node(new_root_value);
            }
            // there is a root already
            else
            {
                root->value = new_root_value;
            }
            //inserts the root into the multimap
            add_to_map(new_root_value, root);

            return *this;
        }

        // adds a new node to be the left child of the exist given parent
        BinaryTree<T> &add_left(T parent, T left_child)
        {
            // the tree is empty
            if (root == nullptr)
            {
                throw std::invalid_argument("Error: can't add this element beacuse the tree is empty");
            }

            Node p = search_node(parent);
            // parent does not exist
            if (p == nullptr)
            {
                throw std::invalid_argument("Error: the parent does not exist in the tree");
            }
            // the parent has not a left child
            else if (p->left == nullptr)
            {
                p->left = new Node(left_child);
                //inserts the new node into the multimap
                add_to_map(left_child, p->left);
            }
            // the parent already has a left child
            else
            {
                p->left->value = left_child;
            }

            return *this;
        }

        // adds a new node ot be the right child of the exist given parent
        BinaryTree<T> &add_right(T parent, T right_child)
        {
            // the tree is empty
            if (root == nullptr)
            {
                throw std::invalid_argument("Error: can't add this element beacuse the tree is empty");
            }

            Node p = search_node(parent);
            // parent does not exist
            if (p == nullptr)
            {
                throw std::invalid_argument("Error: the parent does not exist in the tree");
            }
            // the parent has not a right child
            else if (p->right == nullptr)
            {
                p->right = new Node(right_child);
                //inserts the new node into the multimap
                add_to_map(right_child, p->right);
            }
            // the parent already has a right child
            else
            {
                p->right->value = right_child;
            }

            return *this;
        }

        /*========================================Inner-Iterator-Class==================================*/

        class Iterator
        {
        private:
            Node *p;

        public:
            Iterator()
            {
            }

            T &operator*()
            {
                return p->value;
            }

            T *operator->()
            {
                return &(p->value);
            }

            // ++i;
            Iterator &operator++()
            {
                p = p->left;
                return *this;
            }

            // i++;
            const Iterator operator++(int)
            {
                Iterator temp = *this;
                p = p->left;
                return temp;
            }

            bool operator==(const Iterator &other)
            {
                return p == other.p;
            }

            bool operator!=(const Iterator &other)
            {
                return p != other.p;
            }
        };

        /*==========================================iterators-Methods===========================================*/

        Iterator begin()
        {
            return Iterator();
        }
        Iterator end()
        {
            return Iterator();
        }
        Iterator begin_preorder()
        {
            return Iterator();
        }
        Iterator end_preorder()
        {
            return Iterator();
        }
        Iterator begin_inorder()
        {
            return Iterator();
        }
        Iterator end_inorder()
        {
            return Iterator();
        }
        Iterator begin_postorder()
        {
            return Iterator();
        }
        Iterator end_postorder()
        {
            return Iterator();
        }

        /*========================================Operator-Overloading===========================================*/

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree)
        {
            // TODO: add some code here
            return os;
        }
    };
}
