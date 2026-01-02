#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <conio.h>

using std::cout;
using std::string;

namespace Utils
{
    // Hàm tách chuỗi (Delimiter mặc định là dấu phẩy và khoảng trắng)
    std::vector<std::string> split(std::string hay, std::string delimiter = ", ");

    string inputNumber(int size);
} // namespace Utils

#endif