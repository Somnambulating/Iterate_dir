#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include "tree.h"
#include "bufferManager.h"
#include "log.h"
#include "common.h"


class FileManager{
public:
    FileManager();
    ~FileManager() {}

    bool init(std::string rootPath);

    bool checkout();                                                     //  锁定资源并下载
    bool checkin();                                                      //  提交修改的文件并解锁
    Buffer* get_lasted_version();                                        //  获取最新版本的文件
    bool rename_file(const std::filesystem::path& filePath);             //  重命名文件
    bool import();                                                       //  上传文件
    bool remove_file(const std::filesystem::path& filePath);             //  删除文件

private:
    TreeNode* is_exists(const std::filesystem::path& filePath);

private:
    TreeNode* _root;
    std::map<std::filesystem::path, Log> _file_history;
};

#endif