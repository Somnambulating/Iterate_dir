#ifndef _TREE_H_
#define _TREE_H_

#include <list>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <ctype.h>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <assert.h>

enum NODEINFOTYPE{
    FILENAME
};

/*
    NodeInfo, which containes the information of current node.
 */
struct NodeInfo {
    std::string _file_name;

    /*
        Node Information
    */
    // std::string _file_creator;
    // uint64_t _last_modified_time;

    void update_file_name(std::string newName);
    std::string get_file_name();
};


/*
    TreeNode, which construct the data-structure of <directory-tree>
 */
class TreeNode {
public:
    TreeNode() = delete;
    TreeNode(std::string fileName);
    ~TreeNode() {}

    static TreeNode* create_root(const std::string& fileName);
    static TreeNode* create_TreeNode(const std::string& fileName);
    static TreeNode* find_TreeNode(TreeNode* root, const std::string& relativePath);
    static std::filesystem::path get_absolute_path(TreeNode *node);
    static TreeNode* get_parent_TreeNode(TreeNode* node);

    void insert_child_node(const std::string& fileName);
    TreeNode* get_TreeNode(const std::string& fileName);
    void erase_all(TreeNode* node);
    void remove_node(const std::string& filename);
    void create_tree(const std::string& absolutePath);
    void update_node_info(NodeInfo *nodeInfo, NODEINFOTYPE nodeInfoType);

    // for test
    static void iterate_all_children(TreeNode* node);

public:
    NodeInfo _node_info;

private:

    TreeNode* _parent;
    std::list<TreeNode*> _children;
};
#endif