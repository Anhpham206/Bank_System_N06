#include "Utils.h"

#include <string>
using std::string;

std::vector<std::string> Utils::split(std::string hay, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = hay.find(delimiter)) != std::string::npos)
    {
        token = hay.substr(0, pos);
        tokens.push_back(token);
        hay.erase(0, pos + delimiter.length());
    }
    tokens.push_back(hay); // Lấy phần còn lại cuối cùng
    return tokens;
}

string Utils::inputNumber(int size)
{
    char num;
    string number = "";
    while (true)
    {
        num = _getch();

        if (num == 13)
        {

            if (number.empty())
                continue;
            break;
        }
        if (num == 8)
        {
            if (!number.empty())
            {
                number.pop_back();
                cout << "\b \b";
            }
        }
        else if (num >= '0' && num <= '9' && number.length() < size)
        {
            cout << num;
            number += num;
        }
    }
    return number;
}

// Nhập số có độ dài cố định; chỉ cho phép kết thúc khi đã nhập đúng `size` ký tự
string Utils::inputNumberFixedLength(int size)
{
    char num;
    string number = "";
    while (true)
    {
        num = _getch();

        // Enter chỉ được chấp nhận khi đủ chiều dài
        if (num == 13)
        {
            if ((int)number.length() != size)
                continue;
            break;
        }

        if (num == 8)
        {
            if (!number.empty())
            {
                number.pop_back();
                cout << "\b \b";
            }
        }
        else if (num >= '0' && num <= '9' && number.length() < size)
        {
            cout << num;
            number += num;
        }
    }
    return number;
}

string Utils::inputPassword()
{
    char c;
    string pass = "";
    while (true)
    {
        c = _getch();

        if (c == 13)
        {

            if (pass.empty())
                continue;
            break;
        }
        if (c == 8)
        {
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            cout << "*";
            pass += c;
        }
    }
    return pass;
}