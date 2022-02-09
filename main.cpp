#include <stdio.h>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <unistd.h>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "tree.h"
#include "common.h"

#define TAG "main.cpp-> "

void test(std::string path) {
    TreeNode *root = TreeNode::create_root(path);
    if (!root) {
        LOGE << TAG << "invalid node.\n";
        return;
    }

    root->create_path(path);
    TreeNode* node = TreeNode::find_TreeNode(root, "/b/bb/bb1.txt");
    if (node) {
        node->iterate_all_children(node);
    } else {
        std::cout << "Not found.\n";
    }
    // root->iterate_all_children(root);

    // TreeNode* b_node = root->get_TreeNode("b");
    // b_node->remove_node("b1.txt");
    // root->remove_node("b");
    // root->iterate_all_children(root);
}

int main(int argc, char *argv[]) {
    test("/home/descosmos/c++/self_projects/Iterate_dir/test_dir");
    return 0;
}