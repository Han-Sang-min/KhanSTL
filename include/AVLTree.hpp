#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "TreeBase.hpp"

namespace avl {

    template <typename DataType>
    struct Node {
        using ValueType = DataType;
        DataType data;
        Node* left;
        Node* right;
        int height;
        Node(const DataType& inData) 
            : data(inData), left(nullptr), right(nullptr), height(1) {}
    };
    
} // namespace avl

template<typename DataType>
class AVLTree : public TreeBase<AVLTree<DataType>, avl::Node<DataType> > {
    template<typename, typename>
    friend class TreeBase;
    
    using Node = avl::Node<DataType>;
protected:
    void rebalance(Node*& node) {
        if (node == nullptr) {
            return;
        }
        
        node->height = max_child_height(node) + 1;

        int bal = get_balance(node);
        /* XXX: If the remove operation is added, should we also check for cases where the avl_node is null? */
        if (bal > 1) {
            /* Case LR (first half of LR) */
            if (get_balance(node->left) < 0) {
                left_rotate(node->left);
            }
            /* Case LL (and also the second half of LR)*/
            right_rotate(node);
        } else if (bal < -1) {
            /* Case RL (first half of RL) */
            if (get_balance(node->right) > 0) {
                right_rotate(node->right);
            }
            /* Case RR (and also the second half of RL) */
            left_rotate(node);
        }
    }

#ifdef DEBUG_CONTAINER
    void additional_print(Node* node, std::ostream& os) const {
        os << "(h:" << node->height << ") ";
    }
#endif

private:
    int height(Node* node) const {
        return node ? node->height : 0;
    }
    
    inline int max_child_height(Node* n) const {
        int lh = height(n->left);
        int rh = height(n->right);
        return (lh > rh) ? lh : rh;
    }

    int get_balance(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void right_rotate(Node*& y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;

        y->height = max_child_height(y) + 1;
        x->height = max_child_height(x) + 1;

        y = x;
    }

    void left_rotate(Node*& x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        x->height = max_child_height(x) + 1;
        y->height = max_child_height(y) + 1;

        x = y;
    }
};

#endif // AVL_TREE_HPP