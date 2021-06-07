#include <iostream>
#include <stdio.h>
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
        // I got the idea from Lior Atiya
        class Iterator
        {
        private:
            std::vector<Node<T> *> nodes_container;
            Node *current;
            // pre
            void preorder_method()
            {
                nodes_container.clear();
                current = this->root;
                while (current)
                {
                    nodes_container.push_back(current);
                    preorder_method(current->left);
                    preorder_method(current->right);
                }
            }
            // in
            void inorder_method()
            {
                nodes_container.clear();
                current = this->root;
                while (current)
                {
                    inorder_method(current->left);
                    nodes_container.push_back(current);
                    inorder_method(current->right);
                }
            }
            // post
            void postorder_method()
            {
                nodes_container.clear();
                current = this->root;
                while (current)
                {
                    postorder_method()(current->left);
                    postorder_method()(current->right);
                    nodes_container.push_back(current);
                }
            }

        public:
            Iterator(std::string order_method)
            {
                switch (order_method)
                {
                case "pre":
                    preorder_method();
                    current = nodes_container[0];
                    break;
                case "in":
                    inorder_method();
                    current = nodes_container[0];
                    break;
                case "post":
                    postorder_method();
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
                    current->value = nodes_container[0];
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
                if (nodes_container.size() > 1)
                {
                    Iterator temp = *this;
                    nodes_container.erase(nodes_container.begin());
                    current->value = nodes_container[0];
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

        Iterator begin("in")
        {
            return Iterator();
        }
        Iterator end()
        {
            return Iterator();
        }
        Iterator begin_preorder("pre")
        {
            return Iterator();
        }
        Iterator end_preorder()
        {
            return Iterator();
        }
        Iterator begin_inorder("in")
        {
            return Iterator();
        }
        Iterator end_inorder()
        {
            return Iterator();
        }
        Iterator begin_postorder("post")
        {
            return Iterator();
        }
        Iterator end_postorder()
        {
            return Iterator();
        }

        /*==================================================Utility-Function================================================*/
        // source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
        void print_tree(Node *root, int space, std::ostream &os)
        {
            // Base case
            if (root == NULL)
                return;

            // Increase distance between levels
            space += COUNT;

            // Process right child first
            print_tree(root->right, space);

            // Print current node after space count
            os << endl;
            for (int i = COUNT; i < space; i++)
                cout << " ";
            coosut << root->value << "\n";

            // Process left child
            print_tree(root->left, space);
        }

        /*========================================Operator-Overloading===========================================*/

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree)
        {
            // Pass initial space count as 0
            print_tree(tree->root, 0, os);
            return os;
        }
    };
}
