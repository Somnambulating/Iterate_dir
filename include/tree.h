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


/*
    NodeInfo 结构体中存储着结点的信息
 */
struct NodeInfo {
    std::string _file_name;
    std::filesystem::path _absolute_path;

    /*
        其它信息
    */
    // std::string _file_creator;
    // uint64_t _last_modified_time;
};


/*
    TreeNode 类组成了<目录树>的数据结构
 */
class TreeNode {
public:
    TreeNode() = delete;
    TreeNode(std::string fileName);
    ~TreeNode() {}

    static TreeNode* create_root(const std::string& fileName);
    static TreeNode* create_TreeNode(const std::string& fileName);
    void insert_child_node(const std::string& fileName);
    TreeNode* get_TreeNode(const std::string& fileName);
    static TreeNode* find_TreeNode(TreeNode* root, const std::string& abosultePath);
    void erase_all(TreeNode* node);
    void remove_node(const std::string& filename);
    void create_path(const std::string& path);
    void update_node_info(NodeInfo *nodeInfo);

    // for test
    void iterate_all_children(TreeNode* node);

private:

    TreeNode* _parent;
    std::list<std::pair<std::string, TreeNode*>> _children;
    NodeInfo _node_info;
};
#endif