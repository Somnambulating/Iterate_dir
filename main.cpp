#include <stdio.h>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <unistd.h>
#include <filesystem>
#include <iostream>

#include "tree.h"
#include "common.h"

#define TAG "main.cpp: "

void test(const char *path) {
    TreeNode *root = new TreeNode(path);
    if (!root) {
        LOGE << TAG << "invalid node.\n";
        return;
    }

    root->iterate_path(path);
    root->iterate_all_children(root);

    root->remove_node("b");
    root->iterate_all_children(root);
}

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     LOGE << "lack argv.\n";
    //     return -1;
    // }
    
    // test(argv[1]);
    test("/home/descosmos/c++/self_projects/Iterate_dir/test_dir");
    return 0;
}