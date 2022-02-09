#include "fileManager.h"

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

bool FileManager::rename_file() {
    return true;
}

bool FileManager::import() {
    return true;
}

bool FileManager::remove_file() {
    return true;
}