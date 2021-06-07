#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include "orderMethods.hpp"
#define COUNT 10
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
            // constructors
            Node() = default;
            Node(T input_value)
            {
                this->value = input_value;
                this->left = nullptr;
                this->right = nullptr;
            }
            // destructor
            ~Node();

            // overloading
            bool operator==(Node other)
            {
                return this->value == other->value && this->left == other->left && this->right == other->right;
            }

            bool operator!=(Node other)
            {
                return this->value != other->value || this->left != other->left || this->right != other->right;
            }
        };

        /*===========================================Private-Methods=========================================*/

    private:
        Node *root;                       // the root of the tree
        std::multimap<T, Node *> my_tree; // contains all the nodes in the tree

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
        BinaryTree(const BinaryTree &other);

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

            Node *p = search_node(parent);
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
        // I got the idea from Lior Atiya
        class Iterator
        {
        private:
            std::vector<Node *> nodes_container;
            Node *current;
            // pre
            void preorder_method(Node *root)
            {
                nodes_container.clear();
                current = root;
                while (current)
                {
                    nodes_container.push_back(current);
                    preorder_method(current->left);
                    preorder_method(current->right);
                }
            }
            // in
            void inorder_method(Node *root)
            {
                nodes_container.clear();
                current = root;
                while (current)
                {
                    inorder_method(current->left);
                    nodes_container.push_back(current);
                    inorder_method(current->right);
                }
            }
            // post
            void postorder_method(Node *root)
            {
                nodes_container.clear();
                current = root;
                while (current)
                {
                    postorder_method(current->left);
                    postorder_method(current->right);
                    nodes_container.push_back(current);
                }
            }

        public:
            Iterator(Methods order_method, Node *root)
            {
                switch (order_method)
                {
                case preorder:
                    preorder_method(root);
                    current = nodes_container[0];
                    break;
                case inorder:
                    inorder_method(root);
                    current = nodes_container[0];
                    break;
                case postorder:
                    postorder_method(root);
                    current = nodes_container[0];
                    break;
                default:
                    throw std::invalid_argument("Error: invalid order_method");
                    break;
                }
            }

            Iterator() : current(nullptr) {}

            T &operator*()
            {
                return current->value;
            }

            T *operator->()
            {
                return &(current->value);
            }

            // ++i;
            Iterator &operator++()
            {
                if (nodes_container.size() > 1)
                {
                    nodes_container.erase(nodes_container.begin());
                    current = nodes_container[0];
                }
                else
                {
                    current = nullptr;
                }
                return *this;
            }

            // i++;
            const Iterator operator++(int)
            {
                Iterator temp;
                if (nodes_container.size() > 1)
                {
                    temp = *this;
                    nodes_container.erase(nodes_container.begin());
                    current = nodes_container[0];
                }
                else
                {
                    temp = nullptr;
                }
                return temp;
            }

            bool operator==(const Iterator &other)
            {
                return current == other.current;
            }

            bool operator!=(const Iterator &other)
            {
                return current != other.current;
            }
        };

        /*==========================================iterators-Methods===========================================*/

        Iterator begin()
        {
            return Iterator(inorder, this->root);
        }
        Iterator end()
        {
            return Iterator();
        }
        Iterator begin_preorder()
        {
            return Iterator(preorder, this->root);
        }
        Iterator end_preorder()
        {
            return Iterator();
        }
        Iterator begin_inorder()
        {
            return Iterator(inorder, this->root);
        }
        Iterator end_inorder()
        {
            return Iterator();
        }
        Iterator begin_postorder()
        {
            return Iterator(postorder, this->root);
        }
        Iterator end_postorder()
        {
            return Iterator();
        }

        /*==================================================Utility-Function================================================*/
        // source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
        static void print_tree(Node *root, int space, std::ostream &os)
        {
            // Base case
            if (root == NULL)
                return;

            // Increase distance between levels
            space += COUNT;

            // Process right child first
            print_tree(root->right, space);

            // Print current node after space count
            os << std::endl;
            for (int i = COUNT; i < space; i++)
                os << " ";
            os << root->value << "\n";

            // Process left child
            print_tree(root->left, space);
        }

        /*========================================Operator-Overloading===========================================*/

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree)
        {
            // Pass initial space count as 0
            BinaryTree<T>::print_tree(tree->root, 0, os);
            return os;
        }
    };
}
