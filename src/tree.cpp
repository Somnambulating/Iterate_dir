#include "tree.h"
#include "common.h"

#define TAG "tree.cpp-> "

//===========================
//  NodeInfo struct
//===========================

/*
@ Function Name: NodeInfo::get_file_name
@ args: None
@ ret: Return _file_name.
*/
std::string NodeInfo::get_file_name() {
    return this->_file_name;
}

/*
@ Function Name: NodeInfo::update_file_name
@ args: fileName
@ ret: Update _file_name with fileName.
*/
void NodeInfo::update_file_name(std::string fileName) {
    this->_file_name = fileName;
}


//===========================
//  TreeNode class
//===========================
TreeNode::TreeNode(std::string fileName) {
    this->_parent = nullptr;
    this->_node_info._file_name = fileName;
    /* 
        Infomation initialzition.
     */
}

/*
@ Function Name: TreeNode::create_root
@ args: fileName
@ ret: Return the root TreeNode, or nullptr if failed.
*/
TreeNode* TreeNode::create_root(const std::string& fileName) {
    TreeNode* root = create_TreeNode(fileName);
    root->_node_info._file_name = fileName;
    return root;
}

/*
@ Function Name: TreeNode::insert_child_node
@ args: fileName
@ ret: This function returns a new TreeNode node , or nullptr if the request fails.
@ description: Insert a child TreeNode to children set.
*/
TreeNode* TreeNode::create_TreeNode(const std::string& fileName) {
    TreeNode* newNode = new TreeNode(fileName);
    return newNode;
}

/*
@ Function Name: TreeNode::insert_child_node
@ args: fileName
@ description: Insert a child TreeNode to children set.
*/
void TreeNode::insert_child_node(const std::string& fileName) {
    TreeNode *newNode = create_TreeNode(fileName);
    if (!newNode) {
        LOGE << TAG << "invalid newNode\n";
        return;
    }
    newNode->_parent = this;
    newNode->_node_info._file_name = fileName;

    this->_children.push_back(newNode);
}

/*
@ Function Name: TreeNode::get_parent_TreeNode
@ args: node
@ ret: Return the parent TreeNode of the node, or nullptr if not found.
*/
TreeNode* TreeNode::get_parent_TreeNode(TreeNode* node) {
    return node->_parent != nullptr? node->_parent: nullptr;
}

/*
@ Function Name: TreeNode::get_TreeNode
@ args: fileName
@ ret: Return the TreeNode of fileName, or nullptr if not found.
@ description: To search a TreeNode named fileName in this->_children, 
               if exists return fileName's TreeNode, if not return nullptr.
*/
TreeNode* TreeNode::get_TreeNode(const std::string& fileName) {
    for (auto it = _children.begin(); it != _children.end(); ++it) {
        if (!strcmp(fileName.c_str(), (*it)->_node_info.get_file_name().c_str())) {
            return *it;
        }
    }

    return nullptr;
}

/*
@ Function Name: TreeNode::find_TreeNode
@ args: relativePath
@ ret: Return the TreeNode of relativePath, or nullptr if not found.
@ description: To search recursively whether relativePath in root or not, 
               if in return relativePath's TreeNode, if not return nullptr.
*/
TreeNode* TreeNode::find_TreeNode(TreeNode* root, const std::string& relativePath) {
    TreeNode* result = root;
    std::queue<std::string> que;
    split_string_to_vector(relativePath, que, "/");
    while (!que.empty()) {
        // LOGI << TAG << "que.front(): " << que.front() << "\n";
        result = result->get_TreeNode(que.front());
        que.pop();
        if (!result) {
            return nullptr;
        }      
    }

    return result;
}

/*
@ Function Name: TreeNode::get_absolute_path
@ args: node
@ description: Return absolute path of the node.
*/
std::filesystem::path TreeNode::get_absolute_path(TreeNode *node) {
    std::filesystem::path absolute_path;
    if (!get_parent_TreeNode(node)) {
        return node->_node_info._file_name;
    }
    
    absolute_path = get_absolute_path(get_parent_TreeNode(node));
    absolute_path.append(node->_node_info._file_name);
    return absolute_path;
}

/*
@ Function Name: TreeNode::erase_all
@ args: node
@ description: Delete all sub-node and itself recrusively.
*/
void TreeNode::erase_all(TreeNode* node) {
    for (auto it = node->_children.begin(); it != node->_children.end(); it++) {
        erase_all(*it);
    }
    
    node->_children.clear();
    delete node;
}

/*
@ Function Name: TreeNode::remove_node
@ args: fileName
@ description: Remove the node of fileName and all nodes inferior than the node of fileName.
*/
void TreeNode::remove_node(const std::string& fileName) {
    TreeNode *node = get_TreeNode(fileName);
    if (!node) {
        LOGE << TAG << "Cannot remove the node: " << fileName << "\n";
        return;
    }

    // remove the node from parent._children
    TreeNode* parent = get_parent_TreeNode(node);
    if (parent != nullptr) {
        for (auto it = parent->_children.begin(); it != parent->_children.end(); ++it) {
            if (*(it) == node) {
                parent->_children.erase(it);
                break;
            }
        }
    }

    // remove children nodes of the node
    for (auto it = node->_children.begin(); it != node->_children.end(); ++it) {
        erase_all(*it);
    }
    node->_children.clear();

    // remove itself
    delete node;
}

/*
@ Function Name: TreeNode::create_path
@ args: absolutePath
@ description: Construct a TreeNode-tree based on path.
*/
void TreeNode::create_tree(const std::string& absolutePath) {
    const std::filesystem::path sandbox(absolutePath);
    // LOGI << "iterate_path: " << sandbox << "\n";
    for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox}) {
        insert_child_node(std::filesystem::path(dir_entry).filename().string());
        if (is_directory(dir_entry)) {
            TreeNode *current_dir = this->get_TreeNode(std::filesystem::path(dir_entry).filename().string());
            assert(current_dir != nullptr);

            current_dir->create_tree(std::filesystem::path(dir_entry));
        }
    }
}

/*
@ Function Name: TreeNode::update_node_info
@ args: nodeInfo, nodeInfoType
@ description: Modify the content of this->_node_info with nodeInfo. 
            nodeInfoType indicates the target item inner NodeInfo structure will be modified.
*/
void TreeNode::update_node_info(NodeInfo *nodeInfo, NODEINFOTYPE nodeInfoType) {
    std::filesystem::path absolute_path = TreeNode::get_absolute_path(this);

    switch(nodeInfoType) {
    case FILENAME:
        std::filesystem::rename(absolute_path, std::filesystem::path(absolute_path).parent_path().append(nodeInfo->get_file_name()));
        _node_info.update_file_name(nodeInfo->get_file_name());
        break;

    default:
        LOGE << TAG << "Cannot recognize nodeInfoType: " << nodeInfoType << "\n"; 
    }
}

//  for test
void TreeNode::iterate_all_children(TreeNode* root) {
    if (!root) {
        return;
    }

    if (root->_children.empty()) {
        std::cout << "|---- " << root->_node_info._file_name << "\n";
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

            que.push(*(it));
            // std::cout << "|---- " << it->first << "\n";
            std::cout << "|---- " << (*it)->_node_info.get_file_name().c_str() << "\n";
        }
        
        std::cout << "\n\n";
    }
}