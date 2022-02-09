#include "common.h"

void split_string_to_vector(std::string str, std::queue<std::string>& que, const std::string delimiter) {
    if (str.empty()) {
        return;
    }

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        if (!token.empty()) {
            que.push(token);
        }
        str.erase(0, pos + delimiter.length());
    }
    if (!str.empty()) {
        que.push(str);
    }
}