#include "LoginCmd.h"
#include "../../Business/AppContext.h"

#include <iostream>

LoginCmd::LoginCmd()
{
}
void LoginCmd::execute()
{
    string username;
    string pass;
    auto bankSystem = AppContext::getInstance().getBankSystem();
    do
    {
        std::cout << "Tên đăng nhập: \t";

        std::cin >> username;
        std::cout << "Mật khẩu: \t";

        std::cin >> pass;
    } while (!bankSystem->login(username, pass));
    return;
}