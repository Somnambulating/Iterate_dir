#include "fileManager.h"

#define TAG "fileManager.cpp-> "

FileManager::FileManager() {}

bool FileManager::init(std::string rootPath) {
    _root = TreeNode::create_root(rootPath);
    return _root == nullptr? false: true;
}

bool FileManager::checkout() {
    return true;
}

bool FileManager::checkin() {
    return true;
}

Buffer* FileManager::get_lasted_version() {
    return nullptr;
}

bool FileManager::rename_file(const std::filesystem::path& filePath) {
    TreeNode *node = is_exists(filePath);
    if (!node) {
        return false;
    }
    std::string file_name = filePath.filename().string();
    NodeInfo nodeInfo {file_name};
    node->update_node_info(&nodeInfo, NODEINFOTYPE::FILENAME);
    
    TreeNode *parent_node = TreeNode::get_parent_TreeNode(node);
    // TODO

    return true;
}

bool FileManager::import() {
    return true;
}

bool FileManager::remove_file(const std::filesystem::path& filePath) {
    TreeNode *node = is_exists(filePath);
    if (!node) {
        return false;
    }

    node->remove_node(filePath.filename());
    return true;
}

TreeNode* FileManager::is_exists(const std::filesystem::path& filePath) {
    TreeNode *node = TreeNode::find_TreeNode(_root, filePath);
    if (!node) {
        LOGI << TAG << filePath << " not found in " << _root->_node_info.get_file_name();
        return nullptr;
    }

    return node;
}