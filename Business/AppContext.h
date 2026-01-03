#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <memory>
#include <string>
#include "../Entity/BankSystem/BankSystem.h" // Include class BankSystem của bạn

class AppContext
{
public:
    static AppContext &getInstance()
    {
        static AppContext instance;
        return instance;
    }

    void initialize(const std::string &bankName);

    // --- HÀM TRUY CẬP (GỌI MỌI LÚC) ---
    std::shared_ptr<BankSystem> getBankSystem();

    // Xóa copy constructor
    AppContext(const AppContext &) = delete;
    void operator=(const AppContext &) = delete;

private:
    AppContext() = default;
    std::shared_ptr<BankSystem> _bankSystem;
};

#endif