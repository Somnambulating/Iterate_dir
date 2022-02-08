#ifndef _TREE_H_
#define _TREE_H_

#include <list>
#include <string>
#include <ctype.h>
#include <filesystem>
#include <map>
#include <queue>
#include <cstdlib>
#include <assert.h>


/*
    NodeInfo 结构体中存储着结点的信息
 */
struct NodeInfo {
    std::string _file_name;

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

    TreeNode* create_TreeNode(const std::string& fileName);
    void insert_child_node(const std::string& fileName);
    TreeNode* get_TreeNode(const std::string& fileName);
    void erase_all(TreeNode* node);
    void remove_node(const std::string& filename);
    void iterate_path(const std::string& path);

    // for test
    void iterate_all_children(TreeNode* node);

private:

    TreeNode* _parent;
    std::list<std::pair<std::string, TreeNode*>> _children;
    NodeInfo _node_info;
};
#endif