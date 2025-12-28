#include <iostream>
#include <memory>
#include <vector>
#include "Entity/Account/Account.h" // Thay đổi đường dẫn theo project của bạn
#include "Entity/Transaction/DepositTransaction.h"
#include "Entity/Transaction/WithdrawTransaction.h"
#include "Entity/Transaction/TransferTransaction.h"
#include "Entity/Notification/Notification.h"

// Giả sử bạn đã có một lớp ConcreteAccount thực thi từ Account
class ConcreteAccount : public Account
{
public:
    ConcreteAccount(std::string number, long long bal) : Account(number, nullptr, bal)
    {
        // Khởi tạo các thuộc tính từ lớp cha Account
        // (Lưu ý: Bạn cần gán giá trị cho _accountNumber và _balance trong thực tế)
    }
    void loadFromFile(std::string numberAccount) override {}
};

int main()
{
    // 1. Khởi tạo tài khoản bằng shared_ptr (Bắt buộc)
    auto accountA = std::make_shared<ConcreteAccount>("ACC001", 5000000); // 5 triệu VND
    auto accountB = std::make_shared<ConcreteAccount>("ACC002", 1000000); // 1 triệu VND

    std::cout << "--- STARTING BANK TRANSACTION TEST ---" << std::endl;

    // 2. Test Giao dịch nạp tiền (Deposit)
    auto depTrans = std::make_shared<DepositTransaction>("DEP_001", accountA, 2000000);
    depTrans->execute(); //

    // 3. Test Giao dịch rút tiền (Withdraw)
    auto withTrans = std::make_shared<WithdrawTransaction>("WIT_001", accountA, 1000000);
    withTrans->execute(); //

    // 4. Test Giao dịch chuyển khoản (Transfer)
    auto transTransaction = std::make_shared<TransferTransaction>("TRA_001", accountA, accountB, 500000);
    transTransaction->execute(); //

    // 5. Kiểm tra kết quả Thông báo (Notification)

    std::cout << "\n--- CHECKING NOTIFICATIONS FOR ACCOUNT A ---" << std::endl;
    auto notifications = accountA->Notifications(); //

    for (const auto &notif : notifications)
    {
        notif->displayInfo(); // Sẽ in ra nội dung tiếng Anh bạn đã sửa
    }
    system("pause");

    return 0;
}