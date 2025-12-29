#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <memory>
#include "../Entity/BankSystem/BankSystem.h" // Include class BankSystem của bạn

class AppContext
{
public:
    static AppContext &getInstance()
    {
        static AppContext instance;
        return instance;
    }

    void initialize(const std::string &bankName)
    {
        if (_bankSystem == nullptr)
        {
            // std::make_shared sẽ truyền 'bankName' thẳng vào constructor của BankSystem
            _bankSystem = std::make_shared<BankSystem>(bankName);
        }
    }

    // --- HÀM TRUY CẬP (GỌI MỌI LÚC) ---
    std::shared_ptr<BankSystem> getBankSystem()
    {
        // An toàn: Kiểm tra nếu chưa init thì báo lỗi hoặc xử lý
        if (_bankSystem == nullptr)
        {
            return nullptr;
        }
        return _bankSystem;
    }

    // Xóa copy constructor
    AppContext(const AppContext &) = delete;
    void operator=(const AppContext &) = delete;

private:
    AppContext() = default;
    std::shared_ptr<BankSystem> _bankSystem;
};

#endif