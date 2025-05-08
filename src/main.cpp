#include <iostream>
#include <fstream>
#include <filesystem>

#define DEBUG_CONTAINER

#include "../include/AVLTree.hpp"

int main() {
    // Create output directory if it doesn't exist
    std::filesystem::create_directories("output");

    // Create output files
    std::ofstream avlOutput("output/avl_tree_output.txt");

    // Test AVL Tree
    AVLTree<int> avlTree;
    avlOutput << "AVL Tree Test:" << std::endl;
    avlTree.insert(9);
    avlTree.insert(5);
    avlTree.insert(10);
    avlTree.insert(0);
    avlTree.insert(6);
    avlTree.insert(11);
    avlTree.insert(-1);
    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.remove(10);
    avlTree.remove(1);
    avlTree.print_inorder(avlOutput);
    avlOutput.close();

    std::cout << "Output has been written to output/binary_tree_output.txt and output/avl_tree_output.txt" << std::endl;
    return 0;
} 