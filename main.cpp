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

void test_remove_node(TreeNode* root) {
    TreeNode* b_node = root->get_TreeNode("a");
    // b_node->remove_node("b1.txt");
    root->remove_node("a");
}

void test_find_node(TreeNode* root) {
    TreeNode* node = TreeNode::find_TreeNode(root, "/b/bb/bb1.txt");
    if (node) {
        // LOGI << TAG << "absolute: " << TreeNode::get_absolute_path(node) << "\n";
        node->iterate_all_children(node);
    } else {
        std::cout << "Not found.\n";
    }
}

void test(std::string path) {
    TreeNode *root = TreeNode::create_root(path);
    if (!root) {
        LOGE << TAG << "invalid node.\n";
        return;
    }

    root->create_path(path);
    // test_find_node(root);
    test_remove_node(root);
    root->iterate_all_children(root);
}

int main(int argc, char *argv[]) {
    test("/home/descosmos/c++/self_projects/Iterate_dir/test_dir");
    return 0;
}