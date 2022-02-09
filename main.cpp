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

#define TAG "main.cpp: "

void test(const char *path) {
    TreeNode *root = TreeNode::create_root(path);
    if (!root) {
        LOGE << TAG << "invalid node.\n";
        return;
    }

    root->iterate_path(path);
    root->iterate_all_children(root);

    TreeNode* b_node = root->get_TreeNode("b");
    b_node->remove_node("b1.txt");
    // root->remove_node("b");
    root->iterate_all_children(root);
}

int main(int argc, char *argv[]) {
    test("/home/descosmos/c++/self_projects/Iterate_dir/test_dir");
    return 0;
}