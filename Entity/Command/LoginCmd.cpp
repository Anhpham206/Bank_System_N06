#include "LoginCmd.h"

#include <iostream>

LoginCmd::LoginCmd(std::shared_ptr<BankSystem> bankSystem)
{
    _bankSystem = bankSystem;
}
void LoginCmd::execute()
{
    string username;
    string pass;
    do
    {
        std::cout << "Tên đăng nhập: \t";

        std::cin >> username;
        std::cout << "Mật khẩu: \t";

        std::cin >> pass;
    } while (!_bankSystem->login(username, pass));
    return;
}