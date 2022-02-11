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

    bool init(const std::string rootPath);

    bool checkout();                                                                                 //  lock file and download
    bool checkin();                                                                                  //  Commit the modified file and unlock
    Buffer* get_lasted_version();                                                                    //  get the lasted-version file
    bool rename_file(const std::filesystem::path& filePath, const std::string& newName);             //  rename file
    bool import();                                                                                   //  upload file
    bool remove_file(const std::filesystem::path& filePath);                                         //  Remove file

    //  test
    void print_all_files();

private:
    TreeNode* is_exists(const std::filesystem::path& filePath);
    std::filesystem::path get_relative_path(const std::filesystem::path& absolutePath);

private:
    TreeNode* _root;
    std::map<std::filesystem::path, Log> _file_history;
};

#endif