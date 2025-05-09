#ifndef TREE_BASE_HPP
#define TREE_BASE_HPP

#ifdef DEBUG_CONTAINER
#include <iostream>
#endif

/* Based on BST */
template<typename Derived, typename NodeType>
class TreeBase {
public:
    using ValueType = typename NodeType::ValueType;

    void insert(const ValueType& v) {
        insert_impl(root_, v);
    }

    void remove(const ValueType& v) {
        remove_impl(root_, v);
    }

#ifdef DEBUG_CONTAINER
    void print_inorder(std::ostream& os = std::cout) const {
        print_inorder_impl(root_, os);
        os << '\n';
    }
#endif

    ~TreeBase() {
        clear(root_);
    }

protected:
    NodeType* root_ = nullptr;

    Derived& derived() { return static_cast<Derived&>(*this); }
    const Derived& derived() const { return static_cast<const Derived&>(*this); }

    void insert_impl(NodeType*& node, const ValueType& v) {
        if (!node) {
            node = new NodeType(v);
            return;
        }
        if (v < node->data) {
            insert_impl(node->left, v);
        } else if (v > node->data) {
            insert_impl(node->right, v);
        } else {
            return;
        }
        derived().rebalance(node);
    }

    void remove_impl(NodeType*& node, const ValueType& v) {
        if (!node) {
            return;
        }
        if (v < node->data) {
            remove_impl(node->left, v);
        } else if (v > node->data) {
            remove_impl(node->right, v);
        } else {
            if (!node->left) {
                NodeType* temp = node->right;
                delete node;
                node = temp;
            } else if (!node->right) {
                NodeType* temp = node->left;
                delete node;
                node = temp;
            } else {
                NodeType* temp = min_value_node(node->right);
                node->data = temp->data;
                remove_impl(node->right, temp->data);
            }
        }
        derived().rebalance(node);
    }

    NodeType* min_value_node(NodeType* node) {
        NodeType* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

#ifdef DEBUG_CONTAINER
    void print_inorder_impl(NodeType* node, std::ostream& os, int depth = 0) const {
        if (!node) {
            return;
        }
        
        print_inorder_impl(node->right, os, depth + 1);
        
        os << std::string(depth * 4, ' ') 
        << node->data;
        derived().additional_print(node, os);
        os << "\n";
        
        print_inorder_impl(node->left, os, depth + 1);
    }
#endif

    void clear(NodeType* node) {
        if (!node) 
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

#endif // TREE_BASE_HPP
