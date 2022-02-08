#include <fstream>
#include <iostream>
#include <filesystem>
#include <queue>
#include <list>
#include <cstdlib>

std::string current_path;
std::queue<std::filesystem::path> containter_dir_path;

void Iterate_dir() {
    std::string dir_path(containter_dir_path.front());
    containter_dir_path.pop();
    const std::filesystem::path sandbox(dir_path);
    std::list<std::filesystem::path> container;

    for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox}) {
        if (is_directory(dir_entry)) {
            container.push_back(dir_entry);
        }
        // if (is_regular_file(dir_entry)) {
        //     std::cout << dir_entry << " is regular file" << std::endl;
        // }   
    }

    system("clear");
    std::cout << current_path << "\n";
    for (auto const& dir: container) {
        std::cout << "|\n";
        // std::cout << "|---- " << dir.c_str() << "\n";
        std::cout << "|---- " << dir.filename().string() << "\n";
    }

}

void Iterate_all_dir() {
    // while (containter_dir_path.size() > 0) {
    //     Iterate_dir();
    // }

    while (1) {
        Iterate_dir();
        std::cout << "Input path: ";
        std::cin >> current_path;
        containter_dir_path.push(current_path);
    }
}


int main(int argc, char *argv[]) {
    current_path = std::string(argv[1]);
    containter_dir_path.push(current_path);
    Iterate_all_dir();

    // std::filesystem::path co("/");
    // std::cout << co << "\n";
    // co.append("src");
    // std::cout << co << "\n";
    // co.append("include");
    // std::cout << co << "\n";
    // std::cout << co.parent_path().string() << "\n";
    return 0;
}