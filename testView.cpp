// #include "UI/Views/CustomerView.h"
#include "Business/AppContext.h"

#include <iostream>

int test()
{
    AppContext::getInstance().initialize("N06");
    shared_ptr<BankSystem> bank = AppContext::getInstance().getBankSystem();

    std::cout << bank->info();
    system("pause");
}