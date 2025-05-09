#ifndef BST_HPP
#define BST_HPP

#include "TreeBase.hpp"

namespace bst {

template <typename DataType>
struct Node {
    using ValueType = DataType;
    DataType data;
    Node* left;
    Node* right;
    Node(const DataType& inData) 
        : data(inData), left(nullptr), right(nullptr) {}
};

} // namespace BST

template <typename DataType>
class BST : public TreeBase<BST<DataType>, bst::Node<DataType> > {
    template<typename, typename>
    friend class TreeBase;

    using Node = bst::Node<DataType>;
protected:
    void rebalance(Node*& node) {
        // No rebalancing needed for a simple BST
    }

#ifdef DEBUG_CONTAINER
    void additional_print(Node* node, std::ostream& os) const {
        // No additional print for BST
    }
#endif
};

#endif // BST_HPP