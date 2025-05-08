#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "TreeBase.hpp"

namespace rb {

enum class Color { RED, BLACK };

template <typename DataType>
struct Node {
    using ValueType = DataType;
    DataType data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    Node(const DataType& inData) 
        : data(inData), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

} // namespace rb

template <typename DataType>
class RBTree : public TreeBase<RBTree<DataType>, rb::Node<DataType>> {
    template<typename, typename>
    friend class TreeBase;

    using Node = rb::Node<DataType>;
protected:
    void rebalance(Node*& node) {
        // Rebalance the tree after insertion or deletion
        // Implementation of RBTree rebalancing logic goes here
    }
    
}; 

#endif // RB_TREE_HPP