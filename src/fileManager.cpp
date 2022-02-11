#include "fileManager.h"

#define TAG "fileManager.cpp-> "

FileManager::FileManager() {}

bool FileManager::init(const std::string rootPath) {
    _root = TreeNode::create_root(rootPath);
    if (!_root) {
        return false;
    }

    _root->create_tree(rootPath);
    return true;
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

bool FileManager::rename_file(const std::filesystem::path& filePath, const std::string& newName) {
    std::filesystem::path relative_path = get_relative_path(filePath);
    LOGI << TAG << "relative_path: " << relative_path.string() << "\n";
    if (relative_path.empty()) {
        return false;
    }

    TreeNode *node = is_exists(relative_path);
    if (!node) {
        return false;
    }
    std::string file_name = relative_path.filename().string();
    NodeInfo nodeInfo {newName};
    node->update_node_info(&nodeInfo, NODEINFOTYPE::FILENAME);
    return true;
}

bool FileManager::import() {
    return true;
}

bool FileManager::remove_file(const std::filesystem::path& filePath) {
    std::filesystem::path relative_path = get_relative_path(filePath);
    // LOGI << TAG << "relative_path: " << relative_path.string() << "\n";
    if (relative_path.empty()) {
        return false;
    }

    if (!is_exists(relative_path)) {
        LOGE << TAG << filePath << " not exists.\n";
        return false;
    }
    TreeNode *parent_node = TreeNode::find_TreeNode(_root, relative_path.parent_path().string());
    
    parent_node->remove_node(relative_path.filename().string());
    std::filesystem::remove_all(filePath);
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

std::filesystem::path FileManager::get_relative_path(const std::filesystem::path& absolutePath) {
    std::filesystem::path relative_path;
    size_t index = absolutePath.string().find(_root->_node_info.get_file_name());
    if (index == std::string::npos) {
        LOGE << TAG << absolutePath.string() << " not in " << _root->_node_info.get_file_name() << "\n";
        return "";
    }

    return std::filesystem::path(std::string(absolutePath.string().substr(_root->_node_info.get_file_name().length())));
}

void FileManager::print_all_files() {
    TreeNode::iterate_all_children(_root);
}