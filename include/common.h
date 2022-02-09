#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <vector>
#include <queue>
#include <string>

#ifndef LOGI
#define LOGI std::cout
#endif

#ifndef LOGE
#define LOGE std::cerr
#endif

/*
@ Function Name: split_string_to_vector
@ args: str, que, delimiter
@ description: To split a str to string segments using delimiter, and putting the string segments in que.
*/
void split_string_to_vector(std::string str, std::queue<std::string>& que, const std::string delimiter);

#endif