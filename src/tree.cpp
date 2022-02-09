#include "tree.h"
#include "common.h"

#define TAG "tree.cpp "

TreeNode::TreeNode(std::string fileName) {
    this->_parent = nullptr;
    this->_node_info._file_name = fileName;
    /* 
        Infomation initialzition.
     */
}

TreeNode* TreeNode::create_root(const std::string& fileName) {
    TreeNode* root = create_TreeNode(fileName);
    root->_node_info._file_name = fileName;
    root->_node_info._absolute_path = fileName;
    return root;
}

TreeNode* TreeNode::create_TreeNode(const std::string& fileName) {
    TreeNode* newNode = new TreeNode(fileName);
    return newNode;
}

void TreeNode::insert_child_node(const std::string& fileName) {
    TreeNode *newNode = create_TreeNode(fileName);
    if (!newNode) {
        LOGE << TAG << "invalid newNode\n";
        return;
    }
    newNode->_parent = this;
    newNode->_node_info._file_name = fileName;
    newNode->_node_info._absolute_path = this->_node_info._absolute_path;   newNode->_node_info._absolute_path.append(fileName);

    // LOGI << TAG << "_absolute_path: " << newNode->_node_info._absolute_path.string() << "\n";

    this->_children.push_back(std::make_pair(fileName, newNode));
}

TreeNode* TreeNode::get_TreeNode(const std::string& fileName) {
    for (auto it = _children.begin(); it != _children.end(); ++it) {
        if (fileName.find(it->first) != std::string::npos) {
            return it->second;
        }
    }

    return nullptr;
}

void TreeNode::erase_all(TreeNode* node) {
    for (auto it = node->_children.begin(); it != node->_children.end(); it++) {
        erase_all(it->second);
        node->_children.erase(it);
    }

    if (!std::filesystem::exists(node->_node_info._absolute_path)) {
        LOGE << TAG << node->_node_info._absolute_path.c_str() << " not exists.\n";
    }
    std::remove(node->_node_info._absolute_path.c_str());
    delete node;
}

void TreeNode::remove_node(const std::string& fileName) {
    TreeNode *node = get_TreeNode(fileName);
    if (!node) {
        LOGE << TAG << "Cannot remove the node: " << fileName << "\n";
        return;
    }

    // remove the node from parent._children
    TreeNode* parent = node->_parent;
    if (parent != nullptr) {
        for (auto it = parent->_children.begin(); it != parent->_children.end(); ++it) {
            if (it->second == node) {
                parent->_children.erase(it);
                break;
            }
        }
    }

    // // remove children nodes of the node
    for (auto it = node->_children.begin(); it != node->_children.end(); ++it) {
        erase_all(it->second);
    }
    node->_children.erase(node->_children.begin(), node->_children.end());

    // // remove itself
    if (!std::filesystem::exists(node->_node_info._absolute_path)) {
        LOGE << TAG << node->_node_info._absolute_path.c_str() << " not exists.\n";
    }
    std::remove(node->_node_info._absolute_path.c_str());
    delete node;
}

void TreeNode::iterate_path(const std::string& path) {
    const std::filesystem::path sandbox(path);
    // LOGI << "iterate_path: " << sandbox << "\n";
    for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox}) {
        insert_child_node(std::filesystem::path(dir_entry).filename().string());
        if (is_directory(dir_entry)) {
            TreeNode *current_dir = this->get_TreeNode(std::filesystem::path(dir_entry).filename().string());
            assert(current_dir != nullptr);

            current_dir->iterate_path(std::filesystem::path(dir_entry));
        }
    }
}

void TreeNode::update_node_info(NodeInfo *nodeInfo) {
    //  TODO: 
}

//  for test
void TreeNode::iterate_all_children(TreeNode* root) {
    if (!root) {
        return;
    }

    std::queue<TreeNode*> que;
    que.push(root);

    while (!que.empty()) {
        TreeNode* node = que.front();   que.pop();
        if (!node->_children.empty()) {
            std::cout << node->_node_info._file_name << "\n";
        }
        
        int nums = 0;
        for (auto it = node->_children.begin(); it != node->_children.end(); ++it) {
            nums++;

            que.push(it->second);
            // std::cout << "|---- " << it->first << "\n";
            // std::cout << "|---- " << it->second->_node_info._absolute_path.string() << "\n";
            std::cout << "|---- " << it->second->_node_info._file_name << "\n";
        }
        
        std::cout << "\n\n";
    }
}