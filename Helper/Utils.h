#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>
#include <sstream>

#include <string>
#include <vector>
#include <sstream>

namespace Utils {
    // Hàm tách chuỗi (Delimiter mặc định là dấu phẩy và khoảng trắng)
    static std::vector<std::string> split(std::string hay, std::string delimiter = ", ") {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = hay.find(delimiter)) != std::string::npos) {
            token = hay.substr(0, pos);
            tokens.push_back(token);
            hay.erase(0, pos + delimiter.length());
        }
        tokens.push_back(hay); // Lấy phần còn lại cuối cùng
        return tokens;
    }
} // namespace Utils

#endif