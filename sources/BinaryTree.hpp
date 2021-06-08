#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include "orderMethods.hpp"
// #define COUNT 10
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
            Node(T input_value) : value(input_value), left(nullptr), right(nullptr) {}
        };

        /*===========================================Private-Methods=========================================*/

    private:
        Node *root;                       // the root of the tree
        std::multimap<T, Node *> my_tree; // contains all the nodes in the tree

        // this function makes a deep copy
        void copy(Node *to_tree, const Node *from_tree)
        {
            // TODO
            // if (from_tree != nullptr)
            // {
            //     to_tree = new Node(from_tree->value);
            //     copy(to_tree->right, from_tree->right);
            //     copy(to_tree->left, from_tree->left);
            // }
            if (from_tree->right != nullptr)
            {
                to_tree->right = new Node(from_tree->right->value);
                copy(to_tree->right, from_tree->right);
            }
            if (from_tree->left != nullptr)
            {
                to_tree->left = new Node(from_tree->left->value);
                copy(to_tree->left, from_tree->left);
            }
        }

        // This function search the given node value in the tree and return a poniter to its node
        Node *search_node(T target_value)
        {
            Node *target_node = nullptr;
            // the tree is not empty
            if (this->root != nullptr)
            {
                auto search = my_tree.find(target_value);
                if (search != my_tree.end())
                {
                    // std::cout << target_value << " - Found\n";
                    target_node = search->second;
                }
                else
                {
                    // std::cout << target_value << " - Not found\n";
                    target_node = nullptr;
                }
                // std::cout << "my tree: ";
                // for (auto kv : my_tree)
                // {
                //     auto &key = kv.first;
                //     std::cout << key << ", ";
                // }
                // std::cout << std::endl;
            }

            return target_node;
        }

        void add_to_map(T node_value, Node *node_pointer)
        {
            //inserts the node into the multimap
            my_tree.insert({node_value, node_pointer});
        }

        void delete_all_the_nodes(Node *current)
        {
            if (current->left != nullptr)
            {
                delete_all_the_nodes(current->left);
            }
            if (current->right != nullptr)
            {
                delete_all_the_nodes(current->right);
            }
            delete current;
        }

        /*===========================================Public-Methods=========================================*/

    public:
        // constructor
        BinaryTree()
        {
            this->root = nullptr;
        }
        // copy constructor
        BinaryTree(const BinaryTree &other)
        {
            if (other.root != nullptr)
            {
                this->root = new Node(other.root->value);
                copy(this->root, other.root);
            }
        }
        // distructor
        ~BinaryTree()
        {
            if (this->root != nullptr)
            {
                delete_all_the_nodes(this->root);
            }
        }
        // move constructor
        BinaryTree(BinaryTree &&tree) noexcept;

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
                my_tree.erase(this->root->value);
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
            // parent exists
            if (p != nullptr)
            {
                // the parent has not a left child
                if (p->left == nullptr)
                {
                    p->left = new Node(left_child);
                    //inserts the new node into the multimap
                    add_to_map(left_child, p->left);
                }
                // the parent already has a left child
                else
                {
                    my_tree.erase(p->left->value);
                    p->left->value = left_child;
                    //inserts the new node into the multimap
                    add_to_map(left_child, p->left);
                }
            }

            else
            {
                throw std::invalid_argument("Error: the parent does not exist in the tree");
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

            Node *p = search_node(parent);
            // parent exists
            if (p != nullptr)
            {
                // the parent has not a right child
                if (p->right == nullptr)
                {
                    p->right = new Node(right_child);
                    //inserts the new node into the multimap
                    add_to_map(right_child, p->right);
                }
                // the parent already has a right child
                else
                {
                    my_tree.erase(p->right->value);
                    p->right->value = right_child;
                    //inserts the new node into the multimap
                    add_to_map(right_child, p->right);
                }
            }

            else
            {
                throw std::invalid_argument("Error: the parent does not exist in the tree");
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
            void preorder_method(Node *current)
            {
                if (current == nullptr)
                {
                    return;
                }
                nodes_container.push_back(current);
                preorder_method(current->left);
                preorder_method(current->right);
            }
            // in
            void inorder_method(Node *current)
            {
                if (current == nullptr)
                {
                    return;
                }
                inorder_method(current->left);
                nodes_container.push_back(current);
                inorder_method(current->right);
            }
            // post
            void postorder_method(Node *current)
            {
                if (current == nullptr)
                {
                    return;
                }
                postorder_method(current->left);
                postorder_method(current->right);
                nodes_container.push_back(current);
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

            Iterator(Node *node) : current(node) {}
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
            Iterator operator++(int)
            {
                Iterator temp(nodes_container[0]);
                ++*this;
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
            // // Base case
            // if (root == NULL)
            //     return;

            // // Increase distance between levels
            // space += COUNT;

            // // Process right child first
            // print_tree(root->right, space);

            // // Print current node after space count
            // os << std::endl;
            // for (int i = COUNT; i < space; i++)
            //     os << " ";
            // os << root->value << "\n";

            // // Process left child
            // print_tree(root->left, space);
        }

        /*========================================Operator-Overloading===========================================*/

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree)
        {
            // Pass initial space count as 0
            BinaryTree<T>::print_tree(tree->root, 0, os);
            return os;
        }

        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            // delete the root
            if (this->root)
            {
                delete root;
            }
            // update the root to the other root
            this->root = other.root;
            // update the other root to be nullptr
            other.root = nullptr;
            return *this;
        }

        BinaryTree &operator=(const BinaryTree<T> &other)
        {
            // same tree
            if (this == &other)
            {
                return *this;
            }
            // delete the old root
            if (this->root != nullptr)
            {
                delete this->root;
            }
            // if the other tree has a root, then copy the tree
            if (other.root != nullptr)
            {
                this->root = new Node{other.root->value};
                copy(this->root, other.root);
            }
            return *this;
        }
    };
}